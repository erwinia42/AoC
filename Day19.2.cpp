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
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;

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

vector<int> parse_part(string part){
    vector<int> result;
    while(true){
        int start = part.find('=');
        int end = part.find(',');
        string s = part.substr(start+1, end - start-1);
        result.push_back(stoi(s));
        if(end == -1){
            break;
        }
        part = part.substr(end+1);
    }
    return result;
}

map<char, int> feature_map{
        {'x', 0},
        {'m', 1},
        {'a', 2},
        {'s', 3}
};

void parse_rule(string rule, const vvi& ranges, map<vvi, string> &result, map<string, string> wf){
    if(rule.size() == 1){
        result[ranges] = rule;
        return;
    }
    if(rule.size() <= 3){
        parse_rule(wf[rule], ranges, result, wf);
        return;
    }
    int feature = feature_map[rule[0]];
    char comparator = rule[1];
    int val = stoi(rule.substr(2, rule.find(':')-2));
    rule = rule.substr(rule.find(':')+1);
    string choice1 = rule.substr(0, rule.find(','));
    string choice2 = rule.substr(rule.find(',') + 1);

    if(comparator == '<'){
        vvi new_range = ranges;
        new_range[feature] = {new_range[feature][0], val-1};
        parse_rule(choice1, new_range, result, wf);
        new_range = ranges;
        new_range[feature] = {val, new_range[feature][1]};
        parse_rule(choice2, new_range, result, wf);
    }else{
        vvi new_range = ranges;
        new_range[feature] = {val + 1, new_range[feature][1]};
        parse_rule(choice1, new_range, result, wf);
        new_range = ranges;
        new_range[feature] = {new_range[feature][0], val};
        parse_rule(choice2, new_range, result, wf);
    }
}


int main() {
    ifstream myFile;
    myFile.open(R"(/home/erwinia/CLionProjects/AoC/input.txt)");

    map<string, string> workflows;
    vector<vector<int>> parts;
    bool part_parse = false;
    while(myFile){
        string line = *new string;
        getline(myFile, line);
        if(line.empty()){
            part_parse = true;
            continue;
        }
        if(!part_parse) {
            string name = line.substr(0, line.find('{'));
            string rules = line.substr(line.find('{')+1, line.find('}')-line.find('{')-1);
            workflows[name] = rules;
        }else{
            parts.push_back(parse_part(line));
        }
    }


    vvi ranges = {
            {1,4000},
            {1,4000},
            {1,4000},
            {1,4000}
    };

    map<vvi, string> result;
    parse_rule(workflows["in"], ranges, result, workflows);

    long long score = 0;
    map<vvi, string>::iterator it;
    for(it = result.begin(); it != result.end(); it++){
        if(it->second == "R"){
            continue;
        }

        long long combinations = 1;
        for(auto range: it->first){
            int start = range[0];
            int end = range[1];
            combinations *= (end - start + 1);
        }
        score += combinations;
    }
    cout << score;
}
