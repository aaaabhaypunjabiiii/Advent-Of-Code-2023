#include "stringopers.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <map>
#include <cctype>

using namespace std;

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

long long gearRatio(vector<vector<std::string>> &grid, size_t row, size_t col, bool **visited, size_t max_rows, size_t max_cols){
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
    vector<long long> nums;
    for(size_t i = 0; i < (sizeof(directions)/sizeof(directions[0])); i++){
        size_t currRow = row + directions[i][0];
        size_t currCol = col + directions[i][1];
        std::string num = "";
        if(currRow >= 0 && currRow < grid.size() && currCol >= 0 && currCol < grid[0].size()){
           
            if(isdigit(grid[currRow][currCol][0]) && (!visited[currRow][currCol])){
                
                visited[currRow][currCol] = true;
                num += grid[currRow][currCol];
                size_t before = currCol - 1;
                size_t after = currCol + 1;

                while(before >=0 && before < grid[0].size() && isdigit(grid[currRow][before][0]) && !visited[currRow][before]){
                    num = grid[currRow][before] + num;
                    visited[currRow][before] = true;
                    before--;
                }

                while(after >=0 && after < grid[0].size() && isdigit(grid[currRow][after][0]) && !visited[currRow][after]){
                    num = num + grid[currRow][after];
                    visited[currRow][after] = true;
                    after++;
                }
            }
            if(num.length()){
                nums.push_back(std::stoll(num));
            }
        }
    }
    if(nums.size() == 2){
        return nums[0] * nums[1]; 
    }
    return 0;
}

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
    long long gearSum = 0;
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

    bool **visited = new bool *[grid.size()];

    for(size_t i = 0; i < grid.size(); i++){
        visited[i] = new bool[grid[i].size()];
        for(size_t j = 0; j < grid[i].size(); j++){
            visited[i][j] = false;
        }
    }

    for(size_t i = 0; i < grid.size(); i++){
        for(size_t j = 0; j < grid[i].size(); j++){
            if(grid[i][j] == "*"){
                gearSum += gearRatio(grid, i, j, visited, grid.size(), grid[0].size());
            }   
        }
    }
    cout << gearSum << endl;
    return 0;
}