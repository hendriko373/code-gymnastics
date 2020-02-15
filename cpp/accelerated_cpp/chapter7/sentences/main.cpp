#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include "grammar.hpp"

using std::ifstream;    using std::string;
using std::vector;      using std::cout;
using std::endl; 

int main()
{
    ifstream input("grammar.txt");

    Grammar grammar = readGrammar(input);

    srand(time(0));
    vector<string> sentence = generateSentence(grammar);

    vector<string>::const_iterator i = sentence.begin();
    if (!sentence.empty()) {
        cout << *i;
        ++i;
    }

    while (i != sentence.end()) {
        cout << " " << *i;
        ++i;
    }
    cout << endl;

    return 0;
}
