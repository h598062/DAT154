#include "framework.h"

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
	VERTICALFLIPPED,
	HORIZONTAL,
	HORIZONTALFLIPPED
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
	TLCircle(const int size) :
		top(0),
		bottom(0 + size),
		left(0),
		right(0 + size),
		size(size)
	{
	}

	// Draw the circle, remember to set brush color before calling this
	void draw(const HDC hdc) const
	{
		Ellipse(hdc, left, top, right, bottom);
	}

	// Updates position using top-left positioning
	void setPos(const int x, const int y)
	{
		top = y;
		bottom = y + size;
		left = x;
		right = x + size;
	}
};

//
// Expected width and height
// Horizontal: 190, 70
// Vertical:   70, 190
//
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
	HBRUSH bgBrush = CreateSolidBrush(RGB(50, 50, 50));

	HPEN tlOutlinePen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));

	// Draw lights on the traffic light
	void drawLights(const HDC& hdc, const bool redState, const bool yellowState, const bool greenState) const
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

	// draw the bg box surrounding the lights
	void drawTLBox(const HDC& hdc) const
	{
		const HGDIOBJ orgPen = SelectObject(hdc, tlOutlinePen);
		switch (dir)
		{
		case TLDir::VERTICAL:
		case TLDir::VERTICALFLIPPED:
			// Background rectangle
			SelectObject(hdc, bgBrush);
			Rectangle(hdc,
			          posX,
			          posY,
			          posX + circleSize + (2 * spacing),
			          posY + (3 * circleSize) + (4 * spacing));
			break;
		case TLDir::HORIZONTAL:
		case TLDir::HORIZONTALFLIPPED:
			// Background rectangle
			SelectObject(hdc, bgBrush);
			Rectangle(hdc,
			          posX,
			          posY,
			          posX + (3 * circleSize) + (4 * spacing),
			          posY + circleSize + (2 * spacing));
			break;
		}
		SelectObject(hdc, orgPen);
	}

public:
	// Create a traffic light, state is initial state
	TrafficLight(const TLState state, const TLDir dir) :
		state(state),
		posX(0),
		posY(0),
		dir(dir)
	{
		this->red = new TLCircle(circleSize);
		this->yellow = new TLCircle(circleSize);
		this->green = new TLCircle(circleSize);
	}

	// Updates the position of the traffic light, position is top-left based
	void setPos(const int x, const int y)
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
		case TLDir::VERTICALFLIPPED:
			green->setPos(posX + spacing, posY + spacing);
			yellow->setPos(posX + spacing, posY + (2 * spacing) + circleSize);
			red->setPos(posX + spacing, posY + (3 * spacing) + (2 * circleSize));
			break;
		case TLDir::HORIZONTALFLIPPED:
			green->setPos(posX + spacing, posY + spacing);
			yellow->setPos(posX + (2 * spacing) + circleSize, posY + spacing);
			red->setPos(posX + (3 * spacing) + (2 * circleSize), posY + spacing);
			break;
		}
	}

	// Changes the state of the traffic light to its next state
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
	void cleanUp() const
	{
		delete red;
		delete yellow;
		delete green;
		DeleteObject(offBrush);
		DeleteObject(redBrush);
		DeleteObject(yellowBrush);
		DeleteObject(greenBrush);
		DeleteObject(bgBrush);
	}

	// Draws the complete traffic light, should not make any external changes to brushes etc.
	void draw(const HDC& hdc) const
	{
		// Store original brush
		const HGDIOBJ hOrg = SelectObject(hdc, bgBrush);

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

	// True or false if a car can drive
	bool canDrive() const
	{
		bool result = false;
		switch (state)
		{
		case TLState::STOP:
		case TLState::READY:
			result = false;
			break;
		case TLState::GO:
		case TLState::SLOW:
			result = true;
			break;
		}
		return result;
	}
};
