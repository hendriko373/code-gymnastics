#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "crossRef.hpp"

using std::map;     using std::string;
using std::vector;  using std::ifstream;
using std::cout;    using std::endl;
using std::string;

int main()
{
    ifstream input("input.txt");

    map<string, vector<int>> crossReference = crossRef(input);

    for (map<string, vector<int>>::const_iterator i = crossReference.begin();
            i != crossReference.end(); ++i) {

        string s = "'" + (*i).first + "' occurs on line(s): ";
        cout << s;

        int count = 0;
        vector<int>::const_iterator j = (*i).second.begin();

        cout << *j;
        ++j;
        ++count;

        while (j != (*i).second.end()) {
            if (count % 3 == 0)
                cout << "\n" << string(s.size(),' ') << *j;
            else
                cout << ", " << *j;
            ++j;
            ++count;
        }
        cout << endl;
    }

    return 0;
}
