#pragma once
#include "framework.h"

class Car
{
private:
	COLORREF color;
	POINT pos;

public:
	Car();
	void Draw(HDC hDC);


};

