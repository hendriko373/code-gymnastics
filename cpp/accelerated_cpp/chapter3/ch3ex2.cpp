#include <vector>
#include <iostream>
#include <algorithm>

using std::cout;		using std::cin;
using std::endl;		using std::max;
using std::sort;		using std::vector;

int main() {

	// ask for a set of integers
	cout << "Please enter a set of integers, "
				"followed by end-of-line." << endl;
	vector<int> ints;
	int x;
	// invariant: ints contains the integers read so far 
	while (cin >> x)
		ints.push_back(x);

	typedef vector<int>::size_type vec_sz;
	vec_sz size = ints.size();
	sort(ints.begin(),ints.end());

	// compute the four quartiles
	vector<int> q1, q2, q3, q4;
	vec_sz r = size % 4;
	
	// invariant: q1 contains the first i elements of the
	//		first quartile
	for (vec_sz i = 0; i != size/4 + max(r%2, r/2); ++i)
		q1.push_back(ints[i]);

	// invariant: q2 contains the first i elements of the
	//		second quartile
	for (vec_sz i = size/4 + max(r%2, r/2);
			i != 2 * (size/4) + max(r%2, 2*(r/2)); ++i)
		q2.push_back(ints[i]);

	// invariant: q3 contains the first i elements of the
	//		third quartile
	for (vec_sz i = 2 * (size/4) + max(r%2, 2*(r/2));
			i != 3 * (size/4) + max(r%3, 3*(r/3)); ++i)
		q3.push_back(ints[i]);

	// invariant: q4 contains the first i elements of the
	//		fourth quartile
	for (vec_sz i = 3 * (size/4) + max(r%3, 3*(r/3));
			i != size; ++i)
		q4.push_back(ints[i]);
			
	// print the quartiles
	vec_sz sz_q1 = q1.size();
	cout << "1st quartile: ";
	// invariant: there are printed i elements of q1
	for (vec_sz i = 0; i != sz_q1; ++i)
	  cout << q1[i] << " ";
	cout << endl;	

	vec_sz sz_q2 = q2.size();
	cout << "2nd quartile: ";
	// invariant: there are printed i elements of q2
	for (vec_sz i = 0; i != sz_q2; ++i)
	  cout << q2[i] << " ";

	cout << endl;	

	vec_sz sz_q3 = q3.size();
	cout << "3rd quartile: ";
	// invariant: there are printed i elements of q3
	for (vec_sz i = 0; i != sz_q3; ++i)
	  cout << q3[i] << " ";

	cout << endl;	

	vec_sz sz_q4 = q4.size();
	cout << "4th quartile: ";
	// invariant: there are printed i elements of q4
	for (vec_sz i = 0; i != sz_q4; ++i)
	  cout << q4[i] << " ";

	cout << endl;	
	return 0;
}
