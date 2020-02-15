#include <map>
#include <vector>
#include <iostream>
#include "report.hpp"
#include "student_info.hpp"

using namespace std;

void Report::addToReport(const StudentInfo& s)
{
    students_[s] = s.letterGrade();
}

void Report::addToReport(const vector<StudentInfo>& v)
{
    for (vector<StudentInfo>::const_iterator i = v.begin();
            i != v.end(); ++i) {
        students_[*i] = (*i).letterGrade();
    } 
    
}

void Report::printReport() const
{
    for (map<StudentInfo, char>::const_iterator i = students_.begin();
            i != students_.end(); ++i) {
        cout << (*i).first.getName() << '\t' << (*i).second << endl;
    }
}
