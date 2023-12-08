#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <sstream>
#include <map>
#include <algorithm>

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
    for(int i = 1; i < input.size(); i++){
        vector<string> temp = split(input[i], " = (");
        vector<string> choices = split(temp[1], ", ");
        choices[1] = choices[1].substr(0, choices[1].size()-1);
        m.insert({temp[0], choices});
    }

    string current = "AAA";
    int counter = 0;
    long long big_counter = 0;
    while(current != "ZZZ"){
        char dir = directions[counter];
        if(dir == 'R'){
            current = m[current][1];
        }else{
            current = m[current][0];
        }
        big_counter++;
        counter++;
        counter %= directions.size();
    }

    cout << big_counter;
}
