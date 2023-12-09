#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;

vector <int> split(string s, const string &del) {
    vector <int> ret;
    string holder;
    while (true) {
        holder = s.substr(0, s.find(del));
        ret.push_back(stoi(holder));
        if (s.find(del) == -1) {
            break;
        }
        s = s.substr(s.find(del) + del.size());
    }
    return ret;
}

int getNext(vector<int> nums){
    vector<int> current = nums;
    vector<vector<int>> diffs = {nums};
    while(true){

        auto *next = new vector<int>;
        bool allzero = true;
        for(int i = 0; i < current.size() - 1; i++) {
            int diff = current[i + 1] - current[i];
            if (diff) {
                allzero = false;
            }
            next->push_back(diff);
        }
        current = *next;
        diffs.push_back(current);
        if(allzero){
            break;
        }
    }

    int retVal = 0;
    for(int i = diffs.size()-1; i>=0; i--){
        retVal = diffs[i][0] - retVal;
    }
    return retVal;
}

int main() {
    ifstream myFile;
    myFile.open(R"(/home/erwinia/CLionProjects/AoC/input.txt)");

    vector<vector<int>> input;
    while(myFile){
        auto* line = new string;
        getline(myFile, *line);
        if(line->empty()){
            continue;
        }
        input.push_back(split(*line, " "));
    }

    int score = 0;
    for(auto line: input){
        score += getNext(line);
    }
    cout << score;
}
