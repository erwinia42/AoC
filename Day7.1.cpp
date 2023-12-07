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

map<char, int> cards = {
        {'2', 2},
        {'3', 3},
        {'4', 4},
        {'5', 5},
        {'6', 6},
        {'7', 7},
        {'8', 8},
        {'9', 9},
        {'T', 10},
        {'J', 11},
        {'Q', 12},
        {'K', 13},
        {'A', 14},
};


int compareHands(string h1, string h2){
    string h1_sorted = h1;
    sort(h1_sorted.begin(), h1_sorted.end(), [&h1](char c1, char c2)
        {return count(h1.begin(), h1.end(), c1) > count(h1.begin(), h1.end(), c2);}
        );
    string h2_sorted = h2;
    sort(h2_sorted.begin(), h2_sorted.end(), [&h2](char c1, char c2)
        {return count(h2.begin(), h2.end(), c1) > count(h2.begin(), h2.end(), c2);}
    );

    if(std::count(h1.begin(), h1.end(), h1_sorted[0]) > std::count(h2.begin(), h2.end(), h2_sorted[0])){
        return true;
    }
    if(std::count(h1.begin(), h1.end(), h1_sorted[0]) < std::count(h2.begin(), h2.end(), h2_sorted[0])){
        return false;
    }

    if(std::count(h1.begin(), h1.end(), h1_sorted[0]) == 3){
        if(std::count(h1.begin(), h1.end(), h1_sorted[3]) > std::count(h2.begin(), h2.end(), h2_sorted[3])){
            return true;
        }
        if(std::count(h1.begin(), h1.end(), h1_sorted[3]) < std::count(h2.begin(), h2.end(), h2_sorted[3])){
            return false;
        }
    }

    if(std::count(h1.begin(), h1.end(), h1_sorted[0]) == 2){
        if(std::count(h1.begin(), h1.end(), h1_sorted[2]) > std::count(h2.begin(), h2.end(), h2_sorted[2])){
            return true;
        }
        if(std::count(h1.begin(), h1.end(), h1_sorted[2]) < std::count(h2.begin(), h2.end(), h2_sorted[2])){
            return false;
        }
    }

    for(int i = 0; i < h1.size(); i++){
        if(cards[h1[i]] > cards[h2[i]]){
            return true;
        }
        if(cards[h1[i]] < cards[h2[i]]){
            return false;
        }
    }

    return true;
}

int main() {
    ifstream myFile;
    myFile.open(R"(/home/erwinia/CLionProjects/AoC/input.txt)");

    vector<vector<string>> hands;
    while(myFile){
        auto* line = new string;
        getline(myFile, *line);
        if(line->empty()){
            continue;
        }
        hands.push_back(split(*line, " "));
    }

    std::sort(hands.begin(), hands.end(), [](vector<string> v1, vector<string> v2){
        bool hand1wins = compareHands(v1[0], v2[0]);
        cout << hand1wins << " " << v1[0] << " " << v2[0] << endl;
        return hand1wins;
    });

    std::reverse(hands.begin(), hands.end());
    long long score = 0;
    for(int i = 0; i < hands.size(); i++){
        score += (i + 1) * stoi(hands[i][1]);
    }
    cout << score;
    //249748283
}
