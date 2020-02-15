#include <vector>
#include <iomanip>
#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <cstdio>		// clearerr
#include <map>

using std::vector;	    using std::sort;
using std::cin;		    using std::cout;
using std::endl;	    using std::string;
using std::streamsize;	    using std::setprecision;
using std::domain_error;    using std::istream;
using std::map;

struct StudentInfo
{
    string name;
    double midterm, finalterm;
    vector<double> homework;
};

istream& read_hw(istream& in, vector<double>& hw)
{
    // check if 'in' is not in failure state
    if (in){
        // get rid of previous contents; this may be necessary because
        // 'hw' is a reference to an existing object so that it already
        // may contain values
        hw.clear();

        double x;
        // invariant: 'hw' contains the grades read so far
        while (in >> x){
            hw.push_back(x);
        }

        // clear the stream so that end-of-file or failure state
        // does not propagate back to caller
        in.clear();
        clearerr(stdin);
    }
    return in;
}

istream& read(istream& is, StudentInfo& s)
{
    // read a student's name and midterm and final grades into 's'
    cout << "Enter a student's name, its midterm, final "
        "and homework grades: " << endl;
    is >> s.name >> s.midterm >> s.finalterm;

    // read a student's homework grades into 's'
    read_hw(is, s.homework);
    return is;
}

double grade(double midterm, double finalterm, double hw)
{
    return 0.2*midterm + 0.4*finalterm + 0.4*hw;
}

double median(vector<double> vec)
{
    typedef vector<double>::size_type VecSz;
    VecSz size = vec.size();

    if (size == 0)
        throw domain_error("median of an empty vector");

    sort(vec.begin(), vec.end());

    VecSz mid = size/2;
    return size%2 == 0 ? (vec[mid-1] + vec[mid])/2 : vec[mid];
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

bool compare (const StudentInfo& s1, const StudentInfo& s2)
{
    return s1.name < s2.name;
}

char getLetterGrade (const StudentInfo& s)
{
    double g = grade(s);
    if (g < 60)
        return 'F';
    else if (g < 70)
        return 'D';
    else if (g < 80)
        return 'C';
    else if (g < 90)
        return 'B';
    else return 'A';
}

int main()
{
    vector<StudentInfo> students;
    string::size_type maxLength = 0;

    // read the student's grade records
    StudentInfo record;
    while (read(cin, record)){
        maxLength = std::max(maxLength, record.name.size());
        students.push_back(record);
    }

    sort(students.begin(), students.end(), compare);

    map<char, vector<StudentInfo>> letterGradesStudents;
    
    for (vector<StudentInfo>::const_iterator i = students.begin();
            i != students.end(); ++i) {

        cout << (*i).name
            << string(maxLength + 1 - (*i).name.size(), ' ');

        try {
            streamsize prec = cout.precision();
            double finalGrade = grade(*i);
            cout << setprecision(3) << finalGrade << setprecision(prec) << endl;

            letterGradesStudents[getLetterGrade(*i)].push_back(*i);
        } catch (domain_error e) {
            cout << e.what();
        }
    }

    for (map<char, vector<StudentInfo>>::const_iterator i = letterGradesStudents.begin();
            i != letterGradesStudents.end(); ++i) {

        cout << "There is (are) " << (*i).second.size()
            << " student(s) with grade " << (*i).first << endl;
    }
    return 0;
}
