#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <sstream>
#include <map>
#include <algorithm>
#include <queue>
#include <set>

using namespace std;

typedef tuple<int, int, int> t3;

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
        input.push_back(split(*line, " "));
    }

    long long y = 0;
    long long x = 0;
    priority_queue<t3, vector<t3>, greater<>> edges;

    for(vector<string> entry:input){
        string data = entry[2];
        string hex = data.substr(2, data.length()-4);
        char dir = data[data.length()-2];
        string color = entry[2];

        long long steps = 0;
        for(char c:hex){
            if(c < 'a'){
                steps += c - '0';
            }else{
                steps += c - 'a' + 10;
            }
            steps *= 16;
        }
        steps /= 16;

        //Debug
        //steps = stoi(entry[1]);
        //dir = entry[0][0];

        if(dir == '0' or dir == 'R'){
            edges.emplace(y, x, x + steps);
            x += steps;
        }else if(dir == '1' or dir == 'D'){
            y += steps;
        }else if(dir == '2' or dir == 'L'){
            edges.emplace(y, x - steps, x);
            x -= steps;
        }else if(dir == '3' or dir == 'U'){
            y -= steps;
        }else{
            cout << "Shouldn't be here" << endl;
        }
    }

    long long prevHeight = -1;
    vector<pair<long long, long long>> ranges;

    long long score = 0;
    while(!edges.empty()){
        t3 edge = edges.top();
        edges.pop();
        long long height = get<0>(edge);
        long long edgeLeft = get<1>(edge);
        long long edgeRight = get<2>(edge);

        for(auto range:ranges) {
            score += (range.second - range.first + 1) * (height - prevHeight);
        }
        prevHeight = height;

        //Check for meld
        bool done = false;
        for(int i = 0; i < ranges.size(); i++){
            pair<long long, long long> r1 = ranges[i];
            for(int j = i + 1; j < ranges.size(); j++){
                pair<long long, long long> r2 = ranges[j];
                if(edgeLeft == min(r1.second, r2.second) and edgeRight == max(r1.first, r2.first)){
                    score += max(r1.first, r2.first) - min(r1.second, r2.second) - 1;
                    ranges.erase(ranges.begin()+j);
                    ranges.erase(ranges.begin()+i);
                    ranges.emplace_back(min(r1.first, r2.first), max(r1.second, r2.second));
                    done = true;
                    break;
                }
            }
            if(done){
                break;
            }
        }
        if(done){
            continue;
        }
        //No meld
        for(int i = 0; i < ranges.size(); i++){
            auto &range = ranges[i];
            //Split
            if(edgeLeft > range.first and edgeRight < range.second){
                long long left = range.first;
                long long right = range.second;
                ranges.emplace_back(left, edgeLeft);
                ranges.emplace_back(edgeRight, right);
                ranges.erase(ranges.begin()+i);
                done = true;
                break;
            }
            //Close
            else if(edgeLeft == range.first and edgeRight == range.second){
                ranges.erase(ranges.begin()+i);
                done = true;
                break;
            }
            //Expand right
            else if(edgeLeft == range.second){
                score += (edgeRight - range.second);
                range.second = edgeRight;
                done = true;
                break;
            }
            //Expand left
            else if(edgeRight == range.first){
                score += (range.first - edgeLeft);
                range.first = edgeLeft;
                done = true;
                break;
            }
            //Contract right
            else if(edgeLeft == range.first){
                range.first = edgeRight;
                done = true;
                break;
            }
            //Contract left
            else if(edgeRight == range.second){
                range.second = edgeLeft;
                done = true;
                break;
            }
        }
        if(!done){
            score += edgeRight - edgeLeft + 1;
            ranges.emplace_back(edgeLeft, edgeRight);
        }
    }
    cout << score;
}
