#ifndef STUDENT_INFO_HPP
#define STUDENT_INFO_HPP

#include <fstream>
#include <string>
#include <vector>

class StudentInfo {
    public:
        StudentInfo();
        StudentInfo(std::ifstream&);

        std::ifstream& read(std::ifstream&);
        double grade() const;
        std::string getName() const;
        bool valid() const;

    private:
        std::string name_;
        double midterm_, finalterm_;
        std::vector<double> homework_;
};

std::string letterGrade(double);
bool compare (const StudentInfo&, const StudentInfo&);

#endif
