#include <vector>
#include <string>
#include <cctype>	// isspace
#include <algorithm>
#include "functions.hpp"

using std::vector;		using std::string;
using std::max;

vector<string> split(const string& str)
{
    vector<string> ret;

    typedef string::size_type StrSz;
    StrSz i = 0;

    // invariant: we have processed chars [orig val i, i) of str
    while (i != str.size()){

        // invariant: chars [orig val i, i) of str are whitespaces
        while (i != str.size() && isspace(str[i]))
            ++i;

        StrSz j = i;

        // invariant: none of the chars [i,j) of str are whitespaces
        while (j != str.size() && !isspace(str[j]))
            ++j;

        if (i != j){
            ret.push_back(str.substr(i,j-i));
            i = j;
        }	
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
    ret.insert(ret.end(), bottom.begin(), bottom.end());
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

