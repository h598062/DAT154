#include <iostream>

using namespace std;

void eks1()
{
	wcout << "Eks 1" << endl;
	int a = 2;
	int b = 3;
	int* p = &a;
	wcout << "*p=" << *p << endl;
	p = &b;
	wcout << "*p=" << *p << endl;
}

void eks2()
{
	wcout << "Eks 2" << endl;
	int x = 10, y = 30;
	int* pi = &x;

	wcout << "x=" << x << ", y=" << y << endl; // 10, 30
	*pi = 20;
	wcout << "x=" << x << ", y=" << y << endl; // 20, 30

	wcout << "*pi=" << *pi << endl; // *pi=20
	pi = &y;
	wcout << "*pi=" << *pi << endl; // *pi=30
}

void eks3()
{
	wcout << "Eks 3" << endl;
	int t[] = {23, 87, 35, 43, 43, 12, 68, 32, 76};
	int* pi = t;
	wcout << "Val: " << *pi << " Ptr addr: " << pi << endl;
	pi++;
	wcout << "Val: " << *pi << " Ptr addr: " << pi << endl;
}

int main(int argc, char* argv[])
{
	wcout << "Lecture 3 del 1" << endl;
	eks1();
	wcout << endl;
	eks2();
	wcout << endl;
	eks3();

	return 0;
}
