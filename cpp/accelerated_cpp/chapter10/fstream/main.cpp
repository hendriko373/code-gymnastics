#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
    int nFails = 0;
    for (int i = 1; i != argc; ++i) {
        ifstream in(argv[i]);
        if (in) {
            string s;
            while (getline(in, s))
                cout << s << endl;
        } else {
            cerr << "Error: File not found: " << argv[i] << endl;
            ++nFails;
        }
    }
    return nFails;
}
