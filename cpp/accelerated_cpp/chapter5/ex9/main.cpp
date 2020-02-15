#include <string>
#include <vector>
#include <iostream>
#include <cstdio>   // clearerr (stdin)
#include <cctype>

using std::string;      using std::vector;
using std::cout;        using std::cin;
using std::endl;        using std::istream;

vector<string> readWords(istream& is)
{
    vector<string> ret;

    if (is) {
        string s;
        while (is >> s)
            ret.push_back(s);

        is.clear();
        clearerr(stdin);
    } 
    return ret;
}

bool hasUpperCase(string s)
{
    bool ret = false;
    
    for (string::size_type i = 0; ret == false && i != s.size(); ++i) {
        if ( isupper(s[i]) )
            ret = true;
    }
    
    return ret;
}

int main()
{
    // Read words from cin and store them into input
    cout << "Please enter a list of words. End with EOL.\n" << endl;
    vector<string> input = readWords(cin);

    vector<string> noUpperCase;
    vector<string> withUpperCase;

    for (vector<string>::const_iterator i = input.begin();
            i != input.end(); ++i) {

        if ( hasUpperCase(*i) ) {
            withUpperCase.push_back(*i);
        } else {
            noUpperCase.push_back(*i);
        }
    }

    // Print output
    cout << "Words without uppercase letters:\n" << endl;
    for (vector<string>::const_iterator i = noUpperCase.begin();
            i != noUpperCase.end(); ++i)
        cout << *i << endl;
    cout << endl;

    cout << "Words with at least one uppercase letter:\n" << endl;
    for (vector<string>::const_iterator i = withUpperCase.begin();
            i != withUpperCase.end(); ++i)
        cout << *i << endl;
    cout << endl;
    
    return 0;
}
