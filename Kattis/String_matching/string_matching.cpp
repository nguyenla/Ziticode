#include <algorithm>
#include <exception>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

// Helper function to display vector
void print(const vector<int>& input) {
    for (const int num : input) {
        cout << num << " ";
    }
    cout << "\n";
}

// Compute the length of the longest string that are both prefix and suffix of
// each prefix S[0 ... i]
vector<int> lps_array(const string& input) {
    int length = input.length();
    vector<int> lps_array(length, 0);

    int cur_longest = 0; // current longest border of the string up to pos
    int pos = 1;
    while (pos < length) {
        if (input[pos] == input[cur_longest]) {
            lps_array[pos] = ++cur_longest;
        }
        else {
            // Go to the longest border of the current longest border
            while (cur_longest > 0 && input[cur_longest] != input[pos]) {
                cur_longest = lps_array[cur_longest - 1];
            }
            if (input[cur_longest] == input[pos]) 
                lps_array[pos] = ++cur_longest;
            else
                lps_array[pos] = 0;
        }
        ++pos;
    }
    return lps_array;
}

// Return the index of the first occurrence of pattern in the text
vector<int> kmp(const string& text, const string& pattern) {
    vector<int> kmp_result;
    string pattern_text(pattern + "$" + text);
    const auto lps = lps_array(pattern_text);

    for (int i = pattern.length(); i < pattern_text.length(); ++i) {
        if (lps[i] == pattern.length()) {
            kmp_result.push_back(i - 2 * pattern.length());
        }
    }
    return kmp_result;
}

int main() {
    string pattern, text;
    while (getline(cin, pattern) && getline(cin, text)) {
        const auto result = kmp(text, pattern);
        if (result.size() != 0) {
            for (int i = 0; i < result.size() - 1; ++i) {
                cout << result[i] << " ";
            }
            cout << result[result.size() - 1];
        }
        cout << "\n";
    }

    return 0;
}
