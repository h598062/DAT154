#include "Car.h"

Car::Car() {
	color = CreateSolidBrush(RGB(0, 0, 0));
	
}

Car::Car(int pos, int red, int green, int blue) {
	position = pos;
	color = CreateSolidBrush(RGB(red, green, blue));
	outline = CreatePen(PS_SOLID, 2, OUTLINE_COLOR);
}

Car::~Car() {
	DeleteObject(color);
	DeleteObject(outline);
}

void Car::Position(int pos) {
	position = pos;
}

int Car::Position() {
	return position;
}

void Car::IncrementPosition(int move) {
	position += move;
}

void Car::Draw(HDC hdc, POINT origin, char direction) const {

	
	HGDIOBJ hOrgPen = SelectObject(hdc, outline);
	HGDIOBJ hOrgBrush = SelectObject(hdc, color);

	switch (direction) {
	case 'H':
	case 'h':
		Rectangle(hdc, position + origin.x, origin.y - CAR_WIDTH / 2, position + CAR_LENGTH + origin.x, origin.y + CAR_WIDTH / 2);
		break;
	default:
		Rectangle(hdc, origin.x - CAR_WIDTH / 2, position + origin.y, origin.x + CAR_WIDTH / 2, position + CAR_LENGTH + origin.y);

	}

	SelectObject(hdc, hOrgBrush);
	SelectObject(hdc, hOrgPen);


}