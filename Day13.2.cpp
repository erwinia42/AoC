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

vector<vector<char>> rotate(vector<vector<char>> vec){
    vector<vector<char>> newVec(vec[0].size());
    for(int i = 0; i < vec[0].size(); i++){
        vector<char> newRow(vec.size());
        for(int j = 0; j < vec.size(); j++){
            newRow[j] = vec[j][i];
        }
        newVec[i] = newRow;
    }
    return newVec;
}

vector<int> reflections(vector<vector<char>> vec){
    vector<int> reflections;
    for(int i = 0; i < vec.size()-1; i++){
        bool is_reflection = true;
        for(int j = 0; j <= i && i+j+1 < vec.size(); j++){
            if(vec[i-j] != vec [i+j+1]){
                is_reflection = false;
                break;
            }
        }
        if(is_reflection){
            reflections.push_back(i+1);
        }
    }
    return reflections;
}

int main() {
    ifstream myFile;
    myFile.open(R"(/home/erwinia/CLionProjects/AoC/input.txt)");

    vector<vector<vector<char>>> input;
    while(myFile){
        vector<vector<char>> grid;
        while(true) {
            auto* line = new string;
            getline(myFile, *line);
            if (line->empty()) {
                break;
            }
            vector<char> cLine(line->begin(), line->end());
            grid.push_back(cLine);
        }
        input.push_back(grid);
    }

    int score = 0;
    for(const auto & grid : input) {
        vector<int> og_row_reflections = reflections(grid);
        vector<int> og_col_reflections = reflections((rotate(grid)));
        for(int i = 0; i < grid.size(); i++) {
            for(int j = 0; j < grid[0].size(); j++) {
                vector<vector<char>> grid_copy = grid;
                grid_copy[i][j] = (grid[i][j] == '#') ? '.' : '#';
                vector<int> row_reflections = reflections(grid_copy);
                vector<int> col_reflections = reflections(rotate(grid_copy));
                for(auto row: row_reflections){
                    if(std::find(og_row_reflections.begin(), og_row_reflections.end(), row) == og_row_reflections.end()){
                        score += 100 * row;
                        og_row_reflections.push_back(row);
                    }
                }
                for(auto col: col_reflections){
                    if(std::find(og_col_reflections.begin(), og_col_reflections.end(), col) == og_col_reflections.end()){
                        score += col;
                        og_col_reflections.push_back(col);
                    }
                }
            }
        }
    }
    cout << score;
}
