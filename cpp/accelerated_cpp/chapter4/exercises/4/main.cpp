#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using std::cin;		using std::cout;
using std::endl;		using std::setw;
using std::streamsize;
using std::vector;	using std::setprecision;

int main()
{
	double maxValue = 10;
	vector<double> values;
	vector<double> squares;

	for (double i=0.1; i <= maxValue ; i+=0.1){
		values.push_back(i);
		squares.push_back(i*i);
	}

	typedef vector<double>::size_type vecSz;
	vecSz size = values.size();
	
	streamsize digitsAfterComma = 2;
	streamsize widthValues = log10(maxValue) + 1 + digitsAfterComma;
	streamsize widthSquares = 2*log10(maxValue) + 1 + digitsAfterComma;

	streamsize prec = cout.precision();

	for (vecSz i=0; i != size; ++i){
		cout << setprecision(widthValues) << setw(widthValues)
			<< values[i] << "  "
			<< setprecision(widthSquares)	<< setw(widthSquares)
			<< squares[i]
			<< setprecision(prec) <<endl;
	}

	return 0;
}
