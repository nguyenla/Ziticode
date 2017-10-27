#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool isPalindrome(const string& word) {
    int i = 0;
    while (i < word.length() - 1 - i) {
        if (word[i] != word[word.length() - 1 - i]) return false;
        ++i;
    }
    return true;
}

int main() {
    string word;
    while (getline(cin, word)) {
        set<string> words;
        for (int i = 0; i < word.length() - 1; ++i) {
            for (int j = i + 2; j <= word.length() ; ++j) {
                if (isPalindrome(word.substr(i, j - i))) {
                    words.insert(word.substr(i, j - i));
                }
            }
        }
        vector<string> sorted;
        for (auto it = words.begin(); it != words.end(); ++it) {
            sorted.push_back(*it);
        }
        sort(sorted.begin(), sorted.end());
        for (int i = 0; i < sorted.size(); ++i) {
            cout << sorted[i] << '\n';
        }
        cout << '\n';
    }
    return 0;
}
