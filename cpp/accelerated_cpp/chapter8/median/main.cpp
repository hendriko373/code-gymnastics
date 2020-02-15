#include <vector>
#include <stdexcept>
#include <algorithm>
#include <iostream>

using std::vector;
using std::domain_error;
using std::sort;
using std::cout;
using std::cin;
using std::endl;
using std::istream;

template <class T>
T median(vector<T> v)
{
    typedef typename vector<T>::size_type vec_sz;
    vec_sz size = v.size();

    if (size == 0)
        throw domain_error("median of an empty vector");

    sort(v.begin(), v.end());

    vec_sz mid = size/2;
    cout << size << endl;
    return size%2 == 0 ? (v[mid-1] + v[mid])/2 : v[mid];
}

template <class T>
void read_vector(istream& in, vector<T>& v)
{
    T temp;
    while (in >> temp)
        v.push_back(temp); 
    return;
}

int main()
{
    char in;
    cout << "Median of ints (I) or doubles (D)? ";
    cin >> in;
    cout << "Enter the set of numbers. Terminate with EOL." << endl;

    if (in == 'I') {

        vector<int> input; 
        read_vector(cin, input);
        cout << "\nThe median is given by " << median(input) << endl;
    }
    else if (in == 'D'){

        vector<double> input;
        read_vector(cin, input);
        cout << "\nThe median is given by " << median(input) << endl;
    }
    else {

        cout << "Not a valid answer." << endl;
        return 1;
    }
    return 0;
}
