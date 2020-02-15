#ifndef STUDENT_INFO_HPP
#define STUDENT_INFO_HPP

#include <iostream>
#include <string>
#include <vector>

class StudentInfo {
    public:
        StudentInfo();
        StudentInfo(std::istream&);

        std::istream& read(std::istream&);
        double grade() const;
        std::string getName() const;
        bool valid() const;

    private:
        std::string name_;
        double midterm_, finalterm_;
        std::vector<double> homework_;
        double grade_;
};

bool compare (const StudentInfo&, const StudentInfo&);

#endif
