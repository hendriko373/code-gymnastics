#ifndef REPORT_HPP
#define REPORT_HPP

#include <map>
#include "student_info.hpp"

struct classCompare {
    bool operator()(const StudentInfo& s1, const StudentInfo& s2)
    {
        return compare(s1, s2);
    }
};

class Report {
    public:
        Report();
        Report(const StudentInfo& s) {
            addToReport(s);
        }
        Report(const std::vector<StudentInfo>& v) {
            addToReport(v);
        }

        void addToReport(const StudentInfo&);
        void addToReport(const std::vector<StudentInfo>&);
        void printReport() const;

    private:
        std::map<StudentInfo, char, classCompare> students_;
};

#endif
