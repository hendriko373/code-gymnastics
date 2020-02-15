#ifndef  URL_HPP
#define  URL_HPP

#include <string>
#include <vector>

bool isNotUrlCharacter(char);

std::string::const_iterator start_url(std::string::const_iterator,
                                        std::string::const_iterator);

std::string::const_iterator end_url(std::string::const_iterator,
                                        std::string::const_iterator);

std::vector<std::string> findUrls(const std::string&);

#endif   /* ----- #ifndef URL_HPP  ----- */
