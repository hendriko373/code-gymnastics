#include "student_info.hpp"
#include <iostream>
#include <cstdio>

using std::istream;
using std::vector;
using std::cout;
using std::endl;

istream& read_hw(istream& in, vector<double>& hw)
{

    // check if 'in' is not in failure state
    if (in){
        // get rid of previous contents; this may be necessary because
        // 'hw' is a reference to an existing object so that it already
        // may contain values
        hw.clear();

        double x;
        // invariant: 'hw' contains the grades read so far
        while (in >> x){
            hw.push_back(x);
        }

        // clear the stream so that end-of-file or failure state
        // does not propagate back to caller
        in.clear();
        clearerr(stdin);
    }
    return in;
}

istream& read(istream& is, StudentInfo& s)
{
    // read a student's name and midterm and final grades into 's'
    cout << "Enter a student's name, its midterm, final "
        "and homework grades: " << endl;
    is >>	s.name >> s.midterm >> s.finalterm;

    // read a student's homework grades into 's'
    read_hw(is, s.homework);
    return is;
}

bool compare (const StudentInfo& s1, const StudentInfo& s2)
{
    return s1.name < s2.name;
}

