#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

template <class T>
void print(const vector<T>& input) {
    for (const T& elem : input) {
        cout << elem << " ";
    }
    cout << "\n";
}

int main() {
    string problem, verdict;
    int time;
    unordered_map<string, vector<int>> mp;
    unordered_set<string> correct;

    cin >> time;
    while (time != -1) {
        cin >> problem >> verdict;
        if (correct.count(problem) > 0) {
            cin >> time;
            continue;
        }
        if (verdict == "right") correct.insert(problem);

        if (mp.find(problem) == mp.end()) {
            vector<int> temp;
            temp.push_back(time);
            mp[problem] = temp;
        }
        else {
            mp[problem].push_back(time); 
        }
        cin >> time;
    }
    int score = 0;
    for (const auto& p : correct) {
        score = score + mp[p][mp[p].size() - 1] + 20 * (mp[p].size() - 1);
    }
    cout << correct.size() << " " << score << endl;
    return 0;
}
