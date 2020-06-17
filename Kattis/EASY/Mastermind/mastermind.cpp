#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    int n;
    string code, guess;
    cin >> n >> code >> guess;

    int r = 0, s = 0;
    vector<bool> correct(n, false);
    unordered_map<char, int> mp;

    for (int i = 0; i < n; ++i) {
        if (code[i] == guess[i]) {
            ++r;
            correct[i] = true;
        }
        else {
            char x = code[i];
            if (mp.find(code[i]) == mp.end()) {
                mp[code[i]] = 1;
            }
            else {
                mp[code[i]] = mp[code[i]] + 1;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (correct[i]) continue;
        if (mp.find(guess[i]) == mp.end()) continue;
        if (mp[guess[i]] > 0) {
            ++s;
            mp[guess[i]] = mp[guess[i]] - 1;
        }
    }
    cout << r << " " << s << "\n";

    return 0;
}
