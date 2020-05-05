#include <algorithm>
#include <exception>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

// Main idea: Apply KMP to search for input[1 : end] in input

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

// Helper function to display vector
void print(const vector<int>& input) {
    for (const int num : input) {
        cout << num << " ";
    }
    cout << "\n";
}

int find_first_occurrence_kmp(const string& pattern, const string& text) {
    const auto lps_pattern = lps_array(pattern);
    int cur_text = 0;
    int cur_pat = 0;
    while (cur_text + cur_pat < text.length()) {
        if (cur_text + cur_pat < text.length() && text[cur_text + cur_pat] == pattern[cur_pat]) {
            ++cur_pat;
        }
        else {
            if (cur_text + cur_pat == text.length()) {
                return cur_text;
            }
            else if (cur_pat == 0) {
                ++cur_text;
            }
            else {
                cur_text = cur_text + cur_pat - lps_pattern[cur_pat - 1];
                cur_pat = lps_pattern[cur_pat - 1];
            }
        }
    }
    return cur_text;
}


// Return first position in the lps array of the input string that is the start
// of an increasing sequence starting from 1
int find_shortest_pattern_length(const string& text) {
    return find_first_occurrence_kmp(text, text.substr(1)) + 1;
}

int main() {
    int input_length;
    string input;
    cin >> input_length;
    while (cin >> input) {
        cout << find_shortest_pattern_length(input) << "\n";
    }

    return 0;
}
