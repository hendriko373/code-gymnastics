#ifndef CROSSREF_HPP
#define CROSSREF_HPP

#include <map>
#include <string>
#include <vector>
#include <fstream>

std::vector<std::string> split(const std::string&);
std::map<std::string, std::vector<int> >
    crossRef(std::ifstream&, std::vector<std::string> findWords(const std::string&) = split);

#endif
