#include <string>
#include <vector>
#include <iostream>
#include <cstdio>   // clearerr(stdin)
#include <cctype>
#include <algorithm>

using std::vector;      using std::string;
using std::getline;     using std::cin;
using std::cout;            using std::endl;
using std::sort;            using std::max;

struct RotatedPhrase {
    vector<string> phrase;
    vector<string>::size_type rots; // Number of rotations: one rotation consists
                            // of shifting phrase[i] -> phrase[i-1] and the first word 
                            // towards the end. If rots = k, the corresponding sentence is
                            // "phrase[k mod n+1] phrase[k+1 mod n+1] ... phrase[k+n mod 
                            // n+1]"
};

vector<string> readPhrases(std::istream& in)
{
    vector<string> ret;
    if (in){
        string s;
        while (getline(in, s))
          ret.push_back(s); 
        in.clear();
        clearerr(stdin);
    }
    return ret;
}

vector<string> splitSentence(const string& sentence)
{
    vector<string> ret;
    typedef string::size_type StrSz;
    StrSz sentenceSz = sentence.size();

    StrSz i = 0;
    while (i != sentenceSz){
        while (i != sentenceSz && isspace(sentence[i]))
            ++i;
        StrSz j = i;
        while (j != sentenceSz && !isspace(sentence[j]))
          ++j;
        if (i != j){
            ret.push_back(sentence.substr(i, j-i));
            i = j;
        }
    }
    return ret;
}

// returns a vector<RotatedPhrase> containing all the rotations of phrase
vector<RotatedPhrase> generateRotations(const vector<string>& phrase)
{
    vector<RotatedPhrase> ret;
    for (vector<string>::size_type i = 0; i != phrase.size(); ++i){
        RotatedPhrase temp = {
            phrase, // temp.phrase
            i           // temp.rots
        };
        ret.push_back(temp);
    }
    return ret;
}

bool compareRotPhrAlpha(const RotatedPhrase& a, const RotatedPhrase& b)
{   
    // we first convert the strings to be compared into uppercase
    // for the relational operator < should compare strings in the same case
    string aString = a.phrase[a.rots];
    string bString = b.phrase[b.rots];
    string aStringUpp, bStringUpp;
    for (string::size_type i = 0; i != aString.size(); ++i)
        aStringUpp += (char)toupper(aString[i]);
    for (string::size_type i = 0; i != bString.size(); ++i)
        bStringUpp += (char)toupper(bString[i]);
    return aStringUpp < bStringUpp;
}

string::size_type computeMaxOffset(const vector< vector<string> > a)
{
    string::size_type ret = 0;

    for (vector< vector<string> >::const_iterator cit = a.begin();
            cit != a.end(); ++cit){
        string::size_type temp = 0;
        for (vector<string>::const_iterator cit2 = (*cit).begin();
                cit2 != (*cit).end(); ++cit2)
            temp += (*cit2).size();
        temp += (*cit).size()-1; // add spaces between words
        ret = max(ret, temp);
    }
    return ret;
}

int main()
{
    cout << "Enter a sequence sentences, seperated by ENTER. "
                "End with EOL (ctrl + D)." << endl;
    vector<string> input = readPhrases(cin);

    // every element of phrases is a vector containing
    // the words of a sentence in input
    vector< vector<string> > phrases;
    for (vector<string>::const_iterator cit = input.begin();
            cit != input.end(); ++cit)
        phrases.push_back(splitSentence(*cit));

    // we generate all the rotations of all the elements of phrases and store
    // them in allRotPhrases
    vector<RotatedPhrase> allRotPhrases;
    for (vector< vector<string> >::const_iterator cit = phrases.begin();
            cit != phrases.end(); ++cit){
        vector<RotatedPhrase> rotations = generateRotations(*cit);
        allRotPhrases.insert(allRotPhrases.end(), rotations.begin(), rotations.end());
    }

    // sort the rotated phrases alphabetically with respect to the first
    // word in the rotated phrase
    sort(allRotPhrases.begin(), allRotPhrases.end(), compareRotPhrAlpha);

    // generate output
    vector<string> output;
    string::size_type maxOffset = computeMaxOffset(phrases);
    for (vector<RotatedPhrase>::const_iterator cit = allRotPhrases.begin();
            cit != allRotPhrases.end(); ++cit){
        string sentence;
        string::size_type correction = 0;
        for (vector<string>::size_type k = 0; k != (*cit).rots; ++k)
            correction += (*cit).phrase[k].size()+1;
        correction -= 1;
        sentence += string(maxOffset - correction,' ');
        for (vector<string>::size_type i = 0; i != (*cit).phrase.size(); ++i){
            if (i == (*cit).rots)
                sentence += string(2,' ');
            sentence += (*cit).phrase[i] + " ";
        }

        output.push_back(sentence);
    }

    // print output
    for (vector<string>::const_iterator cit = output.begin();
            cit != output.end(); ++cit)
        cout << *cit << endl;

    return 0;
}
