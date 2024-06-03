#pragma once
#include "framework.h"
class Car
{
private:
	HBRUSH color;
	HPEN outline;
	int position = 0;
public:
	Car();
	Car(int pos = 0, int red = 0, int green = 0, int blue = 0);
	~Car();
	void Draw(HDC hdc, POINT origin, char direction = 'v') const;
	int Position();
	void Position(int pos);
	void IncrementPosition(int move);
};

