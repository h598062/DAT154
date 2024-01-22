#include <iostream>
#include <iterator>
#include <list>
using namespace std;

#pragma warning(disable : 4996)

class Stud
{
public:
	int nr;
	wchar_t name[100];
};

void StudentReport() // A Complex Exampe
{
	Stud* as[100];
	int is = 0;

	wcout << L"Student report program" << endl;

	wcout << L"Tast inn Nr og Navn for student. Nr = -1 for avslutt." << endl;
	while (true)
	{
		int nr;
		wcout << L"Nr: ";
		wcin >> nr;
		if (nr == -1)
			break;

		wchar_t name[100];
		wcout << "Name: ";
		wcin >> name;

		Stud* ps = new Stud;
		ps->nr = nr;
		wcscpy(ps->name, name);
		as[is] = ps;
		is++;
	}

	// Load students until studnr = -1

	// Display student report
	wcout << endl << L"Student Report HVL" << endl;
	for (int i = 0; i < is; i++)
		wcout << L"Nr: " << as[i]->nr << L" Name: " << as[i]->name << endl;

	// Clean up
	for (int i = 0; i < is; i++)
		delete as[i];
}
