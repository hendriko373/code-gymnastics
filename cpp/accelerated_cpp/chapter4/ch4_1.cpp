#include <vector>
#include <iomanip>
#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>

using std::vector;		using std::sort;
using std::cin;			using std::cout;
using std::endl;			using std::string;
using std::streamsize;	using std::setprecision;
using std::domain_error;using std::istream;

// compute the median of a 'vector<double>'
// calling this function copies argument into parameter
double median(vector<double> vec){

	typedef vector<double>::size_type vec_sz;
	vec_sz size = vec.size();

	if (size == 0)
		throw domain_error("median of an empty vector");

	sort(vec.begin(), vec.end());

	vec_sz mid = size/2;
	return size%2 == 0 ? (vec[mid-1] + vec[mid])/2 : vec[mid];
}

double grade(double midterm, double finalterm, double hw){
	
	return 0.2*midterm + 0.4*finalterm + 0.4*hw;
}

double grade(double midterm, double finalterm, const vector<double>& hw){
	
	if (hw.size() == 0)
		throw domain_error("There are no homework grades.");
	return grade(midterm, finalterm, median(hw));
}

istream& read_hw(istream& in, vector<double>& hw){

	if (in){
		// get rid of previous contents, otherwise 'hw' will contain
		// other stuff than the read in grades
		hw.clear();
		double x;

		// invariant: 'hw' contains the grades read so far
		while (in >> x){
			hw.push_back(x);
		}

		// clear the stream so that end-of-file or failure state
		// does not propagate back to caller
		in.clear();
	}
	return in;
}

int main(){

	// ask for and read the student's name
	cout << "Please enter your first name: ";
	string name;
	cin >> name;
	cout << "Hello, " + name + "!" << endl;

	// ask for and read the midterm and final grades
	double midterm, finalterm;
	cout << "Enter your midterm grade: ";
	cin >> midterm;
	cout << "Enter your final grade: ";
	cin >> finalterm;

	// ask for and read the homework grades
	cout << "Please enter the homework grades of " + name + "; "
				"end with end-of-file:" << endl;
	vector<double> homework;
	read_hw(cin, homework);

	// compute and write the final grade
	try {
		double final_grade = grade(midterm, finalterm, homework);
		streamsize prec = cout.precision();
		cout << "Your final grade is " << setprecision(3)
			<< final_grade << setprecision(prec)
			<< "." << endl;
	} catch (domain_error) {
		cout << endl << "You must enter your grades. "
			"Please try again." << endl;
		return 1;
	}

	return 0;
}
