#ifndef HELPER_H
#define HELPER.H

#include <string>
#include <vector>
#include <iostream>

std::string convertToNonAccentVN(std::string str);

std::string normalize(std::string str);

std::vector<std::string> split(const std::string& str, char delimiter);

#endif //HELPER_H