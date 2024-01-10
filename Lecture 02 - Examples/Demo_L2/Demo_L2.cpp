#include <iostream>
#include <cstring> // May differ !!

using namespace std;

int main()
{
    // Define a integer and a pointer to an integer
    int x = 10;
    int y = 20;
    int *pi = 0;

    // Init the pointer via &, & gives the adress
    pi = &x;

    // Print its contents * gives pointer content (dereferences => get what it points to)
    cout << "The value of x is " << *pi << endl;

    pi = &y;
    cout << "The content of what pi points to is " << *pi;
    cout << "pi without * " << pi;
}
