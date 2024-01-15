#include <iostream>

using namespace std;

void eks1()
{
	wcout << "Eks 1" << endl;
	wchar_t s[] = L"Its a nice day, my house is on fire!!!!";
	int n = 0;

	for (wchar_t* p = s; *p != 0; p++)
	{
		if (*p == 'e')
			n++;
	}
	wcout << L"Number of e's: " << n << endl;
}

void eks2()
{
	wcout << "Eks 2" << endl;
	wchar_t s[] = L"Hello World!";
	wchar_t* p = s;
	while (*p)
		wcout << *p++ << ',';

	wcout << endl;

	int tab[] = {0, 1, 2, 4, 7, 9, -1};
	int* pi = tab;
	while (*pi != -1)
		wcout << *pi++ << ',';
	wcout << endl;
}

void eks3()
{
	wcout << "Eks 3" << endl;
	int tab[] = {0, 4, 8, 16, 20};
	int* p = tab;
	wcout << *p++ << endl;		// 0
	wcout << (*++p)++ << endl;	// 8
	wcout << *p << endl;		// 9
}

void eks4()
{
	wcout << "Eks 4" << endl;
	int tab[4] = {1, 4, 7, 19};
	int* p = tab;

	p++;							// Denne øker peker posisjon for de to nederste linjene
	wcout << tab[2] << endl;		// Array notation
	wcout << *(tab + 2) << endl;	// Same - Pointer notation

	wcout << p[2] << endl;			// Array notation
	wcout << *(p + 2) << endl;		// Same - Pointer notation
}

int main(int argc, char* argv[])
{
	wcout << "Lecture 3 del 2" << endl;
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
