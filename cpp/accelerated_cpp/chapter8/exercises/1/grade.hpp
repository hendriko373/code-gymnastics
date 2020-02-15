#ifndef GRADE_HPP
#define GRADE_HPP

#include "student_info.hpp"
#include "median.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>

double grade(double, double, double);

double gradeMedian(const StudentInfo&);

double gradeAverage(const StudentInfo&);

double gradeOptimMedian(const StudentInfo&);

void writeAnalysis(std::ostream& out, std::string name,
                    double anal(const std::vector<StudentInfo>&),
                    const std::vector<StudentInfo>& vec1,
                    const std::vector<StudentInfo>& vec2);

template <double T(const StudentInfo&)>
double analysis(const std::vector<StudentInfo>& vec)
{
    std::vector<double> grades;
    std::transform(vec.begin(), vec.end(), std::back_inserter(grades), T);
    return median(grades);
}

#endif
