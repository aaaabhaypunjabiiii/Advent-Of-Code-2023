#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

std::map<std::string, int> digitToNum = {
    {"one",1},
    {"two",2},
    {"three",3},
    {"four",4},
    {"five",5},
    {"six",6},
    {"seven",7},
    {"eight",8},
    {"nine",9},
    {"zero",0}
};

int returnDigitFromLeftWord(long long idx, string word){
    if((idx + 2) < word.length()){
        std::string substring = word.substr(idx, 3);
        if((substring.compare("one") == 0)|| (substring.compare("two") == 0) ||(substring.compare("six") == 0)){
            return digitToNum[substring];
        }
    }
    if((idx + 3) < word.length()){
        std::string substring = word.substr(idx, 4);
        if((substring.compare("four") == 0)|| (substring.compare("five") == 0) ||(substring.compare("nine") == 0)||(substring.compare("zero") == 0)){
            return digitToNum[substring];
        }
    }
    if((idx + 4) < word.length()){
        std::string substring = word.substr(idx, 5);
        if((substring.compare("three") == 0)|| (substring.compare("seven") == 0) ||(substring.compare("eight") == 0)){
            return digitToNum[substring];
        }
    }
    return -1;
}

int returnDigitFromRightWord(long long idx, string word){
    if((idx - 2) >= 0){
        std::string substring = word.substr(idx-2, 3);
        if((substring.compare("one") == 0)|| (substring.compare("two") == 0) ||(substring.compare("six") == 0)){
            return digitToNum[substring];
        }
    }
    if((idx - 3) >= 0){
        std::string substring = word.substr(idx-3, 4);
        if((substring.compare("four") == 0)|| (substring.compare("five") == 0) ||(substring.compare("nine") == 0)||(substring.compare("zero") == 0)){
            return digitToNum[substring];
        }
    }
    if((idx - 4) >= 0){
        std::string substring = word.substr(idx-4, 5);
        if((substring.compare("three") == 0)|| (substring.compare("seven") == 0) ||(substring.compare("eight") == 0)){
            return digitToNum[substring];
        }
    }
    return -1;
}

int numValueOfString(string word){
    long long l = 0, r = (word.length()-1);
    bool leftFormed = false, rightFormed = false;
    int lVal = -1, rVal = -1;
    while(l < r){
        if(leftFormed && rightFormed){
            return ((lVal*10) + rVal);
        }
       
        if(!leftFormed){
            if(std::isdigit(word[l])){
                leftFormed = true;
                lVal = std::stoi(std::string(1, word[l]));
            }
            else{
                if((lVal = returnDigitFromLeftWord(l, word)) != -1){
                    leftFormed = true;
                }
                else{
                    l++;
                }
            }
        }

        if(!rightFormed){
            if(std::isdigit(word[r])){
                rightFormed = true;
                rVal = std::stoi(std::string(1, word[r]));
            }
            else{
                if((rVal = returnDigitFromRightWord(r, word)) != -1){
                   rightFormed = true;
                }
                else{
                    r--;
                }
            }
        }
    }

    if(leftFormed && rightFormed){
        cout << "formed is " << (lVal*10) + rVal << endl;
        return ((lVal*10) + rVal);
    }

    else if((l == r) && (std::isdigit(word[l]))){
        return std::stoi(std::string(1, word[l]) + std::string(1, word[r]));
    }

    return 0;
}

int main(){
    std::vector<string> str_list;
    std::ifstream inputFile("day1.txt");
    std::string line;

    // file input
    while(std::getline(inputFile, line)){
        str_list.push_back(line);
    }
    inputFile.close();

    int val = 0;
    for(std::vector<string>::iterator it = str_list.begin(); it != str_list.end(); ++it){
        val += (numValueOfString(*it));
    }

    cout << "Sum is "<<val<<endl;
    return val;
}