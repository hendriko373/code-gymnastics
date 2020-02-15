#include <iostream>
#include <cstdio>
#include <algorithm>
#include "student_info.hpp"

using std::istream;     using std::vector;
using std::cout;        using std::endl;
using std::find;

istream& read_hw(istream& is, vector<double>& hw)
{

    // check if 'is' is not in failure state
    if (is){
        // get rid of previous contents; this may be necessary because
        // 'hw' is a reference to an existing object so that it already
        // may contain values
        hw.clear();

        double x;
        // invariant: 'hw' contains the grades read so far
        while (is >> x){
            hw.push_back(x);
        }

        // clear the stream so that end-of-file or failure state
        // does not propagate back to caller
        is.clear();
        clearerr(stdin);
    }
    return is;
}

istream& read(istream& is, StudentInfo& s)
{
    // read a student's name and midterm and final grades into 's'
    cout << "Enter a student's name, and its midterm and final grades. "
        "(If there are no more students, press EOL):" << endl;
    is >> s.name >> s.midterm >> s.finalterm;

    // read a student's homework grades into 's'
    if (is)
        cout << "Enter " << s.name << "´s homework grades (End with EOL):" << endl;
    read_hw(is, s.homework);
    return is;
}

bool compare (const StudentInfo& s1, const StudentInfo& s2)
{
    return s1.name < s2.name;
}

bool didAllHomework(const StudentInfo& s)
{
    return find(s.homework.begin(), s.homework.end(), 0) == s.homework.end();
}
