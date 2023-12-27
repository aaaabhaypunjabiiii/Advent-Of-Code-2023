#include "stringopers.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <climits>

using namespace std;

void addToMap(std::string line, std::unordered_map<std::pair<unsigned long long, unsigned long long>, unsigned long long>& currMap){
    std::istringstream s(line);
    std::string token;
    std::vector<unsigned long long> nums;
    while(s >> token){
        strip(token);
        nums.push_back(std::stoull(token));
    }

    cout << "here" << nums.size() << endl;
    unsigned long long maxVal = nums[2], idx = 0;

    std::pair<unsigned long long, unsigned long long> startPairs;
    startPairs.first = nums[1];
    startPairs.second = nums[0];

    currMap[startPairs] = nums[2];
}

void gatherSeeds(std::string line, std::vector<unsigned long long>& seeds){
    std::string seedNums = getSplitIndex(line, ":", 1);
    strip(seedNums);
    std::istringstream s(seedNums);
    std::string token;
    while(s >> token){
        strip(token);
        seeds.push_back(std::stoull(token));  
    }
}

int main(){
    std::ifstream inputFile("day5.txt");
    std::string line;

    std::vector<std::unordered_map<std::pair<unsigned long long, unsigned long long>, unsigned long long>> vectorOfMaps;
    std::vector<unsigned long long> seeds;
    std::unordered_map<std::pair<unsigned long long, unsigned long long>, unsigned long long> currMap;
    while(getline(inputFile, line)){
        if(line.length() == 0){

            continue;
        }
        
        // ignore seeds line for now
        if(line.find("seeds") != std::string::npos){
            gatherSeeds(line, seeds);
            cout << "seeds done" << endl;
            continue;
        }

        // form all maps
        if(line.find("map") != std::string::npos){
            cout << "entered";
            if(currMap.size() > 0){
                vectorOfMaps.push_back(currMap);
            }
            currMap.clear();
            continue;
        }
        cout << "here" << endl;
        addToMap(line, currMap);
        cout << "line done" << endl;
    }

    unsigned long long minVal = ULLONG_MAX;
    for(std::vector<unsigned long long>::iterator it = seeds.begin(); it != seeds.end(); it++){
        unsigned long long seedNum = *it;
        unsigned long long currVal = seedNum;
        cout << "seed is " << seedNum << endl;
        for(std::vector<std::unordered_map<unsigned long long, unsigned long long>>::iterator it1 = vectorOfMaps.begin(); it1 != vectorOfMaps.end(); it1++){
            for(auto it2 = (*it1).begin(); it2 != (*it1).end(); it2++){
                if(){

                }
            }
        }

        if(currVal < minVal){
            minVal = currVal;
        }
    }

    cout << minVal << endl;
    return 0;
}
