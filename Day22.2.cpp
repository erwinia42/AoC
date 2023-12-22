#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <sstream>
#include <map>
#include <algorithm>
#include <set>
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

vector <int> int_split(string s, const string &del) {
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


int main() {
    ifstream myFile;
    myFile.open(R"(/home/erwinia/CLionProjects/AoC/input.txt)");

    vector<vector<vector<int>>> input;
    while (myFile) {
        auto *line = new string;
        getline(myFile, *line);
        if (line->empty()) {
            continue;
        }
        vector<string> bricks = split(*line, "~");
        input.push_back({int_split(bricks[0], ","), int_split(bricks[1], ",")});
    }

    std::sort(input.begin(), input.end(), [](vector<vector<int>> v1, vector<vector<int>> v2) {
        return v1[0][2] < v2[0][2];
    });

    vector<vector<int>> supporting = vector<vector<int>>(input.size(), vector<int>());
    vector<vector<int>> supported_by = vector<vector<int>>(input.size(), vector<int>());
    vector<int> low_point;

    vector<vector<pair<int, int>>> surface = vector<vector<pair<int, int>>>(10, vector<pair<int, int>>(10, make_pair(0,
                                                                                                                     -1)));

    int brick_number = 0;
    for (auto brick: input) {
        int lowX = brick[0][0];
        int lowY = brick[0][1];
        int lowZ = brick[0][2];

        int highX = brick[1][0];
        int highY = brick[1][1];
        int highZ = brick[1][2];

        set<int> bricks_below = set<int>();
        do {
            for (int x = lowX; x <= highX; x++) {
                for (int y = lowY; y <= highY; y++) {
                    pair<int, int> surface_point = surface[x][y];
                    if (surface_point.first == lowZ - 1) {
                        bricks_below.insert(surface_point.second);
                    }
                }
            }
            lowZ--;
            highZ--;
        } while (bricks_below.empty());
        lowZ++;
        highZ++;

        for (int x = lowX; x <= highX; x++) {
            for (int y = lowY; y <= highY; y++) {
                surface[x][y] = {highZ, brick_number};
            }
        }

        for (int number: bricks_below) {
            if (number < 0) {
                continue;
            }
            supported_by[number].push_back(brick_number);
            supporting[brick_number].push_back(number);
        }

        low_point.push_back(lowZ);
        brick_number++;
    }

    int score = 0;
    vector<int> redundant;
    for (brick_number = 0; brick_number < input.size(); brick_number++) {
        vector<int> supported_bricks = supported_by[brick_number];
        if (all_of(supported_bricks.begin(), supported_bricks.end(), [supporting](int b) {
            return supporting[b].size() > 1;
        })) {
            score++;
            redundant.push_back(brick_number);
        }
    }

    long long total_score = 0;
    for (brick_number = 0; brick_number < input.size(); brick_number++) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> searching;
        vector<bool> visited = vector<bool>(input.size(), false);
        vector<bool> falling = vector<bool>(input.size(), false);
        searching.emplace(low_point[brick_number], brick_number);

        while(!searching.empty()){
            pair<int, int> next = searching.top();
            int b = next.second;
            searching.pop();

            if(visited[b]){
                continue;
            }else{
                visited[b] = true;
            }

            bool will_fall = true;
            if(b != brick_number) {
                for (int ob: supporting[b]) {
                    if (!falling[ob]) {
                        will_fall = false;
                    }
                }
            }

            if(!will_fall){
                continue;
            }

            falling[b] = true;

            for(int nextB:supported_by[b]){
                searching.emplace(low_point[nextB], nextB);
            }
        }

        int score = 0;
        for(bool f:falling){
            if(f){
                score++;
            }
        }
        cout << brick_number << ", " << score << endl;
        total_score += score - 1;
    }

    cout << "Answer: " << total_score << endl;
}
