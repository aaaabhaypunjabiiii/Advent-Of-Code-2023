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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int count;
    cin >> count;
    while(count--){
        // reset vars here
        discovered = std::map<pairOfBags, bool>();
        frontier  = std::map<pairOfBags, bool>();
        maxKey = -1;
        isEven = false;
        solutionFound = false;
        pairOfBags p = pairOfBags();

        int numbers;
        cin >> numbers;
        
        for(int i = 0; i < numbers; i++){
            int curr;
            cin >> curr; 
            if(p.bag1.find(curr) != p.bag1.end()){
                p.bag1[curr]++;
            }  
            else{
                p.bag1[curr] = 1;
                p.bag2[curr] = 0;
            }
        }

        discovered[p] = true;
        auto dictIter = p.bag1.rbegin();
        maxKey = dictIter->first;
        
        moveBetweenBags(p);
        addBag(p);
        if(solutionFound){
            cout << "Yes" << endl;
        }
        else{
            cout << "No" << endl;
        }
    }
    return 0;
}