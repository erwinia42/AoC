#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <sstream>
#include <set>
#include <map>

using namespace std;

vector <string> split(string s, const string &del) {
    vector <string> ret;
    string holder;
    while (true) {
        holder = s.substr(0, s.find(del));
        if(!holder.empty()){
            ret.push_back(holder);
        }
        if (s.find(del) == -1) {
            break;
        }
        s = s.substr(s.find(del) + del.size());
    }
    return ret;
}

vector<int> numerize(const vector<string> &v){
    vector<int> n;
    for(const auto& e: v){
        n.push_back(stoi(e));
    }
    return n;
}

int main() {
    ifstream myFile;
    myFile.open(R"(/home/erwinia/CLionProjects/AoC/input.txt)");

    vector<pair<vector<int>, vector<int>>> input;
    while(myFile){
        auto* line = new string;
        getline(myFile, *line);
        if(line->empty()){
            continue;
        }

        string card = line->substr(line->find(':') + 2);
        vector<string> s = split(card, " | ");
        vector<string> winning = split(s[0], " ");
        vector<string> have = split(s[1], " ");
        input.emplace_back(numerize(winning), numerize(have));
    }

    int sum = 0;
    map<int, int> running;
    for(int i = 0; i < input.size(); i++){
        int wins = 0;
        vector<int> cards = input[i].second;
        vector<int> winning = input[i].first;
        int copies = running[i] + 1;
        for(auto card: cards){
            if(std::find(winning.begin(), winning.end(), card) != winning.end()){
                wins++;
            }
        }
        for(int j = i + 1; j < min(i + 1 + wins, (int)input.size()); j++){
            running[j] += copies;
        }
        sum += wins * copies + 1;
    }

    cout << sum;
}
