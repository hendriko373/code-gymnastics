#include <vector>
#include <string>
#include <cctype>	// isspace
#include <algorithm>
#include <iterator>
#include "functions.hpp"

using std::vector;		using std::string;
using std::max;                 using std::back_inserter;
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

string::size_type computeMaxLength(const vector<string>& vecIn)
{
    string::size_type ret = 0;

    for (vector<string>::const_iterator it = vecIn.begin();
            it != vecIn.end(); ++it)
        ret = max(ret, (*it).size());

    return ret;
}

vector<string> makeFrame(const vector<string>& vecIn)
{
    vector<string> ret;
    string::size_type maxLength = computeMaxLength(vecIn);

    string border = string(maxLength + 4,'*');
    ret.push_back(border);

    for (vector<string>::const_iterator it = vecIn.begin();
            it != vecIn.end(); ++it)
        ret.push_back("* " + *it + string(maxLength - (*it).size(),' ') + " *");

    ret.push_back(border);

    return ret;
}

vector<string> concatenateVer(const vector<string>& top, const vector<string>& bottom)
{
    vector<string> ret(top.begin(), top.end());
    copy(bottom.begin(), bottom.end(), back_inserter(ret));

    return ret;
}

vector<string> concatenateHor(const vector<string>& left, const vector<string>& right)
{
    vector<string> ret;
    string::size_type widthLeft = computeMaxLength(left);

    vector<string>::const_iterator iterLeft = left.begin(),
        iterRight = right.begin();

    while (iterLeft != left.end() || iterRight != right.end()){

        string s;

        if (iterLeft != left.end()){
            s = *iterLeft + string(widthLeft - (*iterLeft).size(),' ');
            ++iterLeft;
        } else{
            s = string(widthLeft,' ');
        }

        if (iterRight != right.end()){
            s += *iterRight;
            ++iterRight;
        }

        ret.push_back(s);
    }
    return ret;
}

