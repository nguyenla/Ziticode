#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Helper function to display vector
template <class T>
void print(const vector<T>& input) {
    for (const T& elem : input) {
        cout << elem << " ";
    }
    cout << "\n";
}

vector<int> swipe_left(const vector<int>& row) {
    vector<int> res;
    int num_zeros = 0;
    for (int i = 0; i < row.size(); ++i) {
        if (row[i] != 0) res.push_back(row[i]);
        else ++num_zeros;
    }

    for (int i = 0; i < num_zeros; ++i) {
        res.push_back(0);
    }

    if (res[0] > 0 && res[0] == res[1]) {
        res[0] *= 2;
        res[1] = res[2];
        res[2] = res[3];
        res[3] = 0;
        if (res[1] == res[2]) {
            res[1] *= 2;
            res[2] = 0;
        }
    }
    else if (res[1] > 0 && res[1] == res[2]) {
        res[1] *= 2;
        res[2] = res[3];
        res[3] = 0;
    }
    else if (res[2] > 0 && res[2] == res[3]) {
        res[2] *= 2;
        res[3] = 0;
    }
    return res;
}

int main() {
    int n, dir;
    vector<vector<int>> board;
    for (int i = 0; i < 4; ++i) {
        vector<int> row;
        for (int j = 0; j < 4; ++j) {
            cin >> n;
            row.push_back(n);
        }
        board.push_back(row);
    }

    cin >> dir;
    switch (dir) {
        case 0: // left
            for (int i = 0; i < 4; ++i) {
                vector<int> temp;
                for (int j = 0; j < 4; ++j) {
                    temp.push_back(board[i][j]);
                }
                auto res = swipe_left(temp);
                for (int j = 0; j < 4; ++j) {
                    board[i][j] = res[j];
                }
            }
            break;
        case 1:
            for (int j = 0; j < 4; ++j) {
                vector<int> temp;
                for (int i = 0; i < 4; ++i) {
                    temp.push_back(board[i][j]);
                }
                auto res = swipe_left(temp);
                for (int i = 0; i < 4; ++i) {
                    board[i][j] = res[i];
                }
            }

            break;
        case 2:
            for (int i = 0; i < 4; ++i) {
                vector<int> temp;
                for (int j = 3; j >= 0; --j) {
                    temp.push_back(board[i][j]);
                }
                auto res = swipe_left(temp);
                for (int j = 0; j < 4; ++j) {
                    board[i][j] = res[3 - j];
                }
            }
            break;
        case 3:
            for (int j = 0; j < 4; ++j) {
                vector<int> temp;
                for (int i = 3; i >= 0; --i) {
                    temp.push_back(board[i][j]);
                }
                auto res = swipe_left(temp);
                for (int i = 0; i < 4; ++i) {
                    board[i][j] = res[3 - i];
                }
            }
            break;
        default:
            break;
    }

    // Print board
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << board[i][j] << " ";
        }
        cout << board[i][3] << endl;
    }

    return 0;
}
