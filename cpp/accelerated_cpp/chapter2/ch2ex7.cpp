#include <iostream>

using std::cout;
using std::endl;

int main(){
	// invariant: we have written 10 - i numbers
	for(int i = 10; i != -6; --i){
		cout << i << endl;
	}
	return 0;
}
