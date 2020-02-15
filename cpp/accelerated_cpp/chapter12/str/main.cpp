#include <iostream>
#include "str.hpp"

using namespace std;

int main()
{
    Str name = "Hendrik";
    Str message = "Hello " + name;
    message += "!";

    cout << message << endl;
    
    return 0;
}
