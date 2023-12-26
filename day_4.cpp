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

// modified for 4.2
std::vector<unsigned long long> numberOfCards;
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
            longNums++;// = (longNums * 2);
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
        numberOfCards.push_back(1);
    }

    long long index = 0;
    unsigned long long aggrSum = 0;

    for(std::vector<std::string>::iterator it = input.begin(); it != input.end(); it++){
        std::string second = getSplitIndex(*it, ":", 1);
        strip(second);
        std::vector<std::string> parse;
        split(second, "|", parse);
        
        long long current =  getWinningNumbers(parse);
        if(current == 0){
            index++;
            continue;
        }
        
        // cout << "current "<< current << endl;
        for(int i = index + 1; i <= index + current; i++){
            if((index + 1) == (numberOfCards.size())){
                break;
            }
            numberOfCards[i] += numberOfCards[index];            
        }
        index++;
    }
    
    for(std::vector<unsigned long long>::iterator it = numberOfCards.begin(); it != numberOfCards.end(); it++){
        aggrSum += (*it);
        // cout << "num is "<< *it << endl;
    }

    cout << aggrSum << endl;
    return 0;
}