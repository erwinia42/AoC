
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <sstream>

using namespace std;

bool handle_gear(vector<vector<char>> map, int y, int x);

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
        int j = 0;
        int n = input[i].size();
        while(j < n){
            while(j < n and !isdigit(input[i][j])){
                j++;
            }
            string number;
            bool valid = false;
            while(j < n and isdigit(input[i][j])){
                number.push_back(input[i][j]);
                valid = valid | handle_gear(input, i, j);
                j++;
            }
            if(valid){
                sum += stoi(number);
            }
        }
    }

    cout << sum;
}

bool handle_gear(vector<vector<char>> map, int y, int x) {
    for(int i: {-1, 0, 1}){
        for(int j: {-1, 0, 1}){
            if(i == 0 and j == 0){
                continue;
            }
            int newy = y + i, newx = x + j;
            if(newy >= 0 and newy < map.size() and newx >= 0 and newx < map[newy].size()){
                if(!isdigit(map[newy][newx]) and map[newy][newx] != '.'){
                    return true;
                }
            }
        }
    }
    return false;
}
