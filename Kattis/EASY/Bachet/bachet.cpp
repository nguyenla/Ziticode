#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

int main() {
    string line;
    
    while (getline(cin, line)) {
        istringstream iss(line);
        int n, m;
        iss >> n >> m;
        vector<int> moves;
        int move;
        for (int i = 0; i < m; ++i) {
            iss >> move;
            moves.push_back(move);
        }

        vector<bool> winning_state;
        winning_state.push_back(false);
        winning_state.push_back(true);

        for (int i = 2; i <= n; ++i) {
            bool is_winning = false;
            for (int j = 0; j < m; ++j) {
                if (i == moves[j]) is_winning = true;
                if (i > moves[j] && !winning_state[i - moves[j]]) is_winning = true;
            }
            if (is_winning) winning_state.push_back(true);
            else winning_state.push_back(false);
        }
        if (winning_state[n]) cout << "Stan wins\n";
        else cout << "Ollie wins\n";
    }
    return 0;
}
