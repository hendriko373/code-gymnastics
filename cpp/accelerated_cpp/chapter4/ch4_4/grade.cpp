#include <vector>
#include <stdexcept>
#include "student_info.hpp"
#include "grade.hpp"
#include "median.hpp"

using std::vector;
using std::domain_error;

double grade(double midterm, double finalterm, double hw)
{
    return 0.2*midterm + 0.4*finalterm + 0.4*hw;
}

double grade(double midterm, double finalterm, const vector<double>& hw)
{
    if (hw.size() == 0)
        throw domain_error("There are no homework grades.");
    return grade(midterm, finalterm, median(hw));
}

double grade(const StudentInfo& s)
{
    return grade(s.midterm, s.finalterm, s.homework);
}

