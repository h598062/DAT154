#pragma once

#include "Windows.h"

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

	HBRUSH redBrush = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH yellowBrush = CreateSolidBrush(RGB(255, 255, 0));
	HBRUSH greenBrush = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH blueBrush = CreateSolidBrush(RGB(0, 0, 255));
	HBRUSH blackBrush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH whiteBrush = CreateSolidBrush(RGB(255, 255, 255));

public:
	// size is 1x width, 2x height
	int size;
	// position is the relevant position on the road line, dependant on Direction
	BilDirection dir;
	int pos;
	bool invalid;

	Bil(const BilColour colour, const BilDirection dir, const int size);

	void updatePos(const int movement);
	void draw(const HDC& hdc, const int line) const;
	bool collidesWith(const int otherPos, const int movesize) const;
};
