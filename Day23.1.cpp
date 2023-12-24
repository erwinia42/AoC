#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <sstream>
#include <map>
#include <algorithm>
#include <queue>

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

map<char, pair<int, int>> restricted_dirs = {
        {'>', {0, 1}},
        {'<', {0, -1}},
        {'^', {-1, 0}},
        {'v', {1, 0}}
};

vector<pair<int, int>> dirs = {
        {0, 1},
        {0, -1},
        {-1, 0},
        {1, 0}
};

bool valid(int y, int x, const vector<string> &m){
    return y >= 0 && y < m.size() and x >= 0 and x < m[0].size() and m[y][x] != '#';
}

int main() {
    ifstream myFile;
    myFile.open(R"(/home/erwinia/CLionProjects/AoC/input.txt)");

    vector<string> input;
    while(myFile){
        auto* line = new string;
        getline(myFile, *line);
        if(line->empty()){
            continue;
        }
        input.push_back(*line);
    }

    int size = input.size();
    pair<int, int> start = {0, 1};
    pair<int, int> start_dir = {1 , 0};
    pair<int, int> goal = {size - 1, size - 2};

    queue<tuple<int, pair<int, int>, pair<int, int>>> searching;
    searching.emplace(0, start, start_dir);

    while(!searching.empty()){
        tuple<int, pair<int, int>, pair<int, int>> curr = searching.front();
        searching.pop();

        int val = get<0>(curr);
        int y = get<1>(curr).first;
        int x = get<1>(curr).second;
        int yDir = get<2>(curr).first;
        int xDir = get<2>(curr).second;

        if(make_pair(y, x) == goal){
            cout << val << endl;
        }

        if(restricted_dirs.find(input[y][x]) != restricted_dirs.end()){
            pair<int, int> dir = restricted_dirs[input[y][x]];
            if(valid(y+dir.first, x+dir.second, input) && dir != make_pair(-yDir, -xDir)){
                searching.emplace(val + 1, make_pair(y+dir.first, x+dir.second), dir);
            }
        }else{
            for(pair<int, int> dir:dirs){
                if(valid(y+dir.first, x+dir.second, input) && dir != make_pair(-yDir, -xDir)){
                    searching.emplace(val + 1, make_pair(y+dir.first, x+dir.second), dir);
                }
            }
        }

    }
}
