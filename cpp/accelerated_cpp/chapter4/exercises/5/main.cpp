#include <iostream>
#include <vector>
#include <string>

using std::cout;		using std::cin;
using std::endl;		using std::istream;
using std::string;	using std::vector;

struct WordFrequency {
	string word;
	int frequency;
};

bool contains(const vector<WordFrequency>& vec, string s){
	bool r = false;
	for (vector<WordFrequency>::size_type i = 0; i != vec.size(); ++i){
		if (vec[i].word == s)
			r = true;
	}
	return r;
}

istream& readWord(istream& in, vector<string>& vec)
{
	string word;
	if (in >> word)
		vec.push_back(word);

	return in;
}

int main()
{
	cout << "Please enter a list of words:" << endl;	
	vector<string> words;
	int numWords = 0;

	while (readWord(cin, words)){
		++numWords;
	}	

	vector<WordFrequency> wordOccurences;

	typedef vector<string>::size_type vecSz;
	
	cout << words.size() << endl;
	for (vecSz i = 0; i != words.size(); ++i){

		if (contains(wordOccurences, words[i]) == false){

			WordFrequency record;
			record.word = words[i];
			record.frequency = 1;

			for (vecSz j = 0; j != words.size()-(i+1); ++j){
				if (words[i] == words[i+1+j])
					++record.frequency;
			}
			wordOccurences.push_back(record);
		}
	}

	cout << endl << "Total words: " << numWords << endl << endl;

	for (vector<WordFrequency>::size_type i = 0; i != wordOccurences.size(); ++i){
		cout << wordOccurences[i].word << string(4,' ')
		  <<	wordOccurences[i].frequency << endl;
	}
	
	return 0;
}
