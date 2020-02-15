#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include "student_info.hpp"
#include "report.hpp"

using namespace std;

int main()
{
    vector<StudentInfo> students;
    string::size_type maxLength = 0;

    // read the student's grade records
    ifstream input("students_grades.txt");
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
                << setprecision(prec) << endl;
        } catch (domain_error e) {
            cout << e.what();
        }
    }

    cout << endl;
    Report report(students);
    report.printReport();
    
    return 0;
}
