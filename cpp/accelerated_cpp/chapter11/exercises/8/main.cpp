#include <iostream>
#include "list.hpp"

using namespace std;

int main()
{

    List<char> myList;
    myList.pushBack('a');
    myList.pushBack('b');
    myList.pushBack('c');
    myList.pushBack('d');
    myList.pushBack('e');

    for (List<char>::Iterator i = myList.begin(); i != myList.end(); ++i)
        cout << *i << " ";
    cout << endl;

    List<char>::Iterator it = myList.begin();
    ++it;
    List<char>::Iterator en = myList.end();
    --en;
    --en;

    myList.erase(it, en); 
    for (List<char>::Iterator i = myList.begin(); i != myList.end(); ++i)
        cout << *i << " ";
    cout << endl;

    List<char> myListTwo(10, 'X');
    List<char> myListThree = myListTwo;
    myListThree.pushBack('Y');

    for (List<char>::Iterator i = myListTwo.begin(); i != myListTwo.end(); ++i)
        cout << *i << " ";
    cout << endl;

    for (List<char>::Iterator i = myListThree.begin();
            i != myListThree.end(); ++i)
        cout << *i << " ";
    cout << endl;

    myListThree = myList;

    for (List<char>::Iterator i = myListThree.begin();
            i != myListThree.end(); ++i)
        cout << *i << " ";
    cout << endl;
    
    myListTwo.clear();

    for (List<char>::Iterator i = myListTwo.begin(); i != myListTwo.end(); ++i)
        cout << *i << " ";
    cout << endl;
    
    return 0;
}
