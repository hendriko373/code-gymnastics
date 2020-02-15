#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <fstream>
#include "crossRef.hpp"

using std::vector;      using std::string;
using std::find_if;     using std::map;
using std::ifstream;    using std::getline;
using std::find;

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

// Returns key-value pairs where the key is a word and value a vector of int, which
// contains the line numbers on which the key (word) appears
map<string, vector<int>>
        crossRef(ifstream& in, vector<string> findWords(const string&))
{
    map<string, vector<int>> ret;
    string line;
    int lineNo = 0;

    while (getline(in, line)) {
        ++lineNo;

        vector<string> words = findWords(line);

        for (vector<string>::const_iterator i = words.begin();
                i != words.end(); ++i) {
            
            if (find(ret[*i].begin(), ret[*i].end(), lineNo) == ret[*i].end())
                ret[*i].push_back(lineNo);
        }
    }
    return ret;
}
