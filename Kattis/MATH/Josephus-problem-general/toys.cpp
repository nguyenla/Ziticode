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


int main() {
    int t, k;
    cin >> t >> k;

    // General case of Josephus problem
    // Recurrence relation: g(n, k) = (g(n - 1, k) + k) mod n. Base case: g(1, k) = 0
    vector<int> dp{0, 0};
    for (int i = 2; i <= t; ++i) {
        dp.push_back((dp[i - 1] + k) % i);
    }
    cout << dp[t] << endl;
    return 0;
}
