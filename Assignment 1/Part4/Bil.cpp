#include "framework.h"

enum class Colour
{
	RED,
	GREEN,
	BLUE,
	YELLOW,
	BLACK,
	WHITE
};

enum class Direction
{
	HORIZONTAL,
	VERTICAL
};

class Bil
{
	Colour colour;
	Direction dir;

	// position is the relevant position on the road line, dependant on Direction
	int x, y;

	// size is 1x width, 2x height
	int size;

	HBRUSH redBrush = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH yellowBrush = CreateSolidBrush(RGB(255, 255, 0));
	HBRUSH greenBrush = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH blueBrush = CreateSolidBrush(RGB(0, 0, 255));
	HBRUSH blackBrush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH whiteBrush = CreateSolidBrush(RGB(255, 255, 255));

public:
	Bil(const Colour colour, const Direction dir, const int x, const int y, const int size) : colour(colour), dir(dir), x(x), y(y), size(size)
	{
	}

	void draw(const HDC& hdc) const
	{
		HGDIOBJ hOrg = SelectObject(hdc, whiteBrush);
		switch (colour)
		{
		case Colour::RED:
			SelectObject(hdc, redBrush);
			break;
		case Colour::YELLOW:
			SelectObject(hdc, yellowBrush);
			break;
		case Colour::GREEN:
			SelectObject(hdc, greenBrush);
			break;
		case Colour::BLUE:
			SelectObject(hdc, blueBrush);
			break;
		case Colour::BLACK:
			SelectObject(hdc, blackBrush);
			break;
		case Colour::WHITE:
			SelectObject(hdc, whiteBrush);
			break;
		}

		switch (dir)
		{
		case Direction::HORIZONTAL:
			Rectangle(hdc, x, y, x + size, y + (size * 2));
			break;
		case Direction::VERTICAL:
			Rectangle(hdc, x, y, x + (size * 2), y + size);
			break;
		}
		SelectObject(hdc, hOrg);
	}
};
