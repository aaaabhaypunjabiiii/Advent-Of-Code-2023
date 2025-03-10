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

void solution(pairOfBags p1);

void solution(pairOfBags p1){
    int sum = 0;
    for(const auto& pair: p1.bag1){
        sum += pair.second;
    }

    auto it = p1.bag1.begin();
    auto dictIter = p1.bag1.rbegin();
    int maxKey = dictIter->first;

    while(it != p1.bag1.end()){        
        auto key = it->first;
        auto val = it->second;

        if((key == maxKey) && !(val % 2)){
            val = val / 2;
            p1.bag1[key] = val;
            p1.bag2[key] = val;
            break;
        }

        p1.bag1[key] -= 1;
        p1.bag2[key] += 1;
        
        if(p1.bag1 == p1.bag2){
            cout << "Yes" << endl;
            return;
        }

        if(p1.bag1[key] > 1 && p1.bag1[key] > 0){
            p1.bag1[key] = 1;
            key += 1;
            p1.bag1[key] += (val - 2);
        }


        if(p1.bag1 == p1.bag2){
            cout << "Yes" << endl;
            return;
        }
        ++it;
    }

    if(p1.bag1 == p1.bag2){
        cout << "Yes" << endl;
    }
    else{
        cout << "No" << endl;
    }
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int count;
    cin >> count;
    while(count--){
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

        solution(p);
    }
    return 0;
}