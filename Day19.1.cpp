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

string parse_rule(string rule, vector<int> part){
    if(rule.size() <= 3){
        return rule;
    }
    int feature = feature_map[rule[0]];
    char comparator = rule[1];
    int val = stoi(rule.substr(2, rule.find(':')-2));
    rule = rule.substr(rule.find(':')+1);
    string choice1 = rule.substr(0, rule.find(','));
    string choice2 = rule.substr(rule.find(',') + 1);

    bool answer = false;
    if(comparator == '<' and part[feature] < val
        or comparator == '>' and part[feature] > val){
        answer = true;
    }

    if(answer){
        return parse_rule(choice1, part);
    }else{
        return parse_rule(choice2, part);
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

    long long score = 0;
    for(auto part: parts){
        string rule_name = "in";
        while(rule_name.size() > 1){
            rule_name = parse_rule(workflows[rule_name], part);
        }
        if(rule_name == "A"){
            for(int val:part){
                score += val;
            }
        }
    }

    cout << score;
}
