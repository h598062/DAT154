#pragma once

#include "framework.h"

enum class BilColour
{
	RED,
	GREEN,
	BLUE,
	YELLOW,
	BLACK,
	WHITE
};

enum class BilDirection
{
	HORIZONTAL,
	VERTICAL
};

class Bil
{
	BilColour colour;

	HBRUSH redBrush;
	HBRUSH yellowBrush;
	HBRUSH greenBrush;
	HBRUSH blueBrush;
	HBRUSH blackBrush;
	HBRUSH whiteBrush;

public:
	int size;
	BilDirection dir;
	int pos;
	bool invalid;

	Bil(const BilColour colour, const BilDirection dir, const int size);

	void updatePos(const int movement);
	void draw(const HDC& hdc, const int line) const;
	bool collidesWith(const int otherPos, const int movesize) const;
};
