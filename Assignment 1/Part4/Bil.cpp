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

	// size is 1x width, 2x height
	int size;

	HBRUSH redBrush = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH yellowBrush = CreateSolidBrush(RGB(255, 255, 0));
	HBRUSH greenBrush = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH blueBrush = CreateSolidBrush(RGB(0, 0, 255));
	HBRUSH blackBrush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH whiteBrush = CreateSolidBrush(RGB(255, 255, 255));

public:
	// position is the relevant position on the road line, dependant on Direction
	BilDirection dir;
	int pos;
	
	Bil(const BilColour colour, const BilDirection dir, const int size) : colour(colour), dir(dir), pos(0), size(size)
	{
	}

	void updatePos(const int movement)
	{
		pos += movement;
	}

	void draw(const HDC& hdc, const int line) const
	{
		const HGDIOBJ hOrg = SelectObject(hdc, whiteBrush);
		switch (colour)
		{
		case BilColour::RED:
			SelectObject(hdc, redBrush);
			break;
		case BilColour::YELLOW:
			SelectObject(hdc, yellowBrush);
			break;
		case BilColour::GREEN:
			SelectObject(hdc, greenBrush);
			break;
		case BilColour::BLUE:
			SelectObject(hdc, blueBrush);
			break;
		case BilColour::BLACK:
			SelectObject(hdc, blackBrush);
			break;
		case BilColour::WHITE:
			SelectObject(hdc, whiteBrush);
			break;
		}

		switch (dir)
		{
		case BilDirection::HORIZONTAL:
			Rectangle(hdc, pos - size, line - (size/2), pos + size, line + (size/2));
			break;
		case BilDirection::VERTICAL:
			Rectangle(hdc, line - (size/2), pos - size, line + (size/2), pos + size);
			break;
		}
		SelectObject(hdc, hOrg);
	}
};
