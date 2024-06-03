#include "TrafficSim.h"

TrafficSim::TrafficSim() {
    srand(time(0));
}


void TrafficSim::Start(HWND hWnd) {

    SetTimer(hWnd, TIMER_LIGHTS, 2000, 0);
    SetTimer(hWnd, TIMER_CARS, 100, 0);
    SetTimer(hWnd, TIMER_ADD_CARS, 500, 0);

    // We are gambling here that screen resolution doesn't change (change to window size is fine however)
    HDC screenDC = GetDC(hWnd);
    XRes = GetDeviceCaps(screenDC, HORZRES);
    YRes = GetDeviceCaps(screenDC, VERTRES);
    DeleteDC(screenDC);

}


void TrafficSim::Draw(HDC hdc, HWND hWnd) const {

    RECT dims;
    GetClientRect(hWnd, &dims);
    POINT screenCenter = { dims.right / 2, dims.bottom / 2 };

    Rectangle(hdc, dims.left, dims.top, dims.right, dims.bottom);

    drawRoad(hdc, &dims, &screenCenter);

    drawLight(hdc, POINT{ screenCenter.x - ROAD_WIDTH, screenCenter.y - (ROAD_WIDTH * 2) }, 'n');
    drawLight(hdc, POINT{ screenCenter.x - (ROAD_WIDTH * 2), screenCenter.y + (ROAD_WIDTH / 2) }, 'w');

    drawChances(hdc, &screenCenter);


    // Draw cars
    auto it = northCars.begin();
    while (it != northCars.end()) {
        (*it)->Draw(hdc, screenCenter, 'v');
        it++;
    }

    it = westCars.begin();
    while (it != westCars.end()) {
        (*it)->Draw(hdc, screenCenter, 'h');

        it++;
    }


}


void TrafficSim::MoveCars(HWND hWnd) {

    doMove(northCars.begin(), northCars.end(), 2);
    doMove(westCars.begin(), westCars.end(), 0);
    
    InvalidateRect(hWnd, 0, 0);

}


void TrafficSim::doMove(std::deque<Car*>::iterator it, std::deque<Car*>::iterator end, int light) {
    int prevpos = 99999; // Setting an impossible high starting value
    int minDistance = 5;
    int speed = 15;

    while (it != end) {
        if ((*it)->Position() + minDistance + speed + CAR_LENGTH < prevpos) { // not crashing into other cars

            if (lightstate != light                                     // not green light
                && (*it)->Position() + CAR_LENGTH <= ROAD_WIDTH / -2                // and we have not passed the stop line
                && (*it)->Position() + CAR_LENGTH + speed >= ROAD_WIDTH / -2) { // but additional movement would push us over

                (*it)->Position(ROAD_WIDTH / -2 - CAR_LENGTH);
            }
            else { // nothing blocks our movement
                (*it)->IncrementPosition(speed);
            }
        }
        prevpos = (*it)->Position();
        it++;
    }
}


void TrafficSim::SpawnCars(HWND hWnd) {

    if (northCars.empty() || (*northCars.rbegin())->Position() > -(YRes / 2 + 50 - CAR_LENGTH)) {
        if (rand() % 100 < pN) {
            northCars.push_back(new Car(-(YRes / 2 + 50), rand() % 255, rand() % 255, rand() % 255));
        }
    }

    // remove cars outside screen borders
    if (!northCars.empty() && (*northCars.begin())->Position() > YRes / 2 + 50) {
        delete(*northCars.begin());
        northCars.pop_front();

    }

    if (westCars.empty() || (*westCars.rbegin())->Position() > -(XRes / 2 + 50 - CAR_LENGTH)) {
        if (rand() % 100 < pW) {
            westCars.push_back(new Car(-(XRes / 2 + 50),rand() % 255, rand() % 255, rand() % 255));
        }
    }

    // remove cars outside screen borders
    if (!westCars.empty() && (*westCars.begin())->Position() > XRes / 2 + 50) {
        delete(*westCars.begin());
        westCars.pop_front();
    }
}


