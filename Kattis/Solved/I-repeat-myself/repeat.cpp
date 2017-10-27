#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int process(const string& line) {
    for (int i = 1; i <= line.length(); ++i) {
        string cur = line.substr(0, i);
        string big(cur);
        while (big.length() < line.length()) {
            big = big + cur;
        }
        if (big.find(line) != string::npos) {
            return i;
        }
    }
    return -1;
}

int main() {
    int n;
    string line;
    cin >> n;
    getline(cin, line); // thrown away
    for (int i = 0; i < n; ++i) {
        getline(cin, line);
        cout << process(line) << '\n';
    }
    return 0;
}
