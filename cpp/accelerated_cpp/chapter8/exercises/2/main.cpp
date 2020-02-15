#include <iostream>
#include <vector>
#include <list>
#include "algorithm.hpp"

using std::vector;
using std::list;
using std::cout;
using std::endl;

bool greater_than_five(int a)
{
    return a > 5;
}

int main()
{
    vector<int> v;
    list<int> l;
    for (int i = 1; i != 11; ++i)
        v.push_back(i);

    for (vector<int>::const_iterator i = v.begin(); i != v.end(); ++i) {
        cout << *i << ' ';
    }
    cout << endl << endl;

    partition(v.begin(), v.end(), greater_than_five);

    for (vector<int>::const_iterator i = v.begin(); i != v.end(); ++i) {
        cout << *i << ' ';
    }
    cout << endl;

    return 0;
}
