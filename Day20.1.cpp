#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;

map<string, pair<char, vector<string>>> outputs;
map<string, map<string, int>> inverter_memories;
map<string, int> switch_memories;
vector<long long> pulses = {0, 0};

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

auto pulse(string input_node, string prev, int level){
    pulses[level]++;

    pair<char, vector<string>> output = outputs[input_node];
    char type = output.first;
    vector<string> nodes = output.second;
    int output_level = 0;

    vector<tuple<string, string, int>> return_vector;

    if(type == '%'){
        if(level == 1){
            return return_vector;
        }else{
            switch_memories[input_node] = !switch_memories[input_node];
            output_level = switch_memories[input_node];
        }
    }else if(type == '&'){
        inverter_memories[input_node][prev] = level;
        if(!all_of(inverter_memories[input_node].begin(),
                  inverter_memories[input_node].end(),
                  [](const pair<string, int>& entry){
            return entry.second == 1;
        })){
            output_level = 1;
        }
    }

    for(string output_node:output.second){
        return_vector.emplace_back(output_node, input_node, output_level);
    }
    return return_vector;
}


int main() {
    ifstream myFile;
    myFile.open(R"(/home/erwinia/CLionProjects/AoC/input.txt)");


    while(myFile){
        auto* line = new string;
        getline(myFile, *line);
        if(line->empty()){
            continue;
        }
        vector<string> description = split(*line, " -> ");
        char type = description[0][0];
        string name = description[0].substr(1);
        vector<string> output = split(description[1], ", ");
        outputs[name] = {type, output};
        if(type == '%'){
            switch_memories[name] = 0;
        }
        for(auto o:output){
            inverter_memories[o][name] = 0;
        }
    }



    for(int i = 0; i < 1000; i++){
        vector<tuple<string, string, int>> to_activate = {{"roadcaster", "", 0}};
        while(!to_activate.empty()){
            vector<tuple<string, string, int>> new_activate;
            for(auto activation:to_activate){
                string curr = get<0>(activation);
                string prev = get<1>(activation);
                int level = get<2>(activation);
                auto new_a = pulse(curr, prev, level);
                new_activate.insert(new_activate.end(), new_a.begin(), new_a.end());
            }
            to_activate = new_activate;
        }
    }

    cout << pulses[0] * pulses[1] << endl;
}

