#include <iostream>
#include <fstream>
#include "str.hpp"

using namespace std;

int main()
{
    Str name = "Hendrik";
    Str message = "Hello " + name;
    message += "!";

    cout << message << endl;

    Str file = "test.txt";
    ofstream output;
    output.open(file.c_str(), ofstream::out | ofstream::trunc);
    output << "A swift test!\n";
    output << "A second line.";
    output.close();

    Str cmp1 = "word";
    Str cmp2 = "words";
    Str cmp3 = "apple";
    cout << (cmp1 < cmp2) << endl;
    cout << ("word" == cmp1) << endl;
    cout << (cmp1 <= cmp3) << endl;
    cout << endl;

    Str::Iterator it = name.begin();
    *it = 'h';
    it += 3;
    *it = 'D';
    cout << name << endl;
    cout << endl;

    ifstream input("test.txt");
    Str out;
    getLine(input, out);
    cout << out;
    getLine(input, out);
    cout << " / " + out;
    cout << endl;
    
    return 0;
}
