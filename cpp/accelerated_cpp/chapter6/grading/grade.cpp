#include <vector>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <iostream>
#include "student_info.hpp"
#include "grade.hpp"
#include "median.hpp"
#include "average.hpp"

using std::vector;      using std::domain_error;
using std::transform;   using std::back_inserter;
using std::ostream;     using std::string;
using std::endl;        using std::remove_copy;

double grade(double midterm, double finalterm, double hw)
{
    return 0.2*midterm + 0.4*finalterm + 0.4*hw;
}

double gradeMedian(const StudentInfo& s)
{
    try {
        return grade(s.midterm, s.finalterm, median(s.homework));
    } catch (domain_error) {
        return grade(s.midterm, s.finalterm, 0);
    }
}

double gradeAverage(const StudentInfo& s)
{
    return grade(s.midterm, s.finalterm, average(s.homework));
}

double gradeOptimMedian(const StudentInfo& s)
{
    vector<double> nonzeroHomework;
    remove_copy(s.homework.begin(), s.homework.end(), back_inserter(nonzeroHomework), 0);
    try {
        return grade(s.midterm, s.finalterm, median(nonzeroHomework));
    } catch (domain_error) {
        return grade(s.midterm, s.finalterm, 0);        
    }
}

double medianAnalysis(const vector<StudentInfo>& vec)
{
    vector<double> grades;
    transform(vec.begin(), vec.end(), back_inserter(grades), gradeMedian);
    return median(grades);
}

double averageAnalysis(const vector<StudentInfo>& vec)
{
    vector<double> grades;
    transform(vec.begin(), vec.end(), back_inserter(grades), gradeAverage);
    return median(grades);
}

double optimMedianAnalysis(const vector<StudentInfo>& vec)
{
    vector<double> grades;
    transform(vec.begin(), vec.end(), back_inserter(grades), gradeOptimMedian);
    return median(grades);
}

void writeAnalysis(ostream& out, string name,
                    double analysis(const vector<StudentInfo>&),
                    const vector<StudentInfo>& vec1,
                    const vector<StudentInfo>& vec2)
{
    out << name
        << "\n\tMedian of group that did all homework: " << analysis(vec1)
        << "\n\tMedian of group that did *not* all homework: " << analysis(vec2)
        << endl;
    return;
}
