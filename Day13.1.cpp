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

int reflections(vector<vector<char>> vec){
    int reflections = 0;
    for(int i = 0; i < vec.size()-1; i++){
        bool is_reflection = true;
        for(int j = 0; j <= i && i+j+1 < vec.size(); j++){
            if(vec[i-j] != vec [i+j+1]){
                is_reflection = false;
                break;
            }
        }
        if(is_reflection){
            reflections += i + 1;
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
    for(const auto & i : input) {
        score += 100 * reflections(i) + reflections((rotate(i)));
    }
    cout << score;


}
