#pragma once
#include "Car.h"
#include "framework.h"

class TrafficSim
{
private:
	std::deque<Car*> northCars;
	std::deque<Car*> westCars;
	
	int lightstate = 0;
	int pN = 100;
	int pW = 100;
	int XRes = 0;
	int YRes = 0;
	int normalizeSpawnrate(int value);
	void doMove(std::deque<Car*>::iterator start, std::deque<Car*>::iterator end, int light);
	void drawRoad(HDC hdc, const RECT * dimensions, const POINT * origin) const;
	void drawRoadSurface(HDC hdc, const RECT* dimensions, const POINT* origin) const;
	void drawLight(HDC hdc, POINT position, char direction = 'n') const;
	void drawChances(HDC hdc, const POINT * origin) const;
public:
	TrafficSim();
	void Start(HWND hWnd);
	void Draw(HDC hdc, HWND hWnd) const;
	void SpawnCars(HWND hWnd);
	void MoveCars(HWND hWnd);
	void NextLightstate(HWND hWnd);
	void ChangeSpawnrate(int value, char direction);
	void SetSpawnrate(int value, char direction);
	const int& GetSpawnrate(const char& direction) const;

};

