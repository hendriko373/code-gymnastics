#ifndef GRAMMAR_HPP
#define GRAMMAR_HPP

#include <vector>
#include <string>
#include <map>
#include <fstream>

typedef std::vector<std::string> Rule;
typedef std::map<std::string, std::vector<Rule> > Grammar;

Grammar readGrammar(std::ifstream&);
void writeGrammar(const Grammar&);
std::vector<std::string> generateSentence(const Grammar&);
int nRand(int);

#endif
