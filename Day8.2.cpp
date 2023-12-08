#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <sstream>
#include <map>
#include <algorithm>
#include <cassert>
#include <numeric>

using namespace std;

typedef vector<int> vi;
typedef vector<vector<int>> vvi;

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

    string directions = input[0];

    map<string, vector<string>> m;
    vector<string> anodes;
    vector<string> znodes;
    for(int i = 1; i < input.size(); i++){
        vector<string> temp = split(input[i], " = (");
        vector<string> choices = split(temp[1], ", ");
        choices[1] = choices[1].substr(0, choices[1].size()-1);
        m.insert({temp[0], choices});
        if(temp[0][2] == 'A'){
            anodes.push_back(temp[0]);
        }else if(temp[0][2] == 'Z'){
            znodes.push_back(temp[0]);
        }
    }

    vector<long long> cycles;
    vector<vector<long long>> hits;
    for(auto anode: anodes) {
        string current = anode;
        int counter = 0;
        long long big_counter = 0;
        map<int, vector<string>> state_map;
        auto *hit = new vector<long long>;

        while (true) {
            vector<string> state = state_map[counter];

            if(std::find(state.begin(), state.end(), current) != state.end()) {
                hits.push_back(*hit);
                break;
            }
            if(current[2] == 'Z'){
                hit->push_back(big_counter);
                state_map[counter].push_back(current);
            }
            char dir = directions[counter];
            if (dir == 'R') {
                current = m[current][1];
            } else {
                current = m[current][0];
            }
            big_counter++;
            counter++;
            counter %= directions.size();
        }

        cout << big_counter << endl;
    }
    long long answer = hits[0][0];
    for(auto hit : hits){
        answer = lcm(answer, hit[0]);
        cout << answer << endl;
    }
    cout << answer;
}
