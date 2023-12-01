
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
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

    string numbers[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    int sum = 0;
    for(const string& entry:input) {
        int first = -1, last = -1;
        for (int i = 0; i < entry.size(); i++) {
            char c = entry.at(i);
            if (isdigit(c)) {
                last = c - '0';
            } else {
                string sub = entry.substr(i, 5);
                for (int j = 0; j < 9; j++) {
                    if (sub.starts_with(numbers[j])) {
                        last = j + 1;
                    }
                }
            }
            if (first == -1) {
                first = last;
            }
        }
        sum += first * 10 + last;
    }

    cout << sum;
}
