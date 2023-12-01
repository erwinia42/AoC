
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <bits.h>
#include <sstream>
#include <cctype>

using namespace std;

int main() {
    ifstream myFile;
    myFile.open(R"(C:\Users\erwinia\CLionProjects\AoC2023\input.txt)");

    vector<string> input;
    while(myFile){
        auto* line = new string;
        getline(myFile, *line);
        if(!line->empty()) {
            input.push_back(*line);
        }
    }

    int sum = 0;
    for(const string& entry:input) {
        int first = -1, last = -1;
        for (char c: entry) {
            if(isdigit(c)){
                last = c - '0';
                if(first == -1){
                    first = last;
                }
            }
        }
        sum += first * 10 + last;
    }

    cout << sum;
}
