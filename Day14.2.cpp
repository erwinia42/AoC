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
            newRow[j] = vec[vec.size()-j-1][i];
        }
        newVec[i] = newRow;
    }
    return newVec;
}

void slide(vector<vector<char>> &vec){
    for(int i = 0; i < vec[0].size(); i++){
        vector<char> newCol(vec.size(), '.');
        int row = 0;
        int pointer = 0;
        while(row < vec.size()){
            if(vec[row][i] == '#') {
                pointer = row;
                newCol[pointer++] = '#';
            }else if(vec[row][i] == 'O'){
                newCol[pointer++] = 'O';
            }
            row++;
        }

        for(int j = 0; j < newCol.size(); j++){
            vec[j][i] = newCol[j];
        }
    }
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
    }

    map<vector<vector<char>>, vector<long long>> states;

    long long bigCounter = 0;
    long long cycleLength = 0;
    long long bigNum = 4000000000;
    bool hasCycled = false;
    while(bigCounter < bigNum){
        slide(input);
        input = rotate(input);
        for(long long prevHit: states[input]){
            if(prevHit % 4 == bigCounter % 4 and not hasCycled){
                cycleLength = bigCounter - prevHit;
                bigCounter += cycleLength * ((bigNum - bigCounter) / cycleLength);
                hasCycled = true;
            }
        }
        states[input].push_back(bigCounter);
        bigCounter++;
    }
    cout << bigCounter << endl;
    cout << cycleLength << endl;

    int score = 0;
    for(int i = 0; i < input[0].size(); i++){
        for(int row = 0; row < input.size(); row++){
            if(input[row][i] == 'O'){
                score += input.size() - row;
            }
        }
    }

    cout << score;
}
