#include <iostream>
#include "string_list.hpp"

using namespace std;

int main()
{
    StringList l;

    l.pushBack("test");
    l.pushBack("what?");
    l.pushBack("hello");

    cout << l.getSize() << endl;
    for (StringList::Iterator i = l.begin();
            i != l.end(); ++i)
        cout << *i << endl;

    cout << endl;
    l.popFront();
    cout << l.getSize() << endl;
    for (StringList::Iterator i = l.begin();
            i != l.end(); ++i)
        cout << *i << endl;

    cout << endl;
    l.pushBack("new");
    StringList::Iterator i = l.begin();
    ++i;
    *i = string("middle");
    cout << l.getSize() << endl;
    for (StringList::Iterator i = l.begin();
            i != l.end(); ++i)
        cout << *i << endl;

    l.clearMemory();
    cout << l.getSize() << endl;

    return 0;
}
