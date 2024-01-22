#include <iostream>
using namespace std;
#pragma warning(disable : 4996)

class Stud
{
public:
	void* _buffer = 0; // void* is typeless. Convert if you know the type.
	int size = 0;

	Stud(const wchar_t str[])
	{
		size = (wcslen(str) + 1) * sizeof(wchar_t);
		_buffer = malloc(size);
		memcpy(_buffer, str, size);
	}

	Stud(const void* bitmap)
	{
	} // Future, large ammounts of data

	wchar_t* GetString()
	{
		return (wchar_t*)_buffer;
	}

	~Stud()
	{
		free(_buffer);
	}
};

void VoidPointers()
{
	wcout << "Void Pointer Demo" << endl;
	Stud* ps1 = new Stud(L"I am the student Richard");
	wcout << ps1->GetString() << endl;
	delete ps1;
}

void Casting()
{
	int code = (int)L'A';
	// Some value
	wcout << code << endl;
	int x = 10, y = 3;

	// Error if we dont cast
	double d = ((double)x) / y;
	wcout << L"Uten cast : " << x / y << L" Med cast:" << (double)x / y << endl;
}
