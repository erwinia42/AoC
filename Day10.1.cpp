#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <sstream>
#include <map>
#include <algorithm>
#include <queue>


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

map<tuple<char, int, int>, pair<int, int>> new_direction = {
        {{'F', -1, 0}, {0, 1}},
        {{'7', -1, 0}, {0, -1}},
        {{'|', -1, 0}, {-1, 0}},
        {{'|', 1, 0}, {1, 0}},
        {{'J', 1, 0}, {0, -1}},
        {{'L', 1, 0}, {0, 1}},

        {{'F', 0, -1}, {1, 0}},
        {{'7', 0, 1}, {1, 0}},
        {{'-', 0, -1}, {0, -1}},
        {{'-', 0, 1}, {0, 1}},
        {{'J', 0, 1}, {-1, 0}},
        {{'L', 0, -1}, {-1, 0}},

};

int main() {
    ifstream myFile;
    myFile.open(R"(/home/erwinia/CLionProjects/AoC/input.txt)");

    vector<string> input;
    int counter = 0;
    tuple<int, int> start;
    while(myFile){
        auto* line = new string;
        getline(myFile, *line);
        if(line->empty()){
            continue;
        }
        if(line->find('S') != string::npos){
            start = {counter, line->find('S')};
        }
        counter++;
        input.push_back(*line);
    }

    queue<vector<int>> searching;
    vector<vector<bool>> visited = vector(input.size(), vector(input.size() ,false));

    int yStart = get<0>(start);
    int xStart = get<1>(start);

    for(int i: {-1, 0, 1}){
        for(int j:{-1, 0, 1}){
            if(abs(i) == abs(j)){
                continue;
            }
            searching.push({0, yStart, xStart, i, j});
        }
    }

    int biggest = 0;
    while(!searching.empty()){
        vector<int> current = searching.front();
        searching.pop();

        int val = current[0];
        int y = current[1];
        int x = current[2];
        int yDir = current[3];
        int xDir = current[4];

        biggest = max(biggest, val);
        int newY = y+yDir;
        int newX = x+xDir;
        char next_char = input[newY][newX];
        pair<int, int> new_dir = new_direction[{next_char, yDir, xDir}];

        if(new_dir == make_pair(0, 0)){
            continue;
        }
        if(!visited[newY][newX]) {
            searching.push({val + 1, newY, newX, new_dir.first, new_dir.second});
            visited[newY][newX] = true;
        }
    }

    cout << biggest;
}
