#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <sstream>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

vector<string> input;

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

bool valid(int y, int x){
    return y >= 0 and y < input.size() and x >= 0 and x < input[0].size() and input[y][x] != '#';
}

int main() {
    ifstream myFile;
    myFile.open(R"(/home/erwinia/CLionProjects/AoC/input.txt)");

    int y = 0;
    pair<int, int> start;
    while(myFile){
        auto* line = new string;
        getline(myFile, *line);
        if(line->empty()){
            continue;
        }
        if(line->find('S') != string::npos){
            start = {y, line->find('S')};
        }
        input.push_back(*line);
        y++;
    }

    set<pair<int, int>> searching;
    searching.insert(start);
    vector<pair<int, int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    int steps = 64;
    for(int i = 0; i < steps; i++){
        set<pair<int, int>> next;
        for(pair<int, int> pos:searching){
            for(pair<int, int> dir:dirs){
                int newY = pos.first + dir.first;
                int newX = pos.second + dir.second;
                if(valid(newY, newX)){
                    next.insert({newY, newX});
                }
            }
        }
        searching = next;
    }

    cout << searching.size();
}

