#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <bits.h>
#include <sstream>

using namespace std;

int main() {
    ifstream myFile;
    myFile.open(R"(C:\Users\erwinia\CLionProjects\AoC2023\input.txt)");

    vector<vector<int>> input;
    auto *elf = new vector<int>();
    while(myFile){
        auto* line = new string;
        getline(myFile, *line);

        if(line->empty()){
            input.push_back(*elf);
            elf = new vector<int>();
        }else{
            elf->push_back(stoi(*line));
        }
    }

    cout << input.size();
}
