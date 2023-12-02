#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <bits.h>
#include <sstream>

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

int main() {
    ifstream myFile;
    myFile.open(R"(C:\Users\erwinia\CLionProjects\AoC2023\input.txt)");

    vector<string> input;
    while(myFile){
        auto* line = new string;
        getline(myFile, *line);
        input.push_back(*line);
    }

    cout << input.size();
}
