#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <sstream>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

vector<string> input;

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

int mod(int x, int y){
    int t = x - ((x / y) * y);
    if (t < 0) t += y;
    return t;
}

bool valid(int y, int x){
    return input[mod(y, input.size())][mod(x, input[0].size())] != '#';
}

int main() {
    ifstream myFile;
    myFile.open(R"(/home/erwinia/CLionProjects/AoC/input.txt)");

    int y = 0;
    pair<int, int> start;
    while(myFile){
        auto* line = new string;
        getline(myFile, *line);
        if(line->empty()){
            continue;
        }
        if(line->find('S') != string::npos){
            start = {y, line->find('S')};
        }
        input.push_back(*line);
        y++;
    }

    set<pair<int, int>> searching;
    set<pair<int, int>> visited;
    searching.insert(start);
    vector<pair<int, int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    int steps = 26501365;
    long long odd_score = 0;
    long long even_score = 1;

    int width = input.size();
    int remainder = steps % width;
    int v1 = remainder;
    int v2 = remainder + width;
    int v3 = remainder + 2 * width;
    vector<long long> points;
    for(int i = 0; i <= v3; i++){
        if((i - remainder) % width == 0) {
            if(i % 2 == 0){
                cout << even_score << endl;
                points.push_back(even_score);
            }else{
                cout << odd_score << endl;
                points.push_back(odd_score);
            }
        }
        set<pair<int, int>> next;
        for(pair<int, int> pos:searching){
            visited.insert(pos);
            for(pair<int, int> dir:dirs){
                int newY = pos.first + dir.first;
                int newX = pos.second + dir.second;
                if(valid(newY, newX) and !visited.contains({newY, newX})){
                    next.insert({newY, newX});
                }
            }
        }
        searching = next;
        if(i % 2 == 0){
            odd_score += next.size();
        }else{
            even_score += next.size();
        }
    }

    //Thanks AoC reddit
    long long y0 = points[0];
    long long y1 = points[1];
    long long y2 = points[2];

    long long a = (y2+y0-2*y1)/2;
    long long b = y1-y0 -a;
    long long c = y0;
    long long n = steps / width;

    cout << a << "," << b << "," << c << "," << n << endl;

    long long ans = a * n * n + b * n + c;
    cout << ans;
}

