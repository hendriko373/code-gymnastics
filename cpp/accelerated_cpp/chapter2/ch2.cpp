#include <iostream>
#include <string>

int main(){
	// ask for the person's name
	std::cout << "Please enter your first name: ";

	// read the name
	std::string name;
	std::cin >> name;

	// build the message that we intend to write
	const std::string greeting = "Hello, " + name + "!";

	// the number of blanks surrounding the greeting
	int pad;
	std::cout << "What padding do you desire? ";
	std::cin >> pad;

	// total number of rows to write
	const int rows = pad * 2 + 3;

	// total number of columns to write
	const std::string::size_type cols = greeting.size() + pad * 2 + 2;

	// build the frame with greeting
	// blank line
	std::cout << std::endl;
	int r = 0;
	// invariant: there are written r rows
	while (r != rows){
		// write 1 row
		std::string::size_type c = 0;
		// invariant: there are written c characters in row r
		while (c != cols){
			if (r == 0 || r == rows - 1 || c == 0 || c == cols - 1){
				std::cout << "*";
				++c;
			}
			else{
				if (r == pad + 1 && c == pad +1){
					std::cout << greeting;
					c += greeting.size();
				}
				else{
					std::cout << " ";
					++c;
				}
			}
		}
		std::cout << std::endl;
		++r;
	}

	return 0;
}
