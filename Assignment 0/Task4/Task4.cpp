#include <iostream>
using namespace std;

void BuyCar(int* pnr, int* pbuy)
{
	wcout << L"Enter nr: ";
	wcin >> *pnr;
	wcout << L"Enter price: ";
	wcin >> *pbuy;
}

void ListCars(int* pnr, int* pbuy, int* psell, int n)
{
	wcout << L"All cars:" << "\n";
	for (int i = 0; i < n; i++)
		wcout << L"Carnr: " << *(pnr + i) << L" Price: " << *(pbuy + i) << L" Sold: " << *(psell + i) << '\n';
}

void SellCar(int* pnr, int* psell)
{
	wcout << L"Enter nr: ";
	wcin >> *pnr;
	wcout << L"Enter price: ";
	wcin >> *psell;
}

void FindProfit(int* pbuy, int* psell, int n)
{
	int sum = 0;
	for (int i = 0; i < n; ++i)
	{
		sum += *(psell + i) - *(pbuy + i);
	}
	wcout << L"Current profit is " << sum << "\n";
}

void CleanupList(int* pnr, int* pbuy, int* psell, int* n)
{
	// finn alle biler der sellpris != 0 og nuller alle felt
	// gå gjennom liste fra høyre, flytt hver bil du finner til første ledige plass
	// inkrementer lokal var for neste lokasjon å lete fra
	int removed = 0;
	for (int i = 0; i < *n; ++i)
	{
		if (*(psell + i) != 0)
		{
			pbuy[i] = 0;
			psell[i] = 0;
			pnr[i] = 0;
			++removed;
		}
	}
	int lp = 0;
	for (int i = *n - 1; i > lp; --i) // n-1 fordi n er en "ledig" plass
	{
		if (*(pnr + i) != 0)
		{
			bool done = false;
			while (lp < i && !done)
			{
				if (*(pnr + lp) == 0)
				{
					*(pnr + lp) = *(pnr + i);
					*(pbuy + lp) = *(pbuy + i);
					*(psell + lp) = *(psell + i);
					*(pnr + i) = 0;
					*(pbuy + i) = 0;
					*(psell + i) = 0;
					done = true;
				}
				++lp;
			}
		}
	}
	*n -= removed;
}

int main()
{
	int carnr[1000];
	int buyprice[1000];
	int sellprice[1000];
	int choice = 0;
	int idx = 0;
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
			carnr[idx] = nr;
			buyprice[idx] = buy;
			sellprice[idx] = 0;
			idx++;
			wcout << L"Set car " << nr << L" to buy price " << buy << "\n";
			break;
		case 2: SellCar(&nr, &sell);
			i = 0;
			while (i < idx && carnr[i] != nr)
			{
				++i;
			}
			if (i < idx)
			{
				sellprice[i] = sell;
				wcout << L"Set car " << nr << L" to sold price " << sell << "\n";
			}
			else
			{
				wcout << L"Couldnt find car with number " << nr << "\n";
			}
			break;
		case 3: FindProfit(buyprice, sellprice, idx);
			break;
		case 4: ListCars(carnr, buyprice, sellprice, idx);
			break;
		case 5: CleanupList(carnr, buyprice, sellprice, &idx);
			break;
		default: __noop;
		}
	}
	while (choice != 0);
}
