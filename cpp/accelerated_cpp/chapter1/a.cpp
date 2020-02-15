// ask for the person's name
#include <iostream>
#include <string>

int main()
{
	// ask for the person's name
	std::cout << "Please enter your first name: ";

	// read the name
	std::string name;
	std::cin >> name;

	// build the message that we intend to write
	const std::string greeting = "Hello, " + name + "!";

	const std::string spaces(greeting.size(),' ');
	const std::string second = "* " + spaces + " *";
	const std::string first(second.size(),'*');

	// write a greeting
	std::cout << std::endl;
	std::cout << first << std::endl;
	std::cout << second << std::endl;
	std::cout << "* " << greeting << " *" << std::endl;
	std::cout << second << std::endl;
	std::cout << first << std::endl;	

	return 0;
}
