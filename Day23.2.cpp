#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <sstream>
#include <map>
#include <algorithm>
#include <queue>
#include <bitset>

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

int free_around(int y, int x, const vector<string>& input){
    int free = 0;
    for(auto dir: dirs){
        if(valid(y+dir.first, x+dir.second, input)){
            free++;
        }
    }
    return free;
}

int dist(pair<int, int> start, pair<int, int> goal, const vector<string>& input){
    int size = input.size();
    vector<vector<bool>> visited = vector<vector<bool>>(size, vector<bool>(size, false));
    queue<tuple<int, int, int>> searching;
    searching.emplace(0, start.first, start.second);

    while(!searching.empty()){
        tuple<int, int, int> curr = searching.front();
        searching.pop();

        int val = get<0>(curr);
        int y = get<1>(curr);
        int x = get<2>(curr);

        if(make_pair(y, x) == goal) {
            return val;
        }else if(visited[y][x] || (make_pair(y, x) != start && free_around(y, x, input) > 2)){
            continue;
        }else{
            visited[y][x] = true;
        }

        for(auto dir:dirs){
            int newY = y + dir.first;
            int newX = x + dir.second;
            if(valid(newY, newX, input)){
                searching.emplace(val + 1, newY, newX);
            }
        }
    }
    return -INT32_MAX;
}

int dfs(int start, int goal, map<int, vector<pair<int, int>>> &graph){
    bitset<40> visited;
    visited.set(0, true);
    vector<tuple<int, int, bitset<40>>> searching = {{start, 0, visited}};
    int max_dist = 0;

    while(!searching.empty()){
        tuple<int, int, bitset<40>> curr = searching.back();
        searching.pop_back();

        int node = get<0>(curr);
        int dist = get<1>(curr);
        visited = get<2>(curr);

        if(node == goal){
            max_dist = max(max_dist, dist);
            continue;
        }

        for(auto neighbour:graph[node]){
            if(visited[neighbour.first]){
                continue;
            }
            visited[neighbour.first] = true;
            searching.emplace_back(neighbour.first, dist + neighbour.second, visited);
            visited[neighbour.first] = false;
        }
    }
    return max_dist;
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
    vector<pair<int, int>> junctions = {{0, 1}, {size - 1, size - 2}};

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(!valid(i, j, input)){
                continue;
            }
            if(free_around(i, j, input) > 2){
                junctions.emplace_back(i, j);
            }
        }
    }

    map<int, vector<pair<int, int>>> graph;

    for(int i = 0; i < junctions.size(); i++){
        for(int j = i + 1; j < junctions.size(); j++){
            int distance = dist(junctions[i], junctions[j], input);
            if(distance > 0){
                graph[i].emplace_back(j, distance);
                graph[j].emplace_back(i, distance);
            }
        }
    }

    map<pair<int, long long>, int> dp;
    int score = dfs(0, 1, graph);

    cout << score;
}
