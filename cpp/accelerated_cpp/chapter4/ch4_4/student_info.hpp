#ifndef STUDENT_INFO_HPP
#define STUDENT_INFO_HPP

#include <string>
#include <vector>

struct StudentInfo
{
    std::string name;
    double midterm, finalterm;
    std::vector<double> homework;
};

std::istream& read_hw(std::istream&, std::vector<double>&);
std::istream& read(std::istream&, StudentInfo&);
bool compare(const StudentInfo&, const StudentInfo&);

#endif
