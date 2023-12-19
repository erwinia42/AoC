#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <sstream>
#include <map>
#include <algorithm>
#include <queue>
#include <set>

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

map<string, pair<int, int>> dirMap = {
        {"R", {0, 1}},
        {"D", {1, 0}},
        {"L", {0, -1}},
        {"U", {-1, 0}}
};

map<pair<int, int>, string> colors;

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
        input.push_back(split(*line, " "));
    }

    pair<int, int> position = {0,0};
    for(vector<string> entry:input){
        pair<int, int> dir = dirMap[entry[0]];
        int steps = stoi(entry[1]);
        string color = entry[2];

        for(int i = 0; i < steps; i++){
            position = {position.first + dir.first, position.second + dir.second};
            colors[position] = color;
        }
    }

    pair<int, int> floodStart = {1, 1};
    queue<pair<int, int>> searching;

    searching.push(floodStart);

    while(!searching.empty()){
        pair<int, int> current = searching.front();
        searching.pop();

        if(colors.find(current) != colors.end()){
            continue;
        }else {
            colors[current] = "infill";
        }

        for(pair<string, pair<int, int>> dir:dirMap){
            searching.emplace(current.first + dir.second.first, current.second + dir.second.second);
        }
    }

    cout << colors.size();
}
