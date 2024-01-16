
#include <iostream>

int CountDoubleChars(wchar_t* pch)
{
    if (!*pch)
    {
        return 0;
    }
    int doubleChars = 0;
    wchar_t prevC = *pch;
    ++pch;
    while (*pch)
    {
        if (prevC == *pch)
        {
            ++doubleChars;
        }
        prevC = *pch;
        ++pch;
    }
    return doubleChars;
}

int main(int argc, char* argv[])
{
    // wchar_t s[] = L"Ammount of summers drummers - ";
    wchar_t s[] = L"";
    std::wcout << s << L" number of doublechars : " << CountDoubleChars(s);
    return 0;
}
