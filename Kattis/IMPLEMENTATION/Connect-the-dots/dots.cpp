#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

struct Point {
    Point(int row, int col) : row(row), col(col) {}
    Point() : row(0), col(0) {}

    string toString() const {
        return "(" + to_string(row) + " " + to_string(col) + ")";
    }

    int row, col;
};

// Helper function to display vector
template <class T>
void print(const vector<T>& input) {
    for (const T& elem : input) {
        cout << elem << " ";
    }
    cout << "\n";
}

void solve(const vector<string>& input) {
    auto comp = [](const char a, const char b) {
        if (isdigit(a) && isdigit(b)) return a < b;
        else if(isdigit(a) && !isdigit(b)) return true;
        else if(!isdigit(a) && isdigit(b)) return false;

        if (isupper(a) && islower(b)) return false;
        else if (isupper(b) && islower(a)) return true;
        return a < b;
    };
    map<char, Point, decltype(comp)> mp(comp);

    vector<vector<char>> v;
    for (int i = 0; i < input.size(); ++i) {
        vector<char> row;
        for (int j = 0; j < input[i].size(); ++j) {
            row.push_back(input[i][j]);
            if (input[i][j] != '.') {
                mp[input[i][j]] = Point(i, j);
            }
        }
        v.push_back(row);
    }

    // Connecting dots
    bool started = false;
    Point prev_pos;
    for (const auto& item : mp) {
        if (!started) {
            prev_pos = item.second;
            started = true;
            continue;
        }
        
        Point cur_pos = item.second;
        if (cur_pos.row == prev_pos.row) {
            for (int i = min(cur_pos.col, prev_pos.col) + 1; i < max(cur_pos.col, prev_pos.col); ++i) {
                if (v[cur_pos.row][i] == '.') {
                    v[cur_pos.row][i] = '-';
                }
                else if (v[cur_pos.row][i] == '|') {
                    v[cur_pos.row][i] = '+';
                }
            }
        }
        else {
            for (int i = min(cur_pos.row, prev_pos.row) + 1; i < max(cur_pos.row, prev_pos.row); ++i) {
                if (v[i][cur_pos.col] == '.') {
                    v[i][cur_pos.col] = '|';
                }
                else if (v[i][cur_pos.col] == '-') {
                    v[i][cur_pos.col] = '+';
                }
            }
        }
        prev_pos = cur_pos;
    }

    // Print output
    for (int i = 0; i < v.size(); ++i) {
        for (int j = 0; j < v[i].size(); ++j) {
            cout << v[i][j];
        }
        cout << endl;
    }
}

int main() {
    string line;
    bool first = true;

    while (getline(cin, line)) {
        if (!first) cout << endl;
        else first = false;
        vector<string> input;
        while (line != "") {
            input.push_back(line);
            getline(cin, line);
        }
        solve(input);
    }
    return 0;
}
