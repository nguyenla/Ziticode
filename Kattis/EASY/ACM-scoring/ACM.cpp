#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int min;
    char problem;
    string verdict;
    long time = 0;
    int num_correct = 0;
    map<char, int> res;

    cin >> min;

    while (min != -1) {
        cin >> problem >> verdict;
        
        // if the answer is right
        if (verdict == "right") {
            if (res.find(problem) != res.end() && res[problem] != -1) {
                time = time + min + res[problem] * 20;
                res[problem] = -1;
                ++num_correct;
            }
            else if (res.find(problem) == res.end()) {
                time += min;
                ++num_correct;
            }
        }
        else {
            if (res.find(problem) == res.end()) {
                res[problem] = 1;
            }
            else if (res[problem] != -1) {
                res[problem] = res[problem] + 1;
            }
        }
        cin >> min;
    }
    cout << num_correct << " " << time;
    return 0;
}
