#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "crossRef.hpp"

using std::map;         using std::string;
using std::vector;      
using std::cout;        using std::endl;
using std::ifstream;    using std::to_string;

int main()
{
    ifstream input("input.txt");

    // key = word
    // value = lines of occurences
    const map<string, vector<int>> crossReference = crossRef(input);

    // key = number of different occurences
    // value = words with key occurences
    map<int, vector<string> > occurenceGroups;

    for (map<string, vector<int>>::const_iterator i = crossReference.begin();
            i != crossReference.end(); ++i)
        occurenceGroups[(*i).second.size()].push_back((*i).first);

    for (map<int, vector<string>>::const_iterator i = occurenceGroups.begin();
            i != occurenceGroups.end(); ++i) {

        for (vector<string>::const_iterator j = (*i).second.begin();
                j != (*i).second.end(); ++j) {

            vector<int> lines = crossReference.find(*j)->second;
            cout << "'" << *j << "' occurs on line(s): ";

            vector<int>::const_iterator k = lines.begin();
            cout << *k;
            ++k;

            while (k != lines.end()) {
                cout << ", " << *k;
                ++k;
            }

            cout << endl;
        }
    }

    return 0;
}
