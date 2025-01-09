#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <string>
#include <vector>

std::string convertToNonAccentVN(std::string str);

std::string normalize(std::string str);

std::vector<std::string> &split(const std::string &str, char delimiter);

#endif // HELPER_H
