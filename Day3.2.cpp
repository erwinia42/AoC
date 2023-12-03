
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <sstream>

using namespace std;

int handle_gear(vector<vector<char>> &map, int y, int x);

vector<int> get_num(vector<vector<char>> &vector, int newy, int newx);

int main() {
    ifstream myFile;
    myFile.open(R"(/home/erwinia/CLionProjects/AoC/input.txt)");

    vector<vector<char>> input;
    while(myFile){
        auto* line = new string;
        getline(myFile, *line);
        if(line->empty()){
            continue;
        }

        auto *cv = new vector<char>;
        for(char c:*line){
            cv->push_back(c);
        }
        input.push_back(*cv);
    }

    int sum = 0;
    for(int i = 0; i < input.size(); i++){
        for(int j = 0; j < input[i].size(); j++){
            if(input[i][j] == '*'){
                sum += handle_gear(input, i, j);
            }
        }
    }

    cout << sum;
}

int handle_gear(vector<vector<char>> &map, int y, int x) {
    int count_adjacent = 0;
    vector<pair<int, int>> heads;
    int power = 1;
    for(int i: {-1, 0, 1}){
        for(int j: {-1, 0, 1}){
            if(i == 0 and j == 0){
                continue;
            }
            int newy = y + i, newx = x + j;
            if(newy >= 0 and newy < map.size() and newx >= 0 and newx < map[newy].size()){
                if(isdigit(map[newy][newx])){
                    vector<int> v = get_num(map, newy, newx);
                    int n = v[0], heady = v[1], headx = v[2];
                    if(find(heads.begin(), heads.end(), make_pair(heady, headx)) == heads.end()){
                        count_adjacent++;
                        heads.emplace_back(heady, headx);
                        power *= n;
                    }
                }
            }
        }
    }
    if(count_adjacent == 2) {
        return power;
    }
    return 0;
}

vector<int> get_num(vector<vector<char>> &map, int y, int x) {
    string val;
    int ogx = x;
    while(x >= 0 and isdigit(map[y][x])){
        val.push_back(map[y][x--]);
    }
    std::reverse(val.begin(), val.end());
    int headx = x;
    x = ogx + 1;
    while(x < map[y].size() and isdigit(map[y][x])){
        val.push_back(map[y][x++]);
    }
    return {stoi(val), y, headx};
}