void TrafficSim::NextLightstate(HWND hWnd) {
    lightstate = ++lightstate % 4;
    SetTimer(hWnd, TIMER_LIGHTS, lightstate % 2 == 1 ? 1000 : 5000, 0);
}


int TrafficSim::normalizeSpawnrate(int value) {
    value = value < 0 ? 0 : value;
    value = value > 100 ? 100 : value;
    return value;
}


void TrafficSim::ChangeSpawnrate(int value, char direction) {
    switch (direction) {
    case 'n':
    case 'N':
        pN = normalizeSpawnrate(pN + value);
        break;
    case 'w':
    case 'W':
        pW = normalizeSpawnrate(pW + value);
        break;
    }
}


void TrafficSim::SetSpawnrate(int value, char direction) {
    switch (direction) {
    case 'n':
    case 'N':
        pN = normalizeSpawnrate(value);
        break;
    case 'w':
    case 'W':
        pW = normalizeSpawnrate(value);
        break;
    }
}


const int& TrafficSim::GetSpawnrate(const char& direction) const{
    switch (direction) {
    case 'n':
    case 'N':
        return pN;
    case 'w':
    case 'W':
        return pW;
    }
}


void TrafficSim::drawRoad(HDC hdc, const RECT* dimensions, const POINT* origin) const{

    HBRUSH roadBrush = CreateSolidBrush(ROAD_COLOR);
    HPEN outline = CreatePen(PS_SOLID, 2, OUTLINE_COLOR);
    HGDIOBJ hOrgBrush = SelectObject(hdc, roadBrush);
    HGDIOBJ hOrgPen = SelectObject(hdc, outline);

    drawRoadSurface(hdc, dimensions, origin);

    HPEN nullPen = CreatePen(PS_NULL, 2, 0);
    SelectObject(hdc, nullPen);
    drawRoadSurface(hdc, dimensions, origin);

    SelectObject(hdc, hOrgBrush);
    SelectObject(hdc, hOrgPen);
    DeleteObject(roadBrush);
    DeleteObject(nullPen);
    DeleteObject(outline);
}


void TrafficSim::drawRoadSurface(HDC hdc, const RECT* dimensions, const POINT* origin) const {
    Rectangle(hdc, dimensions->left, origin->y - (ROAD_WIDTH / 2), dimensions->right, origin->y + (ROAD_WIDTH / 2));
    Rectangle(hdc, origin->x - (ROAD_WIDTH / 2), dimensions->top, origin->x + (ROAD_WIDTH / 2), dimensions->bottom);
}


