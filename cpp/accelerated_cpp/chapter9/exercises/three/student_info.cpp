#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <cstdio>
#include "student_info.hpp"

using namespace std;

StudentInfo::StudentInfo(): midterm_(0), finalterm_(0){}
StudentInfo::StudentInfo(istream& in)
{
    read(in);
}

string StudentInfo::getName() const
{
    return name_;
}

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

istream& StudentInfo::read(istream& is)
{
    is >> name_ >> midterm_ >> finalterm_;
    read_hw(is, homework_);
    return is;
}

bool StudentInfo::valid() const
{
    return !homework_.empty();
}

double median(vector<double> vec)
{
    typedef vector<double>::size_type VecSz;
    VecSz size = vec.size();

    if (size == 0)
        throw domain_error("median of an empty vector");

    sort(vec.begin(), vec.end());

    VecSz mid = size/2;
    return size%2 == 0 ? (vec[mid-1] + vec[mid])/2 : vec[mid];
}

double grade(double midtm, double finaltm, double hw)
{
    return 0.2*midtm + 0.4*finaltm + 0.4*hw;
}

double grade(double midtm, double finaltm, const vector<double>& hw)
{
    if (hw.empty())
        throw domain_error("There are no homework grades.");
    return grade(midtm, finaltm, median(hw));
}

double StudentInfo::grade() const
{
    try {
        return ::grade(midterm_, finalterm_, homework_);
    } catch (domain_error e) {
        cout << e.what() << endl;
    }
}

bool compare (const StudentInfo& s1, const StudentInfo& s2)
{
	return s1.getName() < s2.getName();
}
