#include <iostream>
#include <vector>
#include <string>

using std::cin;		using std::cout;
using std::endl;		using std::string;
using std::vector;

int main(){

	vector<string> students;
	vector<double> grades;
	string name;
	double midterm, finalterm, hw1, hw2;

	cout << "Please enter a student's name: " ;

	// invariant 1: students contains the names of the students read in so far
	// invariant 2: grades contains the grades of the students read in so far
	//		and students and grades are in sync, i.e., the same index refers to
	//		the same student
	while (cin >> name){
		students.push_back(name);

		cout << "Please enter " + name + "'s midterm, "
			"final, and two homework grades, respectively:" << endl;
		cin >> midterm >> finalterm >> hw1 >> hw2;

		grades.push_back(0.2*midterm + 0.4*finalterm + 0.4*(hw1+hw2)/2);

		cout << "Please enter the following student's name "
			"(or quit with end-of-line): ";
	}

	cout << endl << endl;

	typedef vector<string>::size_type vec_sz;
	vec_sz students_sz = students.size();
	
	cout << "The student's grades are:" << endl << endl;

	// invariant: we have printed the grades of i students
	for (vec_sz i = 0; i != students_sz; ++i){
		cout << students[i] << " " << grades[i] << endl;
	}
	
	return 0;
}
