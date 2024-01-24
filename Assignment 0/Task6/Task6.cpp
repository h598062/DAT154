#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef vector<wstring> Words;

int main(int argc, char* argv[])
{
    wcout << L"Please write words to be sorted, one word per line. Send an empty line to stop.\n";
	Words words;
    while (true)
    {
    	wstring input;
    	getline(wcin, input);
	    if (input.empty())
	    {
		    break;
	    }
    	// wcout << L"You sent: " << input << L"\n";
	    words.push_back(input);
    }

    sort(words.begin(), words.end());
	wcout << L"Sorted alpabetically:\n";
	for (Words::iterator i = words.begin(); i < words.end(); ++i)
	{
		wcout << *i << L"\n";
	}

	return 0;
}
