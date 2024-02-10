#include "Windows.h"
#include "Bil.h"
#include "ColourBrushes.h"


Bil::Bil(const BilColour colour, const BilDirection dir, const int size) :
	colour(colour),
	size(size),
	dir(dir),
	pos(0),
	invalid(false)
{
}

void Bil::updatePos(const int movement)
{
	pos += movement;
}

void Bil::draw(const HDC& hdc, const int line) const
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
		Rectangle(hdc, pos - size, line - (size / 2), pos + size, line + (size / 2));
		break;
	case BilDirection::VERTICAL:
		Rectangle(hdc, line - (size / 2), pos - size, line + (size / 2), pos + size);
		break;
	}
	SelectObject(hdc, hOrg);
}

bool Bil::collidesWith(const int otherPos, const int movesize) const
{
	if (otherPos < 0)
	{
		return false;
	}
	return pos + size + (2 * movesize) >= otherPos;
}
