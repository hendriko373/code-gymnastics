#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::string;
using std::endl;

int main(){
	// ask for the person's name
	cout << "Please enter your first name: ";

	// read the name
	string name;
	cin >> name;

	// build the message that we intend to write
	const string greeting = "Hello, " + name + "!";

	// the number of blanks surrounding the greeting
	int xpad;
	int ypad;
	cout << "What padding do you desire..." << endl;
	cout << "In the x-direction? ";
	cin >> xpad;
	cout << "In the y-direction? ";
	cin >> ypad;

	// total number of rows to write
	const int rows = ypad * 2 + 3;

	// total number of columns to write
	const string::size_type cols = greeting.size() + xpad * 2 + 2;

	// blank line
	// build the frame with greeting
	cout << endl;
	// invariant: there are written r rows
	for (int r = 0; r != rows; ++r){
		// write 1 row
		string::size_type c = 0;
		// invariant: there are written c characters in row r
		while (c != cols){
			// should we write the greeting?
			if (r == ypad + 1 && c == xpad + 1){
					cout << greeting;
					c += greeting.size();
			}
			else{
				// are we on the border?
				if (r == 0 || r == rows - 1 || c == 0 || c == cols - 1)
					cout << "*";
				else
					cout << " ";
				++c;
			}
		}
		cout << endl;
	}

	return 0;
}
