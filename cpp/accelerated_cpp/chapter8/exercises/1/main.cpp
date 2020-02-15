#include <vector>
#include <iostream>
#include "student_info.hpp"
#include "grade.hpp"

using std::vector;
using std::cin;     using std::cout;
using std::endl;

int main()
{
    vector<StudentInfo> didAllHw, didNotAllHw;

    StudentInfo student;
    while (read(cin, student)) {

        if (didAllHomework(student))
            didAllHw.push_back(student);
        else
            didNotAllHw.push_back(student);
    }

    // check if both groups contain any students, otherwise our program
    // serves to nothing
    if (didAllHw.empty()) {
        cout << "None of the students did all homework!" << endl;
        return 1;
    }
    if (didNotAllHw.empty()) {
        cout << "All the students did all homework!" << endl;
        return 1;
    }

    // Analysis in which the grade of a student is computed by considering the median
    // of all homeworks, i.e., including those that were not turned in
    writeAnalysis(cout, "Median of all homework", analysis<gradeMedian>,
                    didAllHw, didNotAllHw);
    
    // Analysis in which the grade of a student is computed by considering the 
    // average of all homeworks, i.e., including those that were not turned in
    writeAnalysis(cout, "Average of all homework", analysis<gradeAverage>,
                    didAllHw, didNotAllHw);

    // Analysis in which the grade of a student is computed by considering the median 
    // of only nonzero homeworks, i.e., excluding those that were not turned in
    writeAnalysis(cout, "Optimistic median of all homework", 
            analysis<gradeOptimMedian>, didAllHw, didNotAllHw);

    return 0;
}
