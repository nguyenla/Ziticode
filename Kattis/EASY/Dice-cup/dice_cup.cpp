#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int m, n;
    cin >> m >> n;
    vector<int> sums(m + n + 1, 0);
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            ++sums[i+j];
        }
    }

    int most_common = 1;
    for (int i = 2; i < sums.size(); ++i) {
        if (sums[i] > sums[most_common]) {
            most_common = i;
        }
    }

    for (int i = 1; i < sums.size(); ++i) {
        if (sums[i] == sums[most_common]) {
            cout << i << "\n";
        }
    }
    return 0;
}
