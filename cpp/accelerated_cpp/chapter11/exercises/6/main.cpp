#include <iostream>
#include "vec.hpp"

using namespace std;

int main()
{

    Vec<int> numbers; 
    numbers.pushBack(1);
    numbers.pushBack(2);
    numbers.pushBack(3);
    numbers.pushBack(4);
    numbers.pushBack(5);
    numbers.pushBack(6);

    for (Vec<int>::Iterator i = numbers.begin(); i != numbers.end(); ++i)
        cout << *i << " ";
    cout << endl << endl;

    cout << *numbers.erase(numbers.begin() + 1, numbers.begin() + 3) << endl;

    for (Vec<int>::Iterator i = numbers.begin(); i != numbers.end(); ++i)
        cout << *i << " ";
    cout << endl;

    numbers.clear();
    numbers.pushBack(9);
    
    for (Vec<int>::Iterator i = numbers.begin(); i != numbers.end(); ++i)
        cout << *i << " ";
    cout << endl;

    return 0;
}
