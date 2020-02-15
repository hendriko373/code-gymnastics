#include <iostream>

using namespace std;

// argv[] is an array of pointer to char. argv then decays to a pointer to the
// first element of argv[]. argc is the number of elements in argv[]. The char
// argv[0] is the first element of the string by which the program is called.
// Subsequent chars argv[i] (i < argc) are the first elements of the strings
// that are the program arguments.
//
// The following program makes this clear by printing out the program arguments,
// i.e., the command line arguments.
int main(int argc, char* argv[])
{
    if (argc > 1) {
        cout << argv[1];
            // Remember that operator<< is overloaded: if ptr is of type char*,
            // it prints the string literal that ptr represents, instead of the
            // value of ptr, which is an address in memory.
    }

    for (int i = 2; i != argc; ++i)
        cout << " " << argv[i];

    cout << endl;
    return 0;
}
