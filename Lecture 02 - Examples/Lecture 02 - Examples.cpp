#include <iostream>
#include <cstring> // May differ !!
using namespace std;
#pragma warning(disable : 4996)

void main1();
void main2();
void main3();
void main4();

int main()
{
    main1();
    //main2();
    //main3();
    //main4();
}

void main1()
{
    // Define a cstring and a char pointer
    char s[] = "HELLO WORLD HELLO TO LOLLY";
    char* pch = s;
    int cnt = 0;

    // Loop through the char array (C string) and count number of L chars
    while (*pch++)
        if (*pch == 'L')
            cnt++;
    // Display the result
    cout << "Number of Ls : " << cnt;
}

// Define a integer and a pointer to an integer
void main2()
{
    int x = 10;
    int y = 20;
    int* pi = 0;

    // Init the pointer via &, & gives the adress
    pi = &x;

    // Print its contents * gives pointer content (dereferece => get what it points to)
    cout << "The value of x is " << *pi << endl;

    pi = &y;
    cout << "The content of what pi points to is " << *pi;
}


void main3()
{
    char s[30];
    strcpy(s, "HELLO WORLD");
    cout << s << '\n';

    for (int i = 0; i < strlen(s); i++)
        cout << s[i] << ' ';
    cout << '\n';

    char s1[100];
    strcpy(s1, "  Learning C++\n");
    strcat(s, s1);
    cout << s;
}


int Sum(int* p, int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum = sum + *p;
        p = p + 1; // compact way to write: sum += *p++;
    }
    return sum;
}

void main4()
{
    // An array name is a constant pointer to the first element of the array.
    int a1[5] = {1, 4, 9, 16, 25}; // Anta a1 = 1000
    int a2[] = {1, 4, 9, 16, 25};

    int* p1; // Anta &p1 = 2000
    p1 = a1;

    cout << "Adr p1 :  " << p1 << endl;
    cout << "Adr &p1:  " << &p1 << endl;
    cout << "  p1[0]:  " << p1[0] << endl;

    // Call function
    int elements = sizeof(a1) / sizeof(int); // DO NOT USE sizeof(p1) -> its 4
    cout << "Sum a1: %d \n" << Sum(a1, elements);
}
