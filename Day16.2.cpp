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

    vector<string> input;
    while(myFile){
        auto* line = new string;
        getline(myFile, *line);
        if(line->empty()){
            continue;
        }
        input.push_back(*line);
    }

    vector<pair<int,int>> startDirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    long long maxCount = 0;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < input.size(); j++) {
            vector<vector<vector<pair<int, int>>>> visited(input.size(), vector<vector<pair<int, int>>>(input[0].size(),
                                                                                                        vector<pair<int, int>>()));

            vector<tuple<pair<int, int>, pair<int, int>>> searching;
            map<int, pair<int, int>> starts = {
                    {0, {j, 0}},
                    {1, {0, j}},
                    {2, {j, input[0].size()-1}},
                    {3, {input.size()-1, j}}
            };
            pair<int, int> start = starts[i];
            pair<int, int> startDir = startDirs[i];
            searching.emplace_back(start, startDir);

            while (!searching.empty()) {
                tuple<pair<int, int>, pair<int, int>> current = searching[searching.size() - 1];
                searching.pop_back();
                pair<int, int> pos = get<0>(current);
                int y = pos.first;
                int x = pos.second;
                pair<int, int> dir = get<1>(current);
                int yDir = dir.first;
                int xDir = dir.second;

                if (find(visited[y][x].begin(), visited[y][x].end(), dir) != visited[y][x].end()) {
                    continue;
                } else {
                    visited[y][x].push_back(dir);
                }


                if (input[y][x] == '|') {
                    if (xDir != 0) {
                        if (y + 1 < input.size()) {
                            searching.push_back({{y + 1, x},
                                                 {1,     0}});
                        }
                        if (y - 1 >= 0) {
                            searching.push_back({{y - 1, x},
                                                 {-1,    0}});
                        }
                        continue;
                    }
                } else if (input[y][x] == '-') {
                    if (yDir != 0) {
                        if (x + 1 < input[0].size()) {
                            searching.push_back({{y, x + 1},
                                                 {0, 1}});
                        }
                        if (x - 1 >= 0) {
                            searching.push_back({{y, x - 1},
                                                 {0, -1}});
                        }
                        continue;
                    }
                } else if (input[y][x] == '/') {
                    int temp = xDir;
                    xDir = -yDir;
                    yDir = -temp;

                } else if (input[y][x] == '\\') {
                    int temp = xDir;
                    xDir = yDir;
                    yDir = temp;
                }
                if (y + yDir >= 0 and y + yDir < input.size() and x + xDir >= 0 and x + xDir < input[0].size()) {
                    searching.push_back({{y + yDir, x + xDir},
                                         {yDir,     xDir}});
                }
            }

            long long count = 0;
            for (auto row: visited) {
                for (auto cell: row) {
                    if (!cell.empty()) {
                        count++;
                    }
                }
            }
            maxCount = max(maxCount, count);
        }
    }
    cout << maxCount;
}
