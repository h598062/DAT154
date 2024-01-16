#include <iostream>

int Myfunction(wchar_t* p)
{
					// The *p is a pointer to a wchar_t array, or a string 
	int i = 0;
	for (; *p; p++) // This loop wil increment the pointer posistion until it reaches a null terminator
	{
		i++;		// counts chars in the string / char array
	}
	return i;		// returns the amount of chars
}


int main(int argc, char* argv[])
{
	wchar_t buffer[25];
	std::wcout << L"Enter a word: ";
	std::wcin >> buffer;
	std::wcout << L"You typed: " << buffer << "\n";
	std::wcout << L"The string you typed is " << Myfunction(buffer) << " characters long" << "\n";
	return 0;
}
