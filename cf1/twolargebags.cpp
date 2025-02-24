#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>


using namespace std;

struct pairOfBags{
    std::map<int, int> bag1;
    std::map<int, int> bag2;

    bool operator<(const pairOfBags& other) const {
        if(bag1 != other.bag1){
            return bag1 < other.bag1;
        }
        return bag2 < other.bag2;
    }
};
std::ostream& operator<<(std::ostream& os, const pairOfBags& p) {
    os << "Bag 1: {";
    for (const auto& [key, value] : p.bag1) {
        os << key << ":" << value << ", ";
    }
    os << "}\n";

    os << "Bag 2: {";
    for (const auto& [key, value] : p.bag2) {
        os << key << ":" << value << ", ";
    }
    os << "}\n";

    return os;
}

void addBag(pairOfBags p1);
void moveBetweenBags(pairOfBags p1);

std::map<pairOfBags, bool> discovered;
std::map<pairOfBags, bool> frontier;
int maxKey = -1;

bool isEven = false, solutionFound = false;
pairOfBags p;

bool isEvenCheck(pairOfBags p1){
    // cout << (p1.bag1 == p1.bag2) << endl;
    // cout << p1 << endl; 
    return (p1.bag1 == p1.bag2);
}

void moveBetweenBags(pairOfBags p1){
    if(solutionFound){
        return;
    }
    bool advance = false;
    if(((frontier.find(p1) != frontier.end()) && !frontier[p1])){
        // cout << "************" << endl;
        // cout << "Frontier explored" << endl;
        // cout << p1 << endl;
        // cout << "************" << endl;
        return;
    }
    else if(isEvenCheck(p1)){
        solutionFound = true;
        // cout << "************" << endl;
        // cout << "SOLUTION FOUND" << endl;
        // cout << p1 << endl;
        // cout << "************" << endl;
        return;
    }


    //cout << "MOVE" << p1 << endl;
    for(auto const&x : p1.bag1){
        if(p1.bag1[x.first] == 0){
            continue;
        }
        p1.bag1[x.first]--;
        p1.bag2[x.first]++;
        if(discovered.find(p1) != discovered.end()){
            p1.bag1[x.first]++;
            p1.bag2[x.first]--;
        }
        else{
            discovered[p1] = true;
            advance = true;
            moveBetweenBags(p1);
            addBag(p1);        }
    }

    if(!advance){
        frontier[p1] = false;
        return;
    }
}

void addBag(pairOfBags p1){
    bool advance = false;
    if(solutionFound){
        return;
    }

    if(((frontier.find(p1) != frontier.end()) && !frontier[p1]) || (p1.bag2 == p.bag1)){
        // cout << "************" << endl;
        // cout << "Frontier explored" << endl;
        // cout << p1 << endl;
        // cout << "************" << endl;
        return;
    }
    else if(isEvenCheck(p1)){
        solutionFound = true;
        // cout << "************" << endl;
        // cout << "SOLUTION FOUND" << endl;
        // cout << p1 << endl;
        // cout << "************" << endl;
        return;
    }

    //cout << "ADD" << p1 << endl;
    for(auto const&x : p1.bag1){
        if(p1.bag2.find(x.first) != p1.bag2.end()){
            if(p1.bag1[x.first] == 0 || p1.bag2[x.first] == 0){
                continue;
            } 
            int oldKey = x.first;
            int newKey = oldKey + 1;

            // don't go higher than the maxKey
            if(newKey > maxKey){
                continue;
            }
            p1.bag1[newKey] += 1;

            p1.bag1[oldKey] -= 1;
            

            if(discovered.find(p1) != discovered.end()){
                p1.bag1[oldKey] += 1;
                p1.bag1[newKey] -= 1;
            }
            else{
                discovered[p1] = true;
                advance = true;
                moveBetweenBags(p1);
                addBag(p1);
            }
        }
    }
    // cout << p1;

    if(!advance){
        frontier[p1] = false;
        return;
    }
}


int main(){
    // std::ofstream outFile("output.txt");
    // std::cout.rdbuf(outFile.rdbuf());


    ifstream file("input.txt");
    string str;

    // int count = std::stoi(str); // read first line
    // while(){


    //     --count;
    // }
    std::getline(file, str);
    int nums = std::stoi(str); // read first line
    while(std::getline(file, str)){
        std::stringstream ss(str);
        int curr;
        while(ss >> curr){
            if(p.bag1.find(curr) != p.bag1.end()){
                p.bag1[curr]++;
            }  
            else{
                p.bag1[curr] = 1;
                p.bag2[curr] = 0;
            }
        }
    }
    discovered[p] = true;

    auto dictIter = p.bag1.rbegin();
    maxKey = dictIter->first;
    // cout << "Max key is " << maxKey << endl;
    
    // cout << p << endl;
    moveBetweenBags(p);
    addBag(p);
    if(solutionFound){
        cout << "Yes" << endl;
    }
    else{
        cout << "No" << endl;
    }
    // outFile.close();
    return 0;
}