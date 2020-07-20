#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

struct Board {
    vector<vector<char>> board;
    int length;

    Board(const string& input, const int n) : length(n) {
        for (int i = 0; i < n; ++i) {
            vector<char> temp(n);
            board.push_back(temp);
        }

        for (int i = 0; i < input.size(); ++i) {
            board[i / n][i % n] = input[i];
        }
    }

    Board(const Board& b) {
        for (int i = 0; i < b.length; ++i) {
            for (int j = 0; j < b.length; ++j) {
                board[i][j] = b.board[i][j];
            }
        }
    }

    string toString() const {
        string sep = "\n";
        string res = "";
        for (int i = 0; i < length; ++i) {
            for (int j = 0; j < length; ++j) {
                res += board[i][j];
            }
            res += sep;
        }
        return res;
    }

    bool operator==(const Board& b1) {
        return toString() == b1.toString();
    }
};

bool search(const Board& input_board, const string& target) {
    queue<pair<int, int>> bqueue;
    const auto board = input_board.board;
    const int n = input_board.length;
    for (int i = 0; i < input_board.length; ++i) {
        for (int j = 0; j < input_board.length; ++j) {
            if (board[i][j] == target[0]) {
                bqueue.emplace(i, j);
            }
        }
    }
    vector<vector<int>> moves = {
        {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, 
        {-2, -1}, {-2, 1}, {2, -1}, {2, 1}
    };

    for (int c = 1; c < target.size(); ++c) {
        if (bqueue.empty()) return false;
        int q_size = bqueue.size();
        char ch = target[c];

        for (int i = 0; i < q_size; ++i) {
            auto cur = bqueue.front();
            bqueue.pop();

            // Add all 8 neighbors to queue if not yet visited
            int x = cur.first;
            int y = cur.second;
            for (int m = 0; m < moves.size(); ++m) {
                int new_x = x + moves[m][0];
                int new_y = y + moves[m][1];
                if (!(new_x >= 0 && new_x < n && new_y >= 0 && new_y < n)) continue;
                if (board[new_x][new_y] != ch) continue;
                bqueue.emplace(new_x, new_y);
            }
        }
    }
    if (bqueue.empty()) return false;
    return true;
}


int main() {
    int n;
    cin >> n;
    string line;
    getline(cin, line); // throw away
    getline(cin, line);
    string target("ICPCASIASG");

    Board board(line, n);
    if (search(board, target)) cout << "YES" << endl;
    else cout << "NO" << endl;

    return 0;
}
