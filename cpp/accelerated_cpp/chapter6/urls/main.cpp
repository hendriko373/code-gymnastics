#include <string>
#include <vector>
#include <iostream>
#include "url.hpp"

using std::string;  using std::vector;
using std::cout;    using std::endl;

int main()
{
    string input =
        "http://test.com en ftp://anotherpage.be :// is geen pagina";

    vector<string> output = findUrls(input);

    for (vector<string>::const_iterator i = output.begin();
            i != output.end(); ++i) {
        cout << *i << endl;
    }
    return 0;
}
