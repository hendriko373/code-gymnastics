#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include "url.hpp"

using std::vector;      using std::string;
using std::find_if;     using std::find;
using std::search;

bool isNotUrlCharacter(char c)
{
    static const string urlChars = "~;/?:@=&$-_.+!*'(),";
    return !(isalnum(c) ||
                find(urlChars.begin(), urlChars.end(), c) != urlChars.end());
}

string::const_iterator start_url(string::const_iterator b,
                                    string::const_iterator e)
{
    static const string sep = "://";

    typedef string::const_iterator strConstIt;
    strConstIt i = b;   // i will denote the first char of a found sep

    while ((i = search(i, e, sep.begin(), sep.end())) != e) {

        if (i != b && i + sep.size() != e) {
            strConstIt start = i;

            while (start != b && isalpha(start[-1]))
                --start;

            if (start != i && !isNotUrlCharacter(i[sep.size()])) {
                return start;
            }
        }
        // if the found sep is not part of a legal url we advance our search
        // after this sep
        i += sep.size();
    }
    return e;
}

string::const_iterator end_url(string::const_iterator b,
                                string::const_iterator e)
{
    return find_if(b, e, isNotUrlCharacter);
}

vector<string> findUrls(const string& s)
{
    vector<string> ret;
    typedef string::const_iterator strConstIt;

    strConstIt b = s.begin(), e = s.end();

    // look through the entire input
    while (b != e) {

        b = start_url(b, e);

        if (b != e) {
            strConstIt end = end_url(b, e);
            ret.push_back(string(b, end));
            b = end;
        }
    }
    return ret;
}
