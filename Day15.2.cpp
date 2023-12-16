#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;

vector <string> split(string s, const string &del) {
    vector <string> ret;
    string holder;
    while (true) {
        holder = s.substr(0, s.find(del));
        ret.push_back(holder);
        if (s.find(del) == -1) {
            break;
        }
        s = s.substr(s.find(del) + del.size());
    }
    return ret;
}

int main() {
    ifstream myFile;
    myFile.open(R"(/home/erwinia/CLionProjects/AoC/input.txt)");

    vector<vector<string>> input;
    while(myFile){
        auto* line = new string;
        getline(myFile, *line);
        if(line->empty()){
            continue;
        }
        input.push_back(split(*line, ","));
    }

    vector<vector<pair<string, int>>> boxes(256, vector<pair<string, int>>());
    for(const string& entry:input[0]){
        long long hash = 0;
        char operation;
        string name;
        for(char c:entry){
            if(c == '-' or c == '='){
                name = entry.substr(0, entry.find(c));
                operation = c;
                break;
            }
            hash += c;
            hash *= 17;
            hash %= 256;
        }


        if(operation == '='){
            bool found = false;
            int strength = stoi(entry.substr(entry.find('=')+1, 1));
            for(pair<string, int> &lens: boxes[hash]){
                if(lens.first == name){
                    lens.second = strength;
                    found = true;
                    break;
                }
            }
            if(!found){
                boxes[hash].emplace_back(name, strength);
            }
        }else if(operation == '-'){
            bool found = false;
            int strength = -1;
            for(const pair<string, int>& lens: boxes[hash]){
                if(lens.first == name){
                    strength = lens.second;
                    found = true;
                    break;
                }
            }
            if(found){
                boxes[hash].erase(remove(boxes[hash].begin(), boxes[hash].end(), make_pair(name, strength)), boxes[hash].end());
            }
        }else{
            cout << "shouldnt be here";
        }
    }

    long long score = 0;
    int counter = 0;
    for(auto box:boxes){
        counter++;
        if(box.size() == 0){
            continue;
        }
        long long partial_score = 0;
        for(int lens_number = 0; lens_number < box.size(); lens_number++){
            auto lens = box[lens_number];
            partial_score += lens.second * counter * (lens_number + 1);
        }
        score += partial_score;
    }

    cout << score;
}
