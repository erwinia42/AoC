#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;

vector <long long> split(string s, const string &del) {
    vector <long long> ret;
    string holder;
    while (true) {
        holder = s.substr(0, s.find(del));
        ret.push_back(stol(holder));
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
        input.push_back(*line);
    }

    map<pair<long long, long long>, long long> sts;
    map<pair<long long, long long>, long long> stf;
    map<pair<long long, long long>, long long> ftw;
    map<pair<long long, long long>, long long> wtl;
    map<pair<long long, long long>, long long> ltt;
    map<pair<long long, long long>, long long> tth;
    map<pair<long long, long long>, long long> htl;

    vector< map<pair<long long, long long>, long long>> maps = {sts, stf, ftw, wtl, ltt, tth, htl};

    vector<long long> seeds = split(input[0].substr(input[0].find(':') + 2), " ");

    int lineC = 1;
    int mapC = 0;

    while(true){
        lineC++;
        if(lineC >= input.size()){
            break;
        }
        lineC++;
        while(!input[lineC].empty()){
            vector<long long> mapLine = split(input[lineC], " ");
            long long dest = mapLine[1];
            long long source = mapLine[0];
            long long diff = mapLine[2];
            maps[mapC][make_pair(source, source + diff - 1)] = dest;
            lineC++;
        }
        mapC++;
    }

    long long location = 0;
    bool found = false;
    while(!found){
        if(location % 100000 == 0){
            cout << location << endl;
        }
        long long current = location;
        for(int i = maps.size() - 1; i >= 0; i--){
            for(auto pair:maps[i]){
                if(current >= pair.first.first and current <= pair.first.second){
                    current = pair.second + current - pair.first.first;
                    break;
                }
            }
        }
        long long seed = current;
        for(int i = 0; i < seeds.size(); i+=2){
            if(seed >= seeds[i] && seed < seeds[i] + seeds[i+1]){
                cout << location << endl;
                found = true;
            }
        }
        location++;
    }
}
