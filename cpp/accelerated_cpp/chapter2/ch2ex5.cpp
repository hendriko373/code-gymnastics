#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main(){
	int xside;
	int yside;
	int choice;
	
	bool valid = false;
	// invariant: valid indicates if the choice is 1, 2 or 3
	while (valid == false){
		cout << "You want me to draw a square (1), rectangle (2) or triangle (3)? ";
		cin >> choice;
		if (choice != 1 && choice != 2 && choice != 3){
			cout << "Invalid choice" << endl;
		} else valid = true;
	}

	if (choice == 1){
		cout << "Out of how many *\'s should its side consist? ";
		cin >> xside;
		string spaces(xside - 2,' ');
		cout << endl;
		// draw the square
		// invariant: we have drawn r rows
		for (int r = 0; r != xside; ++r){
			int c = 0;
			// invariant: we have written c characters
			while (c != xside){
				if (r == 0 || r == xside - 1 || c == 0 || c == xside - 1){
					cout << "*";
					++c;
				} else{
					cout << spaces;
					c += spaces.size();
				}
			}
			cout << endl;
		}
	} else{
		if (choice == 2){
			cout << "Out of how many *\'s should its sides consist..." << endl;
			cout << "Its base? ";
			cin >> xside;
			cout << "Its height? ";
			cin >> yside;
			string spaces(xside - 2,' ');
			cout << endl;
			// draw the square
			// invariant: we have drawn r rows
			for (int r = 0; r != yside; ++r){
				int c = 0;
				// invariant: we have written c characters
				while (c != xside){
					if (r == 0 || r == yside - 1 || c == 0 || c == xside - 1){
						cout << "*";
					++c;
					} else{
						cout << spaces;
						c += spaces.size();
					}
				}
				cout << endl;
			}
		} else{
			cout << "Out of how many *\'s should its base consist?" << endl;
			cout << "The number must be odd and at least 3... ";
			cin >> xside;
			yside = xside/2 + 1;
			cout << endl;
			// draw the triangle
			int mid = (xside - 1)/2;
			// invariant: we have drawn r rows
			for (int r = 0; r != yside; ++r){
				int c = 0;
				// invariant: we have written c characters
				while (c != xside){
					if (r == yside - 1){
						cout << "*";
						++c;
					} else{
						if (c == mid - r || c == mid + r){
							cout << "*";
							++c;
						} else{
							cout << " ";
							++c;
						}
					}	
				}
				cout << endl;
			}
		}
	}
	return 0;
}




