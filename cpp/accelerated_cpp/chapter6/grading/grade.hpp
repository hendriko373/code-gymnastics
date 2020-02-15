#ifndef GRADE_HPP
#define GRADE_HPP

#include "student_info.hpp"
#include <vector>
#include <string>
#include <iostream>

double grade(double, double, double);
//double grade(double, double, const std::vector<double>&);
double gradeMedian(const StudentInfo&);
double gradeAverage(const StudentInfo&);
double gradeOptimMedian(const StudentInfo&);
double medianAnalysis(const std::vector<StudentInfo>&);
double averageAnalysis(const std::vector<StudentInfo>&);
double optimMedianAnalysis(const std::vector<StudentInfo>&);
void writeAnalysis(std::ostream& out, std::string name,
                    double analysis(const std::vector<StudentInfo>&),
                    const std::vector<StudentInfo>& vec1,
                    const std::vector<StudentInfo>& vec2);

#endif
