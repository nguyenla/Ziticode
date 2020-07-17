#include <algorithm>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

// Helper function to display vector
template <class T>
void print(const vector<T>& input) {
    for (const T& elem : input) {
        cout << elem << " ";
    }
    cout << "\n";
}

int main() {
    string line;
    bool is_first = true;

    while (getline(cin, line)) {
        if (is_first) is_first = false;
        else cout << endl;

        vector<string> words;
        unsigned long max_length = 0;
        while (line != "") {
            words.emplace_back(line);
            max_length = max(max_length, line.size());
            getline(cin, line);
        }
        // cout << max_length << endl;

        map<string, string> mp;
        for (const auto& word : words) {
            ostringstream reverse("");
            for (int i = word.size() - 1; i >= 0; --i) {
                reverse << word[i];
            }
            // cout << reverse.str() << endl;

            string formatted_word = word;
            for (int i = 0; i < max_length - word.size(); ++i) {
                formatted_word = " " + formatted_word;
            }
            mp[reverse.str()] = formatted_word;
        }

        for (const auto& item : mp) {
            cout << item.second << endl;
        }
    }
    return 0;
}
