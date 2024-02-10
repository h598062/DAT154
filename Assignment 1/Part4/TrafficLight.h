#pragma once

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

	TLCircle(const int size) :
		top(0),
		bottom(size),
		left(0),
		right(size),
		size(size) {}

	void draw(const HDC hdc) const;
	void setPos(const int x, const int y);
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
	HBRUSH offBrush;
	HBRUSH redBrush;
	HBRUSH yellowBrush;
	HBRUSH greenBrush;
	HBRUSH bgBrush;
	HPEN tlOutlinePen;

	void drawLights(const HDC& hdc, const bool redState, const bool yellowState, const bool greenState) const;
	void drawTLBox(const HDC& hdc) const;

public:
	int stopPos;
	TrafficLight(const TLState state, const TLDir dir, const int stopPos);
	void setPos(const int x, const int y);
	void changeState();
	void draw(const HDC& hdc) const;
	bool canDrive() const;
	void cleanUp();
};

