#include "Windows.h"
#include "TrafficLight.h"

// TLCircle
void TLCircle::draw(const HDC hdc) const
{
	Ellipse(hdc, left, top, right, bottom);
}

void TLCircle::setPos(const int x, const int y)
{
	top = y;
	bottom = y + size;
	left = x;
	right = x + size;
}

// TrafficLight
void TrafficLight::drawLights(const HDC& hdc, const bool redState, const bool yellowState,
	const bool greenState) const
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

void TrafficLight::drawTLBox(const HDC& hdc) const
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

TrafficLight::TrafficLight(const TLState state, const TLDir dir, const int stopPos) :
		state(state),
		posX(0),
		posY(0),
		dir(dir),
		stopPos(stopPos)
{
	this->red = new TLCircle(circleSize);
	this->yellow = new TLCircle(circleSize);
	this->green = new TLCircle(circleSize);
}

void TrafficLight::setPos(const int x, const int y)
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

void TrafficLight::draw(const HDC& hdc) const
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

bool TrafficLight::canDrive() const
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

void TrafficLight::changeState()
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

void TrafficLight::cleanUp() const
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
