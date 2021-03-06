#include <iostream>
#include <iomanip>
#include <vector>

using std::cin;		using std::cout;
using std::endl;		using std::setw;
using std::streamsize;
using std::vector;

int main()
{
	vector<int> values;
	vector<int> squares;

	for (int i=1; i != 101; ++i){
		values.push_back(i);
		squares.push_back(i*i);
	}

	typedef vector<int>::size_type vecSz;
	vecSz size = values.size();

	for (vecSz i=0; i != size; ++i){
		cout << setw(3) << values[i]
			<< setw(7) << squares[i] << endl;
	}

	return 0;
}