void TrafficSim::drawLight(HDC hdc, POINT position, char direction) const {
    direction = tolower(direction);

    HDC lightDC = CreateCompatibleDC(hdc);
    HBITMAP lightBitmap = CreateCompatibleBitmap(hdc, ROAD_WIDTH / 2, 3 * ROAD_WIDTH / 2);
    SelectObject(lightDC, lightBitmap);


    HBRUSH lightBrush = CreateSolidBrush(RGB(255, 255, 255));
    HPEN outline = CreatePen(PS_INSIDEFRAME, 2, OUTLINE_COLOR);
    HGDIOBJ hOrgPen = SelectObject(lightDC, outline);
    HGDIOBJ hOrgBrush = SelectObject(lightDC, lightBrush);

    Rectangle(lightDC, 0, 0, ROAD_WIDTH / 2, 3 * ROAD_WIDTH / 2);

    HBRUSH darkBrush = CreateSolidBrush(LIGHT_OFF_COLOR);
    SelectObject(lightDC, darkBrush);
    for (int i = 0; i <= 2; i++) {
        Ellipse(lightDC, 0, ROAD_WIDTH * i / 2.0, ROAD_WIDTH / 2, ROAD_WIDTH * (i + 1) / 2.0);
    }


    HBRUSH redLight = CreateSolidBrush(RED_COLOR);
    HBRUSH yellowLight = CreateSolidBrush(YELLOW_COLOR);
    HBRUSH greenLight = CreateSolidBrush(GREEN_COLOR);

    int state = (lightstate + ((direction == 'n' || direction == 's') ? 0 : 2)) % 4;

    switch (state) {
    case 0: // red
        SelectObject(lightDC, redLight);
        Ellipse(lightDC, 0, ROAD_WIDTH * 0 / 2.0, ROAD_WIDTH / 2, ROAD_WIDTH * 1 / 2.0);
        break;
    case 1: // red+yellow
        SelectObject(lightDC, redLight);
        Ellipse(lightDC, 0, ROAD_WIDTH * 0 / 2.0, ROAD_WIDTH / 2, ROAD_WIDTH * 1 / 2.0);
        SelectObject(lightDC, yellowLight);
        Ellipse(lightDC, 0, ROAD_WIDTH * 1 / 2.0, ROAD_WIDTH / 2, ROAD_WIDTH * 2 / 2.0);
        break;
    case 2: // green
        SelectObject(lightDC, greenLight);
        Ellipse(lightDC, 0, ROAD_WIDTH * 2 / 2.0, ROAD_WIDTH / 2, ROAD_WIDTH * 3 / 2.0);
        break;
    case 3: // yellow
        SelectObject(lightDC, yellowLight);
        Ellipse(lightDC, 0, ROAD_WIDTH * 1 / 2.0, ROAD_WIDTH / 2, ROAD_WIDTH * 2 / 2.0);
        break;
    }

    SelectObject(lightDC, hOrgBrush);
    SelectObject(lightDC, hOrgPen);
    DeleteObject(lightBrush);
    DeleteObject(darkBrush);
    DeleteObject(redLight);
    DeleteObject(yellowLight);
    DeleteObject(greenLight);
    DeleteObject(outline);

    switch (direction) {
    case 'n':
        BitBlt(hdc, position.x, position.y, ROAD_WIDTH / 2, 3 * ROAD_WIDTH / 2, lightDC, 0, 0, SRCCOPY);
        break;
    case 's':
    {
        POINT coords[3] = { {position.x + ROAD_WIDTH / 2, position.y + 3 * ROAD_WIDTH / 2},{position.x, position.y + 3 * ROAD_WIDTH / 2} ,{position.x + ROAD_WIDTH / 2, position.y} };
        PlgBlt(hdc, coords, lightDC, 0, 0, ROAD_WIDTH / 2, 3 * ROAD_WIDTH / 2, 0, 0, 0);
        break;
    }
    case 'w':
    {
        POINT coords[3] = { {position.x + 3 * ROAD_WIDTH / 2, position.y},{position.x + 3 * ROAD_WIDTH / 2, position.y + ROAD_WIDTH / 2} ,{position.x, position.y} };
        PlgBlt(hdc, coords, lightDC, 0, 0, ROAD_WIDTH / 2, 3 * ROAD_WIDTH / 2, 0, 0, 0);
        break;
    }
    case 'e':
    {
        POINT coords[3] = { {position.x, position.y + ROAD_WIDTH / 2},{position.x, position.y},{position.x + 3 * ROAD_WIDTH / 2, position.y + ROAD_WIDTH / 2} };
        PlgBlt(hdc, coords, lightDC, 0, 0, ROAD_WIDTH / 2, 3 * ROAD_WIDTH / 2, 0, 0, 0);
        break;
    }
    }

    DeleteObject(lightBitmap);
    DeleteDC(lightDC);
}


void TrafficSim::drawChances(HDC hdc, const POINT* origin) const {
    WCHAR num[10];
    SetBkMode(hdc, TRANSPARENT);
    StringCbPrintf(num, 10, L"%d%%", pN);
    TextOut(hdc, origin->x - ROAD_WIDTH, origin->y - (ROAD_WIDTH * 2) - 20, num, wcsnlen_s(num, 4));
    StringCbPrintf(num, 10, L"%d%%", pW);
    TextOut(hdc, origin->x - (ROAD_WIDTH * 2) - 40, origin->y + (ROAD_WIDTH / 2), num, wcsnlen_s(num, 4));
}


