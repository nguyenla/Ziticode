#include <algorithm>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <sstream>
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

int main() {
    string line;
    getline(cin, line);
    vector<int> v;
    for (int i = 0; i < line.length(); ++i) {
        v.push_back(line[i] - 'a');
    }

    vector<int> longest_sub;
    longest_sub.push_back(1);
    int global_max = 1;

    for (int i = 1; i < v.size(); ++i) {
        int cur = 1;
        for (int j = 0; j < i; ++j) {
            if (v[i] - v[j] > 0) {
                cur = max(cur, longest_sub[j] + 1);
            }
        }
        longest_sub.push_back(cur);
        global_max = max(global_max, cur);
    }
    cout << 26 - global_max << "\n";

    return 0;
}
