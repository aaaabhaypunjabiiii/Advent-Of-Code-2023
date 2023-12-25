#include "stringopers.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <map>
#include <cctype>

bool checkForObstacle(std::vector<std::vector<std::string>>& grid, size_t row, size_t col){
    int directions[8][2] = {
        {-1, 0},
        {1, 0},
        {0, -1},
        {0, 1},
        {1, 1},
        {-1, -1},
        {-1, 1},
        {1, -1}
    };

    for(size_t i = 0; i < (sizeof(directions)/sizeof(directions[0])); i++){
        size_t currRow = row + directions[i][0];
        size_t currCol = col + directions[i][1];
        if(currRow >= 0 && currRow < grid.size() && currCol >= 0 && currCol < grid[0].size()){
            if(!isalnum(grid[currRow][currCol][0]) && (grid[currRow][currCol] != ".")){
                return true;
            }
        }
    }
    return false;
}

using namespace std;

int main(){
    std::ifstream inputFile("day3.txt");
    string line;

    std::vector<std::vector<std::string>> grid;

    while(getline(inputFile, line)){
        std::vector<std::string> row;
        for(std::string::iterator it = line.begin(); it != line.end(); it++){
            row.push_back(std::string(1, *it));
        }
        grid.push_back(row);
    }
    
    unsigned long long sum = 0;
    bool nearSymbol = false;
    for(size_t i = 0; i < grid.size(); i++){
        for(size_t j = 0; j < grid[i].size(); j++){
            std::string num = "";
            while(j < grid[i].size() && isdigit(grid[i][j][0])){
                num += grid[i][j];//up, down, left, right.
                if(!nearSymbol && checkForObstacle(grid, i, j)){
                    nearSymbol = true;
                }
                j++;
            }
            if(nearSymbol){
                nearSymbol = false;
                sum += std::stol(num);
                num = "";   
            }
        }
    }

    cout << sum << endl;
    return 0;
}