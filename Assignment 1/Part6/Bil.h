#pragma once

#include "Windows.h"

enum class BilColour
{
	RED,
	GREEN,
	BLUE,
	YELLOW,
	BLACK,
	WHITE,
	PINK,
	ORANGE,
	PURPLE,
	BROWN,
	CYAN
};

enum class BilDirection
{
	HORIZONTAL,
	VERTICAL
};

class Bil
{
	BilColour colour;

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
