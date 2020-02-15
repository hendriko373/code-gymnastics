#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "crossRef.hpp"

using std::map;     using std::string;
using std::vector;  using std::ifstream;
using std::cout;    using std::endl;

int main()
{
    ifstream input("input.txt");

    map<string, vector<int>> crossReference = crossRef(input);

    for (map<string, vector<int>>::const_iterator i = crossReference.begin();
            i != crossReference.end(); ++i) {
        cout << "'" << (*i).first << "'" << " occurs on line(s): ";

        vector<int>::const_iterator j = (*i).second.begin();
        cout << *j;
        ++j;

        while (j != (*i).second.end()) {
            cout << ", " << *j;
            ++j;
        }
        cout << endl;
    }

    return 0;
}
