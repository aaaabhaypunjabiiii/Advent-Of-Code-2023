#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

#include <vector>
#include <fstream>
#include <string>
#include <sstream>

void split(std::string, std::string, std::vector<std::string>&);

void strip(std::string&);

std::string getSplitIndex(std::string str, std::string delimiter, int index);

#endif