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

    vector<vector<string>> input;
    while(myFile){
        auto* line = new string;
        getline(myFile, *line);
        if(line->empty()){
            continue;
        }
        input.push_back(split(*line, ","));
    }

    long long score = 0;
    for(string entry:input[0]){
        long long partial_score = 0;
        for(char c:entry){
            partial_score += c;
            partial_score *= 17;
            partial_score %= 256;
        }
        score += partial_score;
    }

    cout << score;
}
