#include <iostream>

using namespace std;

class Stud
{
public :
	Stud() { _nr = 0; }

	Stud(int nr) : _nr(nr)
	{
	}

	int _nr;
};

void Show(Stud* px)
{
	wcout << L"Studnr:" << px->_nr << endl;
}

void ex1()
{
	Stud* p1 = new Stud(1);
	Stud* p2 = new Stud(2);
	Show(p1);
	Show(p2);
	Show(new Stud(3)); // Legal, but pointer is lost... memory leak...
	// In C++, you must delete objects
	delete p2;
	delete p1;
}

void ex2()
{
	Stud obj1(1); // Legal - obj on stack
	Stud obj2(2);
	Show(&obj1);	// Use & since obj1 is an object
	Show(&obj2);
	// If obj on stack DO NOT DELETE
}

void Init(Stud* ps, int n)
{
	for (int id = 0; id < n; id++, ps++)
		ps->_nr = id + 1;
}

const int MAX = 10;

void ex3()
{
	Stud studarr[MAX];
	Init(studarr, MAX);
	for (int i = 0; i < MAX; i++)
		wcout << "Studnr: " << studarr[i]._nr << endl;
}

void ex4()
{
	Stud* tab[MAX];
	for (int i = 0; i < MAX; i++)
		tab[i] = new Stud(i + 1);
	for (int i = 0; i < MAX; i++)
		Show(tab[i]);
	// Cleanup
	for (int i = 0; i < MAX; i++)
		delete tab[i];
}

int main(int argc, char* argv[])
{
	wcout << "Example 1: new and delete keywords" << "\n";
	ex1();
	wcout << "\n" << "Example 2: object on stack" << "\n";
	ex2();
	wcout << "\n" << "Example 3: array with objects on stack" << "\n";
	ex3();
	wcout << "\n" << "Example 4: array with object pointers" << "\n";
	ex4();
	return 0;
}
