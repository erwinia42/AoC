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

vector<vector<char>> expandColumns(vector<vector<char>> input){
    input = rotate(input);

    for(int i = 0; i < input.size(); i++){
        vector<char> row = input[i];
        if(all_of(row.begin(), row.end(), [](char c){return c == '.';})){
            input.insert(input.begin()+i, row);
            i++;
        }
    }

    return rotate(input);
}

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
        vector<char> cLine(line->begin(), line->end());
        input.push_back(cLine);
        if(all_of(line->begin(), line->end(), [](char c){return c =='.';}))
            input.push_back(cLine);
    }

    input = expandColumns(input);

    vector<pair<int, int>> hash_coords(0);
    for(int i = 0; i < input.size(); i++){
        for(int j = 0; j < input[i].size(); j++){
            if(input[i][j] == '#'){
                hash_coords.emplace_back(i, j);
            }
        }
    }

    int distanceSum = 0;
    int count = 0;
    for(auto coord1: hash_coords){
        for(auto coord2: hash_coords){
            if(coord1 >= coord2){
                continue;
            }
            distanceSum += abs(coord1.first - coord2.first) + abs(coord1.second - coord2.second);
            count++;
        }
    }

    cout << distanceSum << endl;
}
