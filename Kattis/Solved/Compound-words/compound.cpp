#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    string word;
    vector<string> words;
    while (cin >> word) {
        words.push_back(word);
    }

    set<string> res;
    for (int i = 0; i < words.size(); ++i) {
        for (int j = 0; j < words.size(); ++j) {
            if (i == j) continue;
            string wi(words.at(i));
            string wj(words.at(j));
            res.insert(wi + wj);
        }
    }

    vector<string> sorted;
    for (auto it = res.begin(); it != res.end(); ++it) {
        sorted.push_back(*it);
    }

    sort(sorted.begin(), sorted.end());
    for (int i = 0; i < sorted.size(); ++i) {
        cout << sorted[i] << '\n';
    }

    return 0;
}
