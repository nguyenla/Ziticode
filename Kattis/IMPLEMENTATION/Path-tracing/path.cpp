#include <algorithm>
#include <iostream>
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
    vector<string> steps;
    string s;
    int x = 0;
    int y = 0;
    int max_x = 0, max_y = 0, min_x = 0, min_y = 0;

    while (cin >> s) {
        if (s == "down") {
            min_y = min(min_y, --y);
        }
        else if (s == "up") {
            max_y = max(max_y, ++y);
        }
        else if (s == "left") {
            min_x = min(min_x, --x);
        }
        else if (s == "right") {
            max_x = max(max_x, ++x);
        }
        steps.push_back(s);
    }
    vector<vector<string> > output;
    for (int i = 0; i < max_y + abs(min_y) + 3; ++i) {
        vector<string> temp(max_x + abs(min_x) + 3, " ");
        output.push_back(temp);
    }

    for (int i = 0; i < output.size(); ++i) {
        for (int j = 0; j < output[0].size(); ++j) {
            if (i == 0 || j == 0 || i == output.size() - 1 || j == output[0].size() - 1) {
                output[i][j] = "#";
            }
        }
    }

    int start_y = abs(max_y) + 1;
    int start_x = abs(min_x) + 1;
    x = start_x;
    y = start_y;
    for (auto s : steps) {
        if (s == "down") {
            output[++y][x] = "*";
        }
        else if (s == "up") {
            output[--y][x] = "*";
        }
        else if (s == "left") {
            output[y][--x] = "*";
        }
        else if (s == "right") {
            output[y][++x] = "*";
        }
    }
    output[start_y][start_x] = "S";
    output[y][x] = "E";

    // Printing
    for (int i = 0; i < output.size(); ++i) {
        for (int j = 0; j < output[0].size(); ++j) {
            cout << output[i][j];
        }
        cout << "\n";
    }
    return 0;
}
