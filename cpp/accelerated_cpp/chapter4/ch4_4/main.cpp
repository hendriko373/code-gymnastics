#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iomanip>
#include "student_info.hpp"
#include "grade.hpp"

using std::vector;		using std::string;
using std::cin;			using std::cout;
using std::endl;			using std::sort;
using std::streamsize;	using std::setprecision;
using std::domain_error;

int main()
{
	vector<StudentInfo> students;
	string::size_type maxLength = 0;
	
	// read the student's grade records
	StudentInfo record;
	while (read(cin, record)){
		maxLength = std::max(maxLength, record.name.size());
		students.push_back(record);
	}

	sort(students.begin(), students.end(), compare);
	
	typedef vector<StudentInfo>::size_type vecStSz;
	vecStSz size = students.size();

	for (vecStSz i=0; i != size; ++i) {
		cout << students[i].name
			<< string(maxLength + 1 - students[i].name.size(), ' ');

		try {
			streamsize prec = cout.precision();
			double finalGrade = grade(students[i]);
			cout << setprecision(3) << finalGrade
				<< setprecision(prec) << endl;
		} catch (domain_error e) {
			cout << e.what();
		}
	}
	return 0;
}
