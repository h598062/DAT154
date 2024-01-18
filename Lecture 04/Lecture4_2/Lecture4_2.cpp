#include <iostream>
#include <vector>

using namespace std;

typedef int DayTemp;
typedef std::vector<DayTemp> WeekTemp;

int main()
{
	WeekTemp weektemp;
	DayTemp mon = 10;
	DayTemp tue = 20;
	weektemp.push_back(mon);
	weektemp.push_back(tue);
	for (int i = 0; i < weektemp.size(); i++)
	{
		wcout << L"Daynr " << i << L"- t=" << weektemp.at(i) << endl;
	}
}
