#include <iostream>
#include <fstream>
#include "str.hpp"

using namespace std;

int main()
{
    Str name = "Hendrik";
    Str message = "Hello " + name;
    // Str message;
    message += "!";

    cout << message << endl;

    Str file = "test.txt";
    ofstream output;
    output.open(file.c_str(), ofstream::out | ofstream::trunc);
    output << "A swift test!";
    output.close();

    Str cmp1 = "word";
    Str cmp2 = "words";
    Str cmp3 = "apple";
    cout << (cmp1 < cmp2) << endl;
    cout << ("word" == cmp1) << endl;
    cout << (cmp1 <= cmp3) << endl;

    cout << endl;
    Str cond;
    if (!cond)
        cond = "newValue";
    if (cond)
        cout << cond << endl;
    
    return 0;
}
