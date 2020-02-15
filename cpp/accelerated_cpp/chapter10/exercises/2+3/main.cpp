#include <iostream>
#include "median.hpp"

using namespace std;

int main()
{
    double numbers[] = {3, 5, 6, 7};
    double* const p = numbers;
    size_t nNumbers = sizeof(numbers)/sizeof(*numbers);
    cout << median<double>(p, p + nNumbers) << endl; 

    vector<double> vecNumbers {3, 5, 6, 7};
    cout << median<double>(vecNumbers.begin(), vecNumbers.end()) << endl; 

    cout << endl;
    for (vector<double>::const_iterator i = vecNumbers.begin();
            i != vecNumbers.end(); ++i)
        cout << *i << " ";
    cout << endl;

    return 0;
}
