#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
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

vector<int> permute(const int input, const unordered_set<int>& added) {
    string s = to_string(input);
    // sort(s.begin(), s.end());
    vector<int> res;
    do {
        // cout << s << endl;
        int num = stoi(s);
        if (num > input && added.count(num) == 0) {
            res.push_back(num);
        }
    }
    while (next_permutation(s.begin(), s.end()));
    return res;
}

vector<int> permute2(const int input, unordered_set<int>& found, const int max) {
    string s = to_string(input);
    vector<int> res;
    do {
        int num = stoi(s);
        res.push_back(num);
        found.insert(num);
        if (found.size() == max) return res;
    }
    while (next_permutation(s.begin(), s.end()));
    return res;
}

int solve(const int n) {
    queue<int> bfs;
    int count = 0;
    unordered_map<int, int> mp;
    unordered_set<int> added;
    unordered_set<int> permuted;
    int processed = 0;
    bfs.push(1);

    while (!bfs.empty()) {
        int size = bfs.size();
        for (int i = 0; i < size; ++i) {
            int next = bfs.front();
            bfs.pop();
            if (mp.find(next) != mp.end()) continue;
            mp[next] = count;
            if (next == n) {
                // cout << "Processed: " << processed << endl;
                // cout << "Added: " << added.size() << endl;
                return count;
            }
            else {

                // Operation 1
                int plus_one = next + 1;
                if (plus_one == n) {
                    mp[plus_one] = count + 1;
                    // cout << "Processed: " << processed << endl;
                    // cout << "Added: " << added.size() << endl;
                    return mp[plus_one];
                }
                if (added.count(plus_one) == 0) {
                    added.insert(plus_one);
                    bfs.push(plus_one);
                }

                if (permuted.count(next) != 0) continue;
                auto permutations = permute(next, added);
                processed += permutations.size() + 1;

                // Operation 2
                // cout << "Checking " << permutations.size() << " permutations." << endl;
                for (const int num : permutations) {
                    // cout << "Checking: " << num << endl;
                    if (num == n) {
                        mp[num] = count + 1;
                        // cout << "Processed: " << processed << endl;
                        // cout << "Added: " << added.size() << endl;
                        return mp[num];
                    }
                    if (added.count(num) == 0) {
                        added.insert(num);
                        bfs.push(num);
                    }
                }
                permuted.insert(next);
            }
        }
        ++count;
    }
    return -1;
}

int main() {
    int cases, n;
    // cin >> cases;
    for (int i = 20000; i < 21000; ++i) {
        // cin >> n;
        cout << solve(i) << endl;
    }
    return 0;
}
