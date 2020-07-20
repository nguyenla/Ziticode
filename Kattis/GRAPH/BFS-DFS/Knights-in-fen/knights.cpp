#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

struct Board {
    char board[5][5];
    int empty_x;
    int empty_y;

    Board(const vector<string>& input) {
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                board[i][j] = input[i][j];
                if (board[i][j] == ' ') {
                    empty_y = i;
                    empty_x = j;
                }
            }
        }
    }

    Board(const Board& b) : empty_x(b.empty_x), empty_y(b.empty_y) {
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                board[i][j] = b.board[i][j];
            }
        }
    }

    string toString() const {
        string sep = "\n";
        string res = "";
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
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

int search(const Board& board, const Board& target) {
    queue<Board> bqueue;
    bqueue.push(board);
    unordered_set<string> visited;
    vector<vector<int>> moves = {
        {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, 
        {-2, -1}, {-2, 1}, {2, -1}, {2, 1}
    };
    int iter = 0;

    while (iter < 11 && !bqueue.empty()) {
        int q_size = bqueue.size();
        for (int i = 0; i < q_size; ++i) {
            Board cur = bqueue.front();
            bqueue.pop();
            if (cur == target) {
                return iter;
            }
            // Add all 8 neighbors to queue if not yet visited
            int x = cur.empty_x;
            int y = cur.empty_y;
            for (int m = 0; m < moves.size(); ++m) {
                int new_x = x + moves[m][0];
                int new_y = y + moves[m][1];

                if (!(new_x >= 0 && new_x <= 4 && new_y >= 0 && new_y <= 4)) continue;
                Board new_board(cur);
                new_board.board[y][x] = new_board.board[new_y][new_x];
                new_board.board[new_y][new_x] = ' ';
                new_board.empty_x = new_x;
                new_board.empty_y = new_y;

                auto bstring = new_board.toString();
                if (visited.find(bstring) == visited.end()) {
                    visited.insert(bstring);
                    bqueue.push(new_board);
                }
            }

        }
        ++iter;
    }
    return -1;
}


int main() {
    int cases;
    cin >> cases;
    string line;
    getline(cin, line);
    vector<string> target_board{"11111", "01111", "00 11", "00001", "00000"};
    Board target(target_board);

    for (int i = 0; i < cases; ++i) {
        vector<string> input;
        for (int j = 0; j < 5; ++j) {
            getline(cin, line);
            input.push_back(line);
        }
        Board board(input);
        auto moves = search(board, target);
        if (moves == -1) {
            cout << "Unsolvable in less than 11 move(s).\n";
        }
        else {
            cout << "Solvable in " << moves << " move(s).\n";
        }
    }
    return 0;
}
