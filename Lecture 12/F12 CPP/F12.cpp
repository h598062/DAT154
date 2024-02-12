#include <iostream> 
#include <typeinfo>
using namespace std;
class Vehicle { virtual void x() {}};
class Car : public Vehicle { };
class Bike : public Vehicle { };

int main() {
	Vehicle* a[100];  //  [1020, 1080, 1100]

	int iv = 0, ch = 0, nCars = 0;
	do {
		wcout <<  L"1=Car, 2=Bike, 0=Quit: ";
		wcin  >> ch;
		if (ch == 1) a[iv++] = new Car();
		if (ch == 2) a[iv++] = new Bike();
	} while (ch);

	for (int i = 0; i < iv; i++) {
		Vehicle* pv = a[i];
		wcout << typeid(*pv).name() << endl;
		if (dynamic_cast<Car*>(pv))
			nCars++;
	}
	wcout << "Cars:" << nCars;
	for (int i = 0; i < iv; i++)
		delete a[i];
}
