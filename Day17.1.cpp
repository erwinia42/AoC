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

typedef tuple<int, int, int, int, int, int> t6;
typedef tuple<int, int, int, int, int> t5;

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

bool valid(int y, int x, int yLim, int xLim){
    return y >= 0 && x >= 0 && y < yLim && x < xLim;
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


    map<t5, int> visited;
    priority_queue<t6, vector<t6>, greater<>> searching;
    searching.emplace(0,0,0,0,1,3);
    searching.emplace(0,0,0,1,0,3);

    int score = INT32_MAX;
    while(!searching.empty()){
        t6 state = searching.top();
        searching.pop();

        int val = get<0>(state);
        int y = get<1>(state);
        int x = get<2>(state);
        int yDir = get<3>(state);
        int xDir = get<4>(state);
        int steps = get<5>(state);


        if(visited.find({y, x, yDir, xDir, steps}) != visited.end() && visited[{y, x, yDir, xDir, steps}] <= val){
            continue;
        }

        visited[{y, x, yDir, xDir, steps}] = val;
        if(y == input.size()-1 && x == input[0].size()-1){
            score = min(score, val);
            cout << score << endl;
        }


        if(steps > 0 && valid(y+yDir, x+xDir, input.size(), input[0].size())){
            if(visited.find({y+yDir, x+xDir, yDir, xDir, steps-1}) == visited.end() || visited[{y+yDir, x+xDir, yDir, xDir, steps-1}] >= val + input[y+yDir][x+xDir] - '0')
                searching.emplace(val + input[y+yDir][x+xDir] - '0', y+yDir, x+xDir, yDir, xDir, steps-1);
        }
        if(xDir != 0) {
            if(valid(y+1, x, input.size(), input[0].size())) {
                if(visited.find({y+1, x, 1, 0, 2}) == visited.end() || visited[{y+1, x, 1, 0, 2}] >= val + input[y+1][x] - '0')
                    searching.emplace(val + input[y + 1][x] - '0', y + 1, x, 1, 0, 2);
            }
            if(valid(y-1, x, input.size(), input[0].size())) {
                if(visited.find({y-1, x, -1, 0, 2}) == visited.end() || visited[{y-1, x, -1, 0, 2}] >= val + input[y-1][x] - '0')
                    searching.emplace(val + input[y - 1][x] - '0', y - 1, x, -1, 0, 2);
            }
        }
        if(yDir != 0) {
            if(valid(y, x+1, input.size(), input[0].size())) {
                if(visited.find({y, x+1, 0, 1, 2}) == visited.end() || visited[{y, x+1, 0, 1, 2}] >= val + input[y][x+1] - '0')
                    searching.emplace(val + input[y][x+1] - '0', y, x+1, 0, 1, 2);
            }
            if(valid(y, x-1, input.size(), input[0].size())) {
                if(visited.find({y, x-1, 0, -1, 2}) == visited.end() || visited[{y, x-1, 0, -1, 2}] >= val + input[y][x-1] - '0')
                    searching.emplace(val + input[y][x-1] - '0', y, x-1, 0, -1, 2);
            }
        }
    }
    cout << score;
}
