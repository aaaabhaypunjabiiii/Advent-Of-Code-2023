#include <iostream>
#include "stringopers.h"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

std::string getSplitIndex(std::string str, std::string delimiter, int index){
    // assuming that no index out of bounds error occurs
    int num_tokens = 0;
    size_t start = 0, end = str.find(delimiter);
    while(end != std::string::npos){
        std::string token = str.substr(start, end);
        start = end + 1;
        end = str.find(delimiter, start);
        if(num_tokens == index){
            return token;
        }
        num_tokens++;
    }
    return str.substr(start);
}

void split(std::string str, std::string delimiter, std::vector<std::string>& tokens){
    size_t start = 0;
    size_t end = str.find(delimiter);

    while(end != std::string::npos){
        tokens.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find(delimiter, start);
    }

    tokens.push_back(str.substr(start));
}

void strip(std::string& str){
    size_t start = str.find_first_not_of(" \n\r\t");
    size_t end = str.find_last_not_of(" \n\r\t");
    str = str.substr(start, end-start+1);
}