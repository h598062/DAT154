#pragma once
#include "framework.h"

class Car
{
public:
	Car(int x, int y) : m_x(x), m_y(y) {}

	void Text(HDC* pdc);

	int m_x, m_y;
};


