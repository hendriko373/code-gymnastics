#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "student_info.hpp"

using namespace std;

int main()
{
    vector<StudentInfo> students;
    string::size_type maxLength = 0;

    // read the student's grade records
    const char* inFile = "students_grades.txt";
    ifstream input(inFile);
    StudentInfo record;
    while (record.read(input)){
        maxLength = max(maxLength, record.getName().size());
        students.push_back(record);
    }

    sort(students.begin(), students.end(), compare);

    typedef vector<StudentInfo>::size_type VecStSz;
    VecStSz size = students.size();

    for (VecStSz i=0; i != size; ++i) {
        cout << students[i].getName()
            << string(maxLength + 1 - students[i].getName().size(), ' ');

        try {
            streamsize prec = cout.precision();
            double finalGrade = students[i].grade();
            cout << setprecision(3) << finalGrade
                << setprecision(prec) << "\t"
                << letterGrade(finalGrade) << endl;
        } catch (domain_error e) {
            cout << e.what();
        }
    }
    return 0;
}
