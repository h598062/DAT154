#pragma once

#include "Windows.h"

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

	TLCircle(const int size) :
		top(0),
		bottom(size),
		left(0),
		right(size),
		size(size)
	{
	}

	void draw(const HDC hdc) const;
	void setPos(const int x, const int y);
};

//
// Expected width and height
// Horizontal: 190, 70
// Vertical:   70, 190
//
class TrafficLight
{
	TLState state;
	TLDir dir;
	const int spacing = 10;
	const int circleSize = 50;

	TLCircle* red;
	TLCircle* yellow;
	TLCircle* green;

	// Draw lights on the traffic light
	void drawLights(const HDC& hdc, const bool redState, const bool yellowState, const bool greenState) const;
	// draw the bg box surrounding the lights
	void drawTLBox(const HDC& hdc) const;

public:
	int posX;
	int posY;
	int stopPos;
	// Create a traffic light, state is initial state
	TrafficLight(const TLState state, const TLDir dir, const int stopPos);
	// Updates the position of the traffic light, position is top-left based
	void setPos(const int x, const int y);
	// Changes the state of the traffic light to its next state
	void changeState();
	// Draws the complete traffic light, should not make any external changes to brushes etc.
	void draw(const HDC& hdc) const;
	// True or false if a car can drive
	bool canDrive() const;
	// Clean up resources, should be called when object is no longer needed
	void cleanUp() const;
};
