
#include <iostream>

int main(int argc, char* argv[])
{
    wchar_t buffer[25];
    std::wcout << L"Enter a word: ";
    std::wcin >> buffer;
    std::wcout << L"You typed: " << buffer << "\n";

    return 0;
}
