#include <algorithm>
#include <iostream>
#include <math.h>
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

void solve(const int n) {
    vector<int> perm(n, 0);
    int pos = 0;
    for (int i = 1; i <= n; ++i) {
        int moves = i;
        while (moves > 0) {
            pos = (pos + 1) % n;
            while (perm[pos] != 0) pos = (pos + 1) % n;
            --moves;
        }
        perm[pos] = i;
        if (i != n) {
            while (perm[pos] != 0) pos = (pos + 1) % n;
        }
    }
    print(perm);
}

int main() {
    int t = 0, n = 0;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        cin >> n;
        solve(n);
    }

    return 0;
}
