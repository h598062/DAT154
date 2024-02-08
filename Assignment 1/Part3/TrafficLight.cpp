#include "framework.h"
#include "Part3.h"

enum class TLState
{
	STOP,
	READY,
	GO,
	SLOW
};

enum class TLDir
{
	VERTICAL,
	HORIZONTAL
};

class TLCircle
{
public:
	int top;
	int bottom;
	int left;
	int right;

	int size;

	// Posistion is top left corner
	TLCircle(int posX, int posY, int size) :
		top(posY),
		bottom(posY + size),
		left(posX),
		right(posX + size),
		size(size)
	{
	}

	// Draw the circle, remember to set brush color before calling this
	void draw(HDC hdc)
	{
		Ellipse(hdc, left, top, right, bottom);
	}

	void setPos(int x, int y)
	{
		top = y;
		bottom = y + size;
		left = x;
		right = x + size;
	}
};

class TrafficLight
{
	TLState state;
	int posX;
	int posY;
	TLDir dir;
	const int spacing = 10;
	const int circleSize = 50;

	TLCircle* red;
	TLCircle* yellow;
	TLCircle* green;

	HBRUSH offBrush = CreateSolidBrush(RGB(180, 180, 180));
	HBRUSH redBrush = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH yellowBrush = CreateSolidBrush(RGB(255, 255, 0));
	HBRUSH greenBrush = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH outlineBrush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH bgBrush = CreateSolidBrush(RGB(50, 50, 50));

	// Draw lights on the traffic light
	void drawLights(HDC& hdc, bool redState, bool yellowState, bool greenState)
	{
		// Draw Red light
		if (redState)
		{
			SelectObject(hdc, redBrush);
		}
		else
		{
			SelectObject(hdc, offBrush);
		}
		this->red->draw(hdc);

		// Draw Yellow light
		if (yellowState)
		{
			SelectObject(hdc, yellowBrush);
		}
		else
		{
			SelectObject(hdc, offBrush);
		}
		this->yellow->draw(hdc);

		// Draw Green light
		if (greenState)
		{
			SelectObject(hdc, greenBrush);
		}
		else
		{
			SelectObject(hdc, offBrush);
		}
		this->green->draw(hdc);
	}

	void drawTLBox(HDC& hdc)
	{
		switch (dir)
		{
		case TLDir::VERTICAL:
			// Background frame
			SelectObject(hdc, outlineBrush);
			Rectangle(hdc,
			          posX - 5,
			          posY - 5,
			          posX + circleSize + (2 * spacing) + 5,
			          posY + (3 * circleSize) + (4 * spacing) + 5);
		// Background rectangle
			SelectObject(hdc, bgBrush);
			Rectangle(hdc,
			          posX,
			          posY,
			          posX + circleSize + (2 * spacing),
			          posY + (3 * circleSize) + (4 * spacing));
			break;
		case TLDir::HORIZONTAL:
			// Background frame
			SelectObject(hdc, outlineBrush);
			Rectangle(hdc,
			          posX - 5,
			          posY - 5,
			          posX + (3 * circleSize) + (4 * spacing) + 5,
			          posY + circleSize + (2 * spacing) + 5);
		// Background rectangle
			SelectObject(hdc, bgBrush);
			Rectangle(hdc,
			          posX,
			          posY,
			          posX + (3 * circleSize) + (4 * spacing),
			          posY + circleSize + (2 * spacing));
			break;
		}
	}

public:
	// Posistion is top left corner
	TrafficLight(TLState state, int posX, int posY, TLDir dir) :
		state(state),
		posX(posX),
		posY(posY),
		dir(dir)
	{
		this->red = new TLCircle(0, 0, circleSize);
		this->yellow = new TLCircle(0, 0, circleSize);
		this->green = new TLCircle(0, 0, circleSize);
	}

	void setPos(int x, int y)
	{
		posX = x;
		posY = y;
		switch (dir)
		{
		case TLDir::VERTICAL:
			red->setPos(posX + spacing, posY + spacing);
			yellow->setPos(posX + spacing, posY + (2 * spacing) + circleSize);
			green->setPos(posX + spacing, posY + (3 * spacing) + (2 * circleSize));
			break;
		case TLDir::HORIZONTAL:
			red->setPos(posX + spacing, posY + spacing);
			yellow->setPos(posX + (2 * spacing) + circleSize, posY + spacing);
			green->setPos(posX + (3 * spacing) + (2 * circleSize), posY + spacing);
			break;
		}
	}

	void changeState()
	{
		switch (state)
		{
		case TLState::STOP:
			{
				state = TLState::READY;
				break;
			}
		case TLState::READY:
			{
				state = TLState::GO;
				break;
			}
		case TLState::GO:
			{
				state = TLState::SLOW;
				break;
			}
		case TLState::SLOW:
			{
				state = TLState::STOP;
				break;
			}
		}
	}

	// Clean up resources, should be called when object is no longer needed
	void cleanUp()
	{
		delete red;
		delete yellow;
		delete green;
		DeleteObject(offBrush);
		DeleteObject(redBrush);
		DeleteObject(yellowBrush);
		DeleteObject(greenBrush);
		DeleteObject(outlineBrush);
		DeleteObject(bgBrush);
	}

	void draw(HDC& hdc)
	{
		// Store original brush
		HGDIOBJ hOrg = SelectObject(hdc, outlineBrush);

		// Draw the traffic light box
		drawTLBox(hdc);

		switch (state)
		{
		case TLState::STOP:
			{
				drawLights(hdc, true, false, false);
				break;
			}
		case TLState::READY:
			{
				drawLights(hdc, true, true, false);
				break;
			}
		case TLState::GO:
			{
				drawLights(hdc, false, false, true);
				break;
			}
		case TLState::SLOW:
			{
				drawLights(hdc, false, true, false);
				break;
			}
		}
		// Cleanup, set back original brush
		SelectObject(hdc, hOrg);
	}
};
