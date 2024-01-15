// DEMO_L3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <string>
using namespace std;

#pragma warning(disable : 4996)

int main1();
int main2();
int main3();
int main4();
int main5();
int main()
{
	main1();
	//main2();
	//main3();
	//main4();
	//main5();
	
}


int main1()
{
	wchar_t s[] = L"Its a nice day, my house is on fire";
	wchar_t* p = s;
	int   n = 0;
	for (; *p != 0; p++)
	{
		if (*p == 'e')
			n++;
	}
	wcout << "Number of e's :" << n;
	return 0;
}


int main2()
{
    wchar_t s[] = L"Hello World";
    wchar_t* p = s;
    while (*p)
        wcout << *p++ << ',';
    wcout << endl;

    int tab[] = { 0,1,2,3,5,8,-1 };
    int* pi = tab;
    while (*pi != -1)
        wcout << *pi++ << ',';
    wcout << endl;
	return 0;
}



int main3()
{
	int  tab[4] = { 1,4,9,16 };
	int* p = tab; // same as *p=tab;

	wcout << tab[2] << endl;      // Array notation
	wcout << *(tab + 2) << endl;  // Pointer notation

	wcout << p[2] << endl;	    // Array notation
	wcout << *(p + 2) << endl;   // Pointer notation
	return 0;
}

int main4()
{
	int t[] = { 0,1,4,9,16,25,36,49,64,81,100 };
	int* pi = t;

	wcout << " Val : " << *pi << " Ptr Adr: " << pi << endl;
	pi = pi + 1;
	wcout << " Val : " << *pi << " Ptr Adr : " << pi << endl;
	return 0;
}



void DoSq(int *px)
{
	*px = *px  *  *px;
}

int main5()
{
	int x = 10;

	wcout << "Before x2 : " << x << endl;
	
	DoSq(&x);

	wcout << "After x2 : " << x << endl;
	return 0;
}






// Ex3F
//class Stud
//{
//public:
//	Stud(int nr) // : _nr(nr)
//	{
//		_nr = nr;
//	}
//	int _nr;
//};
//
//void Show(Stud* p)
//{
//	wcout << "Stud nr:" << p->_nr << endl;
//}
//
//void main()
//{
//	Stud* ps1 = new Stud(1);
//	Stud* ps2 = new Stud(2);
//
//	Show(ps1);
//	Show(ps2);
//
//	// REMEMBER TO DELETE THE STUDENTS
//	delete ps1;
//	delete ps2;
//
//}

//void main()
//{
//	Stud obj1(1); // Legal – obj on stack
//	Stud obj2(2);
//
//	Show(&obj1); // Use & since obj1 is an object
//	Show(&obj2);
//	 If obj on stack DO NOT DELETE
//}

//void SquareTwo(int* px, int* py) // Like ref in C# and Java
//{
//	*px = *px * *px;
//	*py = *py * *py;
//}
//
//
//int main()
//{
//	int x = 10;
//	int y = 20;
//
//	wcout << " x  =" << x << " y = " << y << endl;
//	SquareTwo(&x, &y);
//	wcout << " x2 = " << x << " y2= " << y << endl;
//
//}

//class Stud
//{
//public:
//	int nr;
//	wchar_t name[100];
//};
//void main() // A Complex Exampe
//{
//	Stud *as[100];
//	int is = 0;
//	while(true) {
//		int nr;
//		wcout <<  "Nr  : ";
//		cin >> nr; 
//		if (nr == -1)
//			break;
//
//		wchar_t name[100];
//		wcout <<  "Name : ";
//		cin >> name;
//	
//		Stud* ps = new Stud;
//		ps->nr = nr;
//		strcpy(ps->name, name);
//		as[is] = ps;
//		is++;
//	}
//
//	// Load students until studnr = -1
//	//	Enter nr
//	//  Enter name
//
//	// Display student report
//	wcout << "Student Report HVL" << endl;
//	for (int i = 0; i < is; i++)
//		wcout << "Nr : " << as[i]->nr << " Name :" << as[i]->name << endl;
//
//	// Clean up
//	for (int i = 0; i < is; i++)
//		delete as[i];
//}
//class Stud
//{
//public:
//	int nr;
//	wchar_t name[100];
//};
//void main()
//{
//	Stud* ap[100];
//	int is = 0;
//
//	while (true)
//	{
//		int nr;
//		wchar_t name[100];
//
//		wcout << "Nr   :";
//		cin >> nr;
//		if (nr == -1)
//			break;
//
//		wcout << "Name : ";
//		cin >> name;
//
//		Stud* ps = new Stud;
//		ps->nr = nr;
//		strcpy(ps->name, name);
//		ap[is] = ps;
//		is++;
//	}
//
//	wcout << endl << "Student Report" << endl;
//	for (int i=0; i < is; i++)
//		wcout << ap[i]->nr << "   " << ap[i]->name << endl;
//}


//class Stud
//{
//public:
//	int nr;
//	wchar_t name[100];
//};
//
//void main()
//{
//	Stud* ap[100];
//	int is = 0;
//
//	// Read nr, name and create student objects
//	while (true)
//	{
//		int nr;
//		wchar_t name[100];
//
//		wcout << L"Nr  :";
//		cin  >> nr;
//		if (nr == -1)
//			break;
//		wcout << L"Name :";
//		cin  >> name;
//
//		Stud* ps = new Stud();
//		ps->nr = nr;
//		strcpy(ps->name, name);
//		ap[is] = ps;
//		is++;
//	}
//	
//
//	// Make a report of students
//	wcout << endl << L"Student Lists" << endl;
//	for (int i = 0; i < is; i++)
//		wcout << ap[i]->nr << "  " << ap[i]->name << endl;
//
//	// Delete the students
//	for (int i = 0; i < is; i++)
//		delete ap[i];
//
//}









