#include "stringopers.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

unsigned long long getPowerOfGame(string& game){
    std::map<std::string, unsigned long long> colorMaxes = {
        {"red", 0},
        {"green", 0},
        {"blue", 0}
    };
    std::vector<std::string> splitFirst, splitSecond;
    split(game, ": ", splitFirst);
    split(splitFirst[1], ";", splitSecond);
    for(std::vector<std::string>::iterator it = splitSecond.begin(); it != splitSecond.end(); ++it){
        std::vector<std::string> subGames;
        split(*it, ", ", subGames);
        for(std::vector<std::string>::iterator it1 = subGames.begin(); it1 != subGames.end(); ++it1){
            std::vector<std::string> splitGame;
            strip(*it1);
            split(*it1, " ", splitGame);
            colorMaxes[splitGame[1]] = std::max(colorMaxes[splitGame[1]], (unsigned long long)std::stoi(splitGame[0]));
        }
    }
    return colorMaxes["blue"] * colorMaxes["green"] * colorMaxes["red"];
}

// part 1
bool validateGame(string game){
    bool check = true;
    std::map<std::string, int> maxes = {
        {"red", 12},
        {"green", 13},
        {"blue", 14}
    };
    std::string getMoves = ": ", getSubGames = ";";   
    size_t start = 0, end = game.find(getMoves);
    std::string gameInfo = game.substr(start, end-start);

    start = end+1;
    game = game.substr(start);
    
    std::vector<std::string> subGames;
    start = 0;
    end = game.find(getSubGames);
    while(end != std::string::npos){
        subGames.push_back(game.substr(start, end-start));
        start = end + 1;
        end = game.find(getSubGames, start);
    } 
    subGames.push_back(game.substr(start));

    for(std::vector<std::string>::iterator it = subGames.begin(); it != subGames.end(); ++it){ 
        if(!check){
            return false;
        }
        std::string curr;
        start = 0;
        end = (*it).find(", ");
        while(end != std::string::npos){
            curr = (*it).substr(start, end-start);
            size_t startDelims  = curr.find_first_not_of(" \t\n\r"); // Find the first non-whitespace character
            size_t endDelims = curr.find_last_not_of(" \t\n\r");   // Find the last non-whitespace character
            curr = curr.substr(startDelims, endDelims - startDelims + 1);
        
            std::istringstream ss(curr);
            std::string arr[2], token;
            int i = 0;
            while(ss >> token){
                arr[i++] = token;
            }
            
            if(maxes[arr[1]] < std::stoi(arr[0])){
                cout << arr[1] << " " << arr[0] << endl;
                check = false;
                break;
            }
            start = end+1;
            end = (*it).find(", ", start);
        }
        if(check){
            curr = (*it).substr(start);
            size_t startDelims  = curr.find_first_not_of(" \t\n\r"); // Find the first non-whitespace character
            size_t endDelims = curr.find_last_not_of(" \t\n\r");   // Find the last non-whitespace character
            curr = curr.substr(startDelims, endDelims - startDelims + 1);
            std::istringstream ss(curr);
            std::string arr[2], token;
            int i = 0;
            while(ss >> token){
                arr[i++] = token;
            }
            if(maxes[arr[1]] < std::stoi(arr[0])){
                cout << arr[1] << " " << arr[0] << endl;
                check = false;
                break;
            }
        }
    }
    return check;
}



int main(){
    std::vector<std::string> games;
    
    std::ifstream inputFile("day2.txt");
    std::string line;

    // file input
    while(std::getline(inputFile, line)){
        games.push_back(line);
    }
    inputFile.close();

    unsigned long long count = 1, val = 0;
    for(auto it = games.begin(); it != games.end(); ++it){
        //if(validateGame(*it)){
            // unsigned long long x = getPowerOfGame(*it);
            // cout << x << endl;
            val += getPowerOfGame(*it);
        //}
        count++;
    }
    cout << val << endl;
    return 0;
}