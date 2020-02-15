#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main(){

	int x;
	int y;

	cout << "Please enter two integral numbers." << endl;
	cout << "Number 1: ";
	cin >> x;
	cout << "Number 2: ";
	cin >> y;

	if (x > y){
		cout << "The biggest number is " << x << endl;
	} else{
		cout << "The biggest number is " << y << endl;
	}
	
	return 0;
}
