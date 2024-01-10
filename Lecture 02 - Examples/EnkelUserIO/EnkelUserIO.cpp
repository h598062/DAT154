#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    int x, y;

    wcout << L"First number: ";
    wcin >> x;
    wcout << L"Seconf number: ";
    wcin >> y;
    int sum = x + y;
    wcout << L"Sum is: " << sum << endl;
}
