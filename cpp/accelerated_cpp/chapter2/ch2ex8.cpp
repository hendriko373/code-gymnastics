#include <iostream>

using std::cout;
using std::endl;

int main(){
	
	int R = 1;
	// invariant: R = product_(k goes from 1 to i) k
	for (int i = 1; i != 9; ++i){
		R *= i + 1;
	}
	cout << R << endl;

	return 0;
}
