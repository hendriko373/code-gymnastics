#include <vector>
#include <string>
#include <iostream>

using std::vector;      using std::string;
using std::cout;        using std::endl;
using std::max;

string::size_type computeMaxLength(const vector<string>& vecIn)
{
    string::size_type ret = 0;

    for (vector<string>::const_iterator it = vecIn.begin();
            it != vecIn.end(); ++it)
        ret = max(ret, (*it).size());

    return ret;
}

vector<string> center(const vector<string>& vec)
{
    vector<string> ret;
    string::size_type maxLength = computeMaxLength(vec);

    for (vector<string>::const_iterator it = vec.begin(); it != vec.end(); ++it) {
        string::size_type lpadding = (maxLength - (*it).size())/2;
        string::size_type rpadding = (*it).size() - lpadding;
        string line = string(lpadding,' ') + *it + string(rpadding,' ');
        ret.push_back(line);
    }
    return ret;
}

bool centerUseful(const vector<string>& vec)
{
    bool ret = true;
    vector<string>::const_iterator it = vec.begin();
    int degree = (*it).size() % 2;
    ++it;
    while (ret == true && it != vec.end()) {
        int temp = (*it).size() % 2;
        if (degree != temp)
            ret = false;
        ++it;
    }
    return ret;
}

int main()
{
    vector<string> input;
    input.push_back("Dit is een zin");
    input.push_back("Een ander lijn woorden");
    input.push_back("De laatste zin");

    vector<string> output = center(input);

    cout << "Centering is useful: " << centerUseful(input) << endl;
    
    for (vector<string>::const_iterator it = output.begin();
            it != output.end(); ++it) {
        cout << *it << endl;
    }
    
}
