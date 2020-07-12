#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct Point {
    Point() {}

    Point(const int row, const int col) : row(row), col(col) {}

    string toString() const {
        return "(" + to_string(row) + ", " + to_string(col) + ")";
    }

    int row;
    int col;
};

void printState(const char input[][105], const int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << input[i][j];
        }
        cout << endl;
    }
}

vector<string> getFinalState(const vector<string>& moves) {
    char state[105][105];
    for (int i = 0; i < 105; ++i) {
        for (int j = 0; j < 105; ++j) {
            state[i][j] = '-';
        }
    }
    vector<string> initial{"ABCDE", "FGHIJ", "KLMNO", "PQRST", "UVWXY"};
    unordered_map<char, Point> positions; 
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            state[50 + i][50 + j] = initial[i][j];
            positions[initial[i][j]] = Point(50 + i, 50 + j);
        }
    }

    for (int i = 0; i < moves.size(); ++i) {
        istringstream iss(moves[i]);
        char letter;
        string direction;
        iss >> letter >> direction;

        // Sliding tiles
        if (direction == "up") {
            char cur = letter;
            Point pos = positions[letter];
            state[pos.row][pos.col] = '-';

            while (true) {
                char temp = state[pos.row - 1][pos.col];
                state[pos.row - 1][pos.col] = cur;
                positions[cur] = Point(pos.row - 1, pos.col);
                cur = temp;
                if (cur == '-') break;
                pos = positions[cur];
            }
        }
        else if (direction == "down") {
            char cur = letter;
            auto pos = positions[letter];
            state[pos.row][pos.col] = '-';

            while (true) {
                char temp = state[pos.row + 1][pos.col];
                state[pos.row + 1][pos.col] = cur;
                positions[cur] = Point(pos.row + 1, pos.col);
                cur = temp;
                if (cur == '-') break;
                pos = positions[cur];
            }
        }
        else if (direction == "left") {
            char cur = letter;
            auto pos = positions[letter];
            state[pos.row][pos.col] = '-';

            while (true) {
                char temp = state[pos.row][pos.col - 1];
                state[pos.row][pos.col - 1] = cur;
                positions[cur] = Point(pos.row, pos.col - 1);
                cur = temp;
                if (cur == '-') break;
                pos = positions[cur];
            }
        }
        else if (direction == "right") {
            char cur = letter;
            auto pos = positions[letter];
            state[pos.row][pos.col] = '-';

            while (true) {
                char temp = state[pos.row][pos.col + 1];
                state[pos.row][pos.col + 1] = cur;
                positions[cur] = Point(pos.row, pos.col + 1);
                cur = temp;
                if (cur == '-') break;
                pos = positions[cur];
            }
        }
    }
    // printState(state, 105);

    int min_row = 200, min_col = 200, max_row = -1, max_col = -1;
    for (int i = 0; i < 105; ++i) {
        for (int j = 0; j < 105; ++j) {
            if (state[i][j] != '-') {
                min_row = min(i, min_row);
                max_row = max(i, max_row);
                min_col = min(j, min_col);
                max_col = max(j, max_col);
            }
        }
    }
    // cout << "(" << min_row << ", " << min_col << "), (" << max_row << ", " << max_col << ")\n";

    vector<string> res;
    for (int i = min_row; i <= max_row; ++i) {
        string line;
        int last_letter_pos = -1;
        for (int j = max_col; j >= min_col; --j) {
            if (state[i][j] != '-') {
                last_letter_pos = j;
                break;
            }
        }

        for (int j = min_col; j <= max_col; ++j) {
            if (state[i][j] == '-') {
                if (j < last_letter_pos) line += ' ';
            }
            else {
                line += state[i][j];
            }
        }
        if (last_letter_pos != -1) res.push_back(line);
        else res.push_back("");
    }
    return res;
}

int main() {
    int n;
    string line;
    cin >> n;
    getline(cin, line); // throw away

    while (n >= 0) {
        vector<string> moves;
        for (int i = 0; i < n; ++i) {
            getline(cin, line);
            moves.push_back(line);
        }
        auto output = getFinalState(moves);
        for (int i = 0; i < output.size(); ++i) {
            cout << output[i] << endl;
        }
        cout << endl;

        cin >> n;
        getline(cin, line); // throw away
    }
    return 0;
}
