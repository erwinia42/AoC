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
        ret.push_back(holder);
        if (s.find(del) == -1) {
            break;
        }
        s = s.substr(s.find(del) + del.size());
    }
    return ret;
}

vector <int> int_split(string s, const string &del) {
    vector <int> ret;
    string holder;
    while (true) {
        holder = s.substr(0, s.find(del));
        ret.push_back(stoi(holder));
        if (s.find(del) == -1) {
            break;
        }
        s = s.substr(s.find(del) + del.size());
    }
    return ret;
}

vector<vector<long long>> dp(100, vector<long long>(10, -1));

void cleardp(){
    dp = vector<vector<long long>>(100*5, vector<long long>(10*5, -1));
}

long long placements(string row, vector<int> nums, int start, int current_num){
    if(dp[start][current_num] != -1){
        return dp[start][current_num];
    }
    if(current_num == nums.size()){
        if(start >= row.size()){
            return 1;
        }
        string sub = row.substr(start, row.size()-start);
        if(any_of(sub.begin(), sub.end(), [](char c){return c == '#';}))
            return 0;
        else
            return 1;
    }
    int next_num = nums[current_num];
    if(start + next_num > row.size()){
        return 0;
    }

    long long retVal = 0;
    int og_start = start;


    string sub = row.substr(start, next_num);
    if(sub[0] == '#') {
        if (all_of(sub.begin(), sub.end(), [](char c) { return c == '#' or c == '?'; })) {
            if (row.size() == start + next_num or row[start + next_num] != '#') {
                retVal += 1 * placements(row, nums, start + next_num + 1, current_num + 1);
            }
            return retVal;  //Must place it here
        }else{
            return 0;
        }
    }


    if(all_of(sub.begin(), sub.end(), [](char c){return c != '.';})){
        if(row.size() == start+next_num or row[start+next_num] != '#'){
            retVal += 1 * placements(row, nums, start+next_num+1, current_num+1);
        }
    }
    retVal += placements(row, nums, start + 1, current_num);


    dp[og_start][current_num] = retVal;
    return retVal;
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

    long long score = 0;
    for(auto row: input){
        cleardp();
        string big_row;
        vector<int> nums = int_split(row[1], ",");
        vector<int> big_nums;
        for(int i = 0; i < 5; i++){
            big_row += row[0];
            if(i < 4){
                big_row += "?";
            }
            big_nums.insert(big_nums.end(), nums.begin(), nums.end());
        }

        long long row_score = placements(big_row, big_nums, 0, 0);
        cout << row_score <<endl;
        score += row_score;
    }
    cout << score;
}
