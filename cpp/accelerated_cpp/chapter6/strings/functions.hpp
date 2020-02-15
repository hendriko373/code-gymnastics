#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <vector>
#include <string>

std::vector<std::string> split(const std::string&);
std::string::size_type computeMaxLength(const std::vector<std::string>&);
std::vector<std::string> makeFrame(const std::vector<std::string>&);

std::vector<std::string> concatenateVer(const std::vector<std::string>&, 
        const std::vector<std::string>&);
std::vector<std::string> concatenateHor(const std::vector<std::string>&, 
        const std::vector<std::string>&);

#endif
