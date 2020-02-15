#include <string>
#include <vector>
#include <iostream>
#include "functions.hpp"

using std::string;		using std::vector;
using std::cin;			using std::cout;
using std::endl;

int main()
{
    string input;
    cout << "Please enter a string, ending with ENTER:" << endl;
    getline(cin, input);
    cout << endl;

    vector<string> words = split(input);
    vector<string> wordsFrame = makeFrame(words);

    vector<string> concat = concatenateVer(words,wordsFrame);

    for (vector<string>::const_iterator it = concat.begin();
            it != concat.end(); ++it){
        cout << *it << endl;
    }

    return 0;
}
