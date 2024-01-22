#include <iostream>
#include <iterator>
#include <vector>
using namespace std;


#include <iostream>
using namespace std;

class Drink
{
public:
	virtual double Promille() = 0; // Pure function
	int _Alc = 0;				   // Can have member
};

class Beer : public Drink
{
public:
	Beer(int Alc) { _Alc = Alc; }

	virtual double Promille()
	{
		return (_Alc * 50) / 1000.0;  // KUN DEMO
	}
};

class WineGlass : public Drink
{
public:
	WineGlass(int Alc) { _Alc = Alc; }

	virtual double Promille()
	{
		return (_Alc * 30) / 1000.0;  // KUN DEMO
	}
};

class Juice : public Drink
{
public:
	virtual double Promille()
	{
		return 0;
	}
};

typedef vector<Drink*> V;
// IKKE BRUK DETTE PROGRAMMET TIL ANNET EN DEMO. FINNES SLIKE KALKULATORER PÅ NETTET SOM ER MYE BEDRE !!
void PolyMorphic()
{
	wcout << "PolyMorphic - Promille" << endl;

	V v = {new Beer(3), new Juice, new Beer(5), new WineGlass(12)};
	double promille = 0;
	for (V::iterator i = v.begin(); i < v.end(); i++)
	{
		Drink* pd = *i;
		wcout << typeid(*pd).name() << L" Pro: " << pd->Promille() << endl;
		promille += pd->Promille();
	}

	wcout << L"TotalPromille: " << promille << endl;

	for (V::iterator i = v.begin(); i < v.end(); i++)
	{
		Drink* pd = *i;
		delete pd;
	}
}
