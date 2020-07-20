#include <algorithm>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

bool checkValid(const vector<string>& input) {
    for (int i = 0; i < input.size() - 1; ++i) {
        if (input[i].size() > input[i + 1].size()) continue;
        string temp = input[i+1].substr(0, input[i].size());
        if (input[i] == temp) return false;
    }
    return true;
}

int main() {
    int t = 0;
    cin >> t;

    for (int i = 0; i < t; ++i) {
        int n = 0;
        string line = "";
        vector<string> input;

        cin >> n;
        for (int j = 0; j < n; ++j) {
            cin >> line;
            input.push_back(line);
        }
        sort(input.begin(), input.end());
        string res = checkValid(input) ? "YES" : "NO";
        cout << res << endl;
    }

    return 0;
}
