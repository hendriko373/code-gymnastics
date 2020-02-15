#include <vector>
#include <string>
#include <algorithm>

using std::vector;  using std::string;
using std::find_if;

bool isSpace(char c)
{
    return isspace(c);
}

bool isNotSpace(char c)
{
    return !isspace(c);
}

vector<string> split(const string& str)
{
    vector<string> ret;

    string::const_iterator i = str.begin();

    while (i != str.end()){

        // ignore blanks
        i = find_if(i, str.end(), isNotSpace);

        // find end of word
        string::const_iterator j = find_if(i, str.end(), isSpace);

        // push word on to the end of ret
        if (i != str.end())
            ret.push_back(string(i, j));

        i = j;
    }
    return ret;
}
