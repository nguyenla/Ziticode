#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_set>
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

string transform(const string& state, const string& move) {
    string res;
    for (int i = 0; i < 9; ++i) {
        if (state[i] == move[i]) res += '0';
        else res += '1';
    }
    return res;
}

// Find the minimum number of moves to get from a blank board to the given board
int solve(const vector<string>& board) {
    string start = "000000000";
    string goal; // 1 for black, 0 for white
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == '*') goal += '1';
            else goal += '0';
        }
    }
    // cout << goal << endl;
    vector<string> moves{
        "110100000", "111010000", "011001000",
        "100110100", "010111010", "001011001",
        "000100110", "000010111", "000001011"
    };

    // BFS
    int count = 0;
    queue<string> bfs;
    unordered_set<string> added;
    bfs.push(start);
    added.insert(start);

    while (!bfs.empty()) {
        int size = bfs.size();
        for (int i = 0; i < size; ++i) {
            string state = bfs.front();
            bfs.pop();
            if (state == goal) return count;
            for (int j = 0; j < moves.size(); ++j) {
                string next_state = transform(state, moves[j]);
                if (added.count(next_state) > 0) continue;
                // cout << next_state << endl;
                added.insert(next_state);
                bfs.push(next_state);
            }
        }
        ++count;
    }

    return -1;
}

int main() {
    int n;
    string line;
    cin >> n;
    getline(cin, line); // throw away

    for (int i = 0; i < n; ++i) {
        vector<string> board;
        for (int j = 0; j < 3; ++j) {
            getline(cin, line);
            board.push_back(line);
        }
        cout << solve(board) << endl;
    }

    return 0;
}
