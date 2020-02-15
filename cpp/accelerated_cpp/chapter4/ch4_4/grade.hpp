#ifndef GRADE_HPP
#define GRADE_HPP

#include "student_info.hpp"
#include <vector>

double grade(double, double, double);
double grade(double, double, const std::vector<double>&);
double grade(const StudentInfo&);

#endif
