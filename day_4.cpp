#include "stringopers.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <map>
#include <unordered_map>
#include <string>

using namespace std;
// std::string str, std::string delimiter, std::vector<long long>& tokens

long long getWinningNumbers(std::vector<std::string>& vec){
    long long longNums = 0;
    std::string winningNumbersStr = vec[0];
    std::string numbersYouHaveStr = vec[1];
    strip(winningNumbersStr); strip(numbersYouHaveStr);
    std::vector<long long> winningNumbers, numbersYouHave;
    splitToNum(winningNumbersStr, " ", winningNumbers);
    splitToNum(numbersYouHaveStr, " ", numbersYouHave);
    std::unordered_map<long long, bool> winners;
    for(std::vector<long long>::iterator it = winningNumbers.begin(); it != winningNumbers.end(); it++){
        winners[*it] = true;
    }

    for(std::vector<long long>::iterator it = numbersYouHave.begin(); it != numbersYouHave.end(); it++){
        auto check = winners.find(*it);
        if(check != winners.end()){
            if(longNums == 0){
                longNums = 1;
                continue;
            }
            longNums = (longNums * 2);
        }
    }

    return longNums;
}
int main(){
    std::vector<std::string> input;
    std::ifstream inputFile("day4.txt");
    std::string line;

    while(getline(inputFile, line)){
        input.push_back(line);
    }
    long long aggrSum = 0;
    for(std::vector<std::string>::iterator it = input.begin(); it != input.end(); it++){
        std::string second = getSplitIndex(*it, ":", 1);
        strip(second);
        std::vector<std::string> parse;
        split(second, "|", parse);
        
        aggrSum += getWinningNumbers(parse);
    }
    cout << aggrSum << endl;
    return 0;
}