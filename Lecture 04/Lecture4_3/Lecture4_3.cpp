#include <algorithm>
#include <iostream>
#include <vector>
#include <deque>

using namespace std;

void exVector()
{
	vector<int> vec;
	vec.push_back(5);
	vec.push_back(9);
	vec.push_back(11);
	for (int i = 0; i < vec.size(); i++)
	{
		wcout << vec.at(i) << endl;
	}
}

void exDeque()
{
	deque<int> deq;
	deq.push_back(5);
	deq.push_back(9);
	deq.push_back(11);
	for (int i = 0; i < deq.size();)
	{
		wcout << deq.front() << endl;
		deq.pop_front();
	}
}

void exIterator()
{
	vector<wstring> names = {
		L"Anne", L"Hege", L"Tiril", L"Silje", L"Linda", L"Isa",
		L"Astrild", L"Ariel"
	};
	for (vector<wstring>::iterator i = names.begin(); i < names.end(); i++)
	{
		wcout << *i << endl;
	}
	for (auto i = names.begin(); i < names.end(); i++)
	{
		wcout << *i << " " << i->length() << endl;
	}
}

void exSort()
{
	vector<wstring> names = {
		L"Anne", L"Hege", L"Tiril", L"Silje", L"Linda", L"Isa", L"Astrild", L"Ariel"
	};
	sort(names.begin(), names.end());
	for (vector<wstring>::iterator i = names.begin(); i < names.end(); i++)
	{
		wcout << *i << endl;
	}
}

bool comparebyLength(const wstring& a, const wstring& b)
{
	return a.length() < b.length();
}

void exSortWithCompare()
{
	vector<wstring> names = {L"Anne", L"Hege", L"Tiril", L"Silje", L"Linda", L"Isa", L"Astrild", L"Ariel"};
	sort(names.begin(), names.end(), comparebyLength);
	for (auto i = names.begin(); i < names.end(); i++)
	{
		wcout << *i << endl;
	}
}

class Stud
{
public:
	Stud(wstring name) : _name(name)
	{
	}

	wstring _name;
};

bool comparePointerContent(const Stud* ps1, const Stud* ps2)
{
	return ps1->_name < ps2->_name;
}

void exSortWithPointer()
{
	vector<Stud*> names = {
		new Stud(L"Anne"), new Stud(L"Hege"),
		new Stud(L"Bjarte"), new Stud(L"Anders"), new Stud(L"Berit"),
	};
	sort(names.begin(), names.end(), comparePointerContent);
	for (auto i = names.begin(); i < names.end(); i++)
	{
		auto ps = *i;
		wcout << ps->_name << " " << endl;
	}
}

void exSearch()
{
	vector<wstring> names = {L"Anne", L"Hege", L"Tiril", L"Silje", L"Linda", L"Isa", L"Astrild", L"Ariel"};
	// We need a sorted array to do a binary search
	sort(names.begin(), names.end());
	vector<wstring> searchWords = {L"Isa", L"Therese"};
	for (auto i = searchWords.begin(); i < searchWords.end(); i++)
	{
		if (binary_search(names.begin(), names.end(), *i))
		{
			wcout << *i << L" was found in the array" << endl;
		}
		else
		{
			wcout << *i << L" was NOT found in the array" << endl;
		}
	}
}

int main(int argc, char* argv[])
{
	wcout << "Vector example:" << "\n";
	exVector();
	wcout << "\n" << "Deque example:" << "\n";
	exDeque();
	wcout << "\n" << "Iterator example:" << "\n";
	exIterator();
	wcout << "\n" << "Sort example:" << "\n";
	exSort();
	wcout << "\n" << "Sort with compare example:" << "\n";
	exSortWithCompare();
	wcout << "\n" << "Sort with pointer objects example:" << "\n";
	exSortWithPointer();
	wcout << "\n" << "Search example:" << "\n";
	exSearch();
	
	return 0;
}
