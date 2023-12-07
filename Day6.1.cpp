#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <sstream>

using namespace std;

int main() {
    vector<long long> times = {56977875};
    vector<long long> distances = {546192711311139};

    long long score = 1;
    for(int i = 0; i < times.size(); i++){
        long long ways = 0;
        long long time = times[i];
        for(int j = 0; j < time; j++){
            if(j * (time - j) > distances[i]){
                ways++;
            }
        }
        score *= ways;
    }

    cout << score;
}
