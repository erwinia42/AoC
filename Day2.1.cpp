#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <bits.h>
#include <sstream>
#include <map>

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

    vector < vector < vector < tuple < string, int >> >> input;

    while (myFile) {
        auto *line = new string;
        getline(myFile, *line);
        if (line->empty()) {
            continue;
        }

        string game = line->substr(line->find(':') + 2);

        vector <string> draws = split(game, "; ");
        auto *entry = new vector <vector<tuple < string, int>> >;
        for (const string &draw: draws) {
            auto *draw_vector = new vector <tuple<string, int>>;
            vector <string> colors = split(draw, ", ");
            for (const string &color: colors) {
                vector <string> separate = split(color, " ");
                draw_vector->emplace_back(separate[1], stoi(separate[0]));
            }
            entry->push_back(*draw_vector);
        }
        input.push_back(*entry);
    }

    int score = 0;
    map<string, int> limits = {
            make_pair("red", 12),
            make_pair("green", 13),
            make_pair("blue", 14)
    };
    for (int i = 0; i < input.size(); i++) {
        bool valid = true;
        for (auto draw: input[i]) {
            for (auto color: draw) {
                if (limits[get<0>(color)] < get<1>(color)) {
                    valid = false;
                    break;
                }
            }
            if (!valid) {
                break;
            }
        }
        if (valid) {
            score += i + 1;
        }
    }

    cout << score;
}
