#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int selfSimilarDegree(const string& input) {
    for (int i = input.size() - 1; i > 0; --i) {
        bool is_correct = true;
        unordered_map<string, int> mp;
        for (int j = 0; j < input.size() - i + 1; ++j) {
            string cur = input.substr(j, i);
            if (mp.find(cur) == mp.end()) {
                mp[cur] = 1;
            }
            else {
                ++mp[cur];
            }
        }

        for (const auto& item : mp) {
            if (item.second <= 1) is_correct = false;
        }
        if (is_correct) return i;
    }
    return 0;
}

int main() {
    string line;
    while (getline(cin, line)) { 
        cout << selfSimilarDegree(line) << endl;
    }
    return 0;
}
