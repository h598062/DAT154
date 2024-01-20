#include <iostream>
using namespace std;

class Car
{
public :
	Car()
	{
		_nr = 0;
		_price = 0;
		_sold = 0;
	}

	Car(int nr, int price) : _nr(nr), _price(price)
	{
		_sold = 0;
	}

	Car(int nr, int price, int sold) : _nr(nr), _price(price), _sold(sold)
	{
	}

	int _nr;
	int _price;
	int _sold;
};

void BuyCar(int* pnr, int* pbuy)
{
	wcout << L"Enter nr: ";
	wcin >> *pnr;
	wcout << L"Enter price: ";
	wcin >> *pbuy;
}

void ListCars(Car** cars, int n)
{
	wcout << L"All cars:" << "\n";
	for (int i = 0; i < n; i++)
		wcout << L"Carnr: " << cars[i]->_nr
			<< L" Price: " << cars[i]->_price
			<< L" Sold: " << cars[i]->_sold << '\n';
}

void SellCar(int* pnr, int* psell)
{
	wcout << L"Enter nr: ";
	wcin >> *pnr;
	wcout << L"Enter price: ";
	wcin >> *psell;
}

void FindProfit(Car** cars, int n)
{
	int sum = 0;
	for (int i = 0; i < n; ++i)
	{
		sum += cars[i]->_sold - cars[i]->_price;
	}
	wcout << L"Current profit is " << sum << "\n";
}

void CleanupList(Car** cars, int* n)
{
	// Gå gjennom liste fra venstre, finn alle biler der sellpris != 0 
	// gå gjennom liste fra høyre, flytt hver bil du finner som ikke er solgt til den solgte bilen i steget før sin pos 
	// inkrementer lokal var for neste lokasjon å lete fra

	int removed = 0;
	int k = *n - 1;
	for (int i = 0; i < *n; ++i)
	{
		if (cars[i]->_sold != 0)
		{
			++removed;
			delete cars[i];
			bool done = false;
			while (k > i && !done)
			{
				if (cars[k]->_sold == 0)
				{
					cars[i] = cars[k];
					done = true;
				}
				--k;
			}
		}
	}
	*n -= removed;
}

int main()
{
	Car* cars[1000];

	cars[0] = new Car(5, 1000, 1100);
	cars[1] = new Car(8, 420, 0);
	cars[2] = new Car(1, 600, 550);

	int choice = 0;
	int idx = 3;
	do
	{
		wcout << '\n' << L"List of choices" << '\n';
		wcout << L"1 Buy a car" << '\n';
		wcout << L"2 Sell a car" << '\n';
		wcout << L"3 Find the profit" << '\n';
		wcout << L"4 List all the cars" << '\n';
		wcout << L"5 Cleanup list (remove sold cars)" << '\n';
		wcout << L"0 Quit" << '\n';
		wcout << L"Choice: ";
		wcin >> choice;
		wcout << "\n";
		int nr, buy, sell, i;
		switch (choice)
		{
		case 1: BuyCar(&nr, &buy);
			cars[idx] = new Car(nr, buy);
			idx++;
			wcout << L"Set car " << nr << L" to buy price " << buy << "\n";
			break;
		case 2: SellCar(&nr, &sell);
			i = 0;
			while (i < idx && cars[i]->_nr != nr)
			{
				++i;
			}
			if (i < idx)
			{
				cars[i]->_sold = sell;
				wcout << L"Set car " << nr << L" to sold price " << sell << "\n";
			}
			else
			{
				wcout << L"Couldnt find car with number " << nr << "\n";
			}
			break;
		case 3: FindProfit(cars, idx);
			break;
		case 4: ListCars(cars, idx);
			break;
		case 5: CleanupList(cars, &idx);
			break;
		default: __noop;
		}
	}
	while (choice != 0);
}
