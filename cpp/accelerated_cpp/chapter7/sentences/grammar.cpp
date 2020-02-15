#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <fstream> 
#include <stdexcept>
#include <cstdlib>
#include "split.hpp"
#include "grammar.hpp"

using std::vector;  using std::string;
using std::map;     using std::ifstream;
using std::getline; using std::cout;
using std::endl;    using std::logic_error;
using std::domain_error;

Grammar readGrammar(ifstream& in)
{
    Grammar ret;
    string input;

    while (getline(in, input)) {
        vector<string> v = split(input);

        if (!v.empty())
            ret[v[0]].push_back(Rule(v.begin() + 1, v.end()));
    }
    return ret;
}

void writeGrammar(const Grammar& g)
{
    for (Grammar::const_iterator i = g.begin(); i != g.end(); ++i) {

        for (vector<Rule>::const_iterator j = (*i).second.begin();
                j != (*i).second.end(); ++j) {
            
            vector<string>::const_iterator k = (*j).begin();
            cout << (*i).first << " -- " << *k;

            ++k;
            while (k != (*j).end()) {
                cout << " " << *k;
                ++k;
            }
            cout << endl;
        }
    }
}

// returns random number in the range [0, n)
int nRand(int n)
{
    if (n <= 0 || n > RAND_MAX)
        throw domain_error("Argument to nRand is out of range");

    int bucketSize = RAND_MAX / n;
    
    int r;
    
    do {
        r = rand()/bucketSize;
    } 
    while (r >= n);

    return r;
}

bool isCategory(const string& s)
{
    return s.size() > 2 && s[0] == '<' && s[s.size() - 1] == '>';
}

void generateSentenceAux(const Grammar& g, const string& s, vector<string>& v)
{
    if (!isCategory(s))
        v.push_back(s);
    else {
        Grammar::const_iterator sEntry = g.find(s);     
        if (sEntry == g.end())
            throw logic_error("Category does not exist.");

        const vector<Rule>& sRules = (*sEntry).second;
        const Rule& sRule = sRules[nRand(sRules.size())];

        for (vector<string>::const_iterator i = sRule.begin();
                i != sRule.end(); ++i)
            generateSentenceAux(g, *i, v);
    }
    return;
}

vector<string> generateSentence(const Grammar& g)
{
    vector<string> ret;
    generateSentenceAux(g, "<sentence>", ret);
    return ret;
}
