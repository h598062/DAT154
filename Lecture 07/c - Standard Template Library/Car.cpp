#include "Car.h"

void Car::Text(HDC* pdc) {
	TextOut(*pdc, m_x, m_y, _T("Car"), 4);
}
