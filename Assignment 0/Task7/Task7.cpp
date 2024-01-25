#include <deque>
#include <iostream>
#include <vector>

using namespace std;

enum class Colour { RED, GREEN, BLUE };

class Car
{
public:
	Car(Colour colour) : _colour(colour)
	{
	}

	Colour _colour;
};

typedef deque<Car*> Garasje;

int main(int argc, char* argv[])
{
	Garasje garasje;

	bool exit = false;
	while (!exit)
	{
		wcout << L"Choose your action [1-5]:\n";
		wcout << L"1. Drive a red car into the garage\n";
		wcout << L"2. Drive a blue car into the garage\n";
		wcout << L"3. Drive a green car into the garage\n";
		wcout << L"4. Drive a car out of the garage\n";
		wcout << L"5. Quit\n";
		int valg;
		wcout << L"Choice: ";
		wcin >> valg;

		switch (valg)
		{
		case 1:
			{
				if (garasje.size() >= 5)
				{
					wcout << L"The garasje is full\n";
					break;
				}
				Car* redCar = new Car(Colour::RED);
				garasje.push_back(redCar);
				wcout << L"Red car drove into the garage\n";
				break;
			}
		case 2:
			{
				if (garasje.size() >= 5)
				{
					wcout << L"The garasje is full\n";
					break;
				}
				Car* blueCar = new Car(Colour::BLUE);
				garasje.push_back(blueCar);
				wcout << L"Blue car drove into the garage\n";
				break;
			}
		case 3:
			{
				if (garasje.size() >= 5)
				{
					wcout << L"The garasje is full\n";
					break;
				}
				Car* greenCar = new Car(Colour::GREEN);
				garasje.push_back(greenCar);
				wcout << L"Green car drove into the garage\n";
				break;
			}
		case 4:
			{
				if (garasje.empty())
				{
					wcout << "The garage is empty!\n";
					break;
				}
				Car* car = garasje.front();
				garasje.pop_front();
				wcout << L"A ";
				switch (car->_colour)
				{
				case Colour::RED: wcout << L"red";
					break;
				case Colour::GREEN: wcout << L"green";
					break;
				case Colour::BLUE: wcout << L"blue";
					break;
				}
				wcout << " car has left the garage\n";
				delete(car);
				break;
			}
		case 5:
			{
				exit = true;
				break;
			}
		default: break;
		}
		wcout << L"\n";
	}


	return 0;
}
