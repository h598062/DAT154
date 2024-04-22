#include <iostream>

static void X2(int *pi)  { *pi = *pi * 2; }
static void X3(int *pi ) { *pi = *pi * 3; }

int main()
{
  // A simple function pointer assigned to lambda
  void (*pf) (int* px) = X2;
  void (*pf1) (int* px) = [](int* p) { *p = *p * 2; }; // Newer compilers lambda
  auto pf3 = X2;                                     // Newer auto
  auto pf2 = [](int* p) { *p = *p + 2; };            // Newer auto and lambda
 

  int x = 2;   
  pf(&x);   // Call via function pointer
  std::wcout << L"X er " << x << std::endl;

  // Reassigning ok
  pf = X3;
  pf(&x);
  std::wcout << L"X er " << x << std::endl;

  // Array of function pointers
  void (*apf[2]) (int *px);
  apf[0] = X2;
  apf[1] = X3;
  int x2 = 3;
  for (auto pf : apf) // Same as forach in C#
    pf(&x2);

  std::wcout << "X er " << x2 << std::endl;
}

