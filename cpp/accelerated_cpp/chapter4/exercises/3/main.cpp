#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using std::cin;		using std::cout;
using std::endl;	using std::setw;
using std::streamsize;
using std::vector;

int main()
{
    int maxValue = 1000;
    vector<int> values;
    vector<int> squares;

    for (int i=1; i != maxValue+1 ; ++i){
        values.push_back(i);
        squares.push_back(i*i);
    }

    typedef vector<int>::size_type vecSz;
    vecSz size = values.size();

    streamsize widthValues = log10(maxValue) + 1;
    streamsize widthSquares = 2*log10(maxValue) + 1;

    for (vecSz i=0; i != size; ++i){
        cout << setw(widthValues) << values[i] << "  "
            << setw(widthSquares) << squares[i] << endl;
    }

    return 0;
}
