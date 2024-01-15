#include <iostream>

using namespace std;

void Do2x(int* pi) // funksjonen endrer på verdien i pekeren
{
	*pi = *pi * 2;
}

void eks1()
{
	wcout << "Eks 1" << endl;
	int x = 10;
	int y = 33;
	int* py = &y;
	Do2x(&x);
	Do2x(py);
	wcout << "x * 2 = " << x << ", y * 2 = " << y << endl;
}

int MyStrLen(wchar_t* p)
{
	int n = 0;
	while (*p++)
		n++;
	return n;
}

void eks2()
{
	wcout << "Eks 2" << endl;
	wchar_t s[] = L"Hello World!";
	wcout << L"Len of " << s << L" is: " << MyStrLen(s) << endl;
}

void swap(int* px, int* py)
{
	int tmp = *px;
	*px = *py;
	*py = tmp;
}

void eks3()
{
	wcout << "Eks 3" << endl;
	int x = 2;
	int y = 100;

	wcout << "x = " << x << " y = " << y << endl;
	swap(&x, &y);
	wcout << "x = " << x << " y = " << y << endl;
}

void eks4()
{
	wcout << "Eks 4" << endl;
	int* p;
	// using the new keyword
	p = new int;
	*p = 2024;
	wcout << "Current Year: " << *p << endl;
	wcout << "Next    Year: " << *p + 1 << endl;
	// remember the delete keyword
	delete p;
}

int main(int argc, char* argv[])
{
	wcout << "Lecture 3 del 3" << endl;
	eks1();
	wcout << endl;
	eks2();
	wcout << endl;
	eks3();
	wcout << endl;
	eks4();
	wcout << endl;
	return 0;
}
