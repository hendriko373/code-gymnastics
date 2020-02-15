#include <string>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <iterator>

using std::string;
using std::find_if;
using std::getline;
using std::cin;
using std::cout;

// isspace is overloaded, which is problematic when directly passed to a template
// function find_if. This auxilary function makes it clear for the compiler what
// version of isspace is to be called.
bool isSpace(char c)
{
    return isspace(c);
}

bool isNotSpace(char c)
{
    return !isspace(c);
}

template <class T>
void split(const string& s, T outIt)
{
    string::const_iterator i = s.begin();

    while (i != s.end()) {

        i = find_if(i, s.end(), isNotSpace);

        string::const_iterator j = find_if(i, s.end(), isSpace);

        if (i != s.end()) {
            *outIt = string(i, j);
            ++outIt;
        }

        i = j;
    }
}

int main()
{
    string input;
    while (getline(cin, input))
        split(input, std::ostream_iterator<string>(cout, "\n"));
    return 0;
}
