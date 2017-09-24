#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Number of n-step closed paths on hexagonal lattice
    int results[] = {0, 6, 12, 90, 360, 2040, 10080, 54810, 290640, 1588356, 8676360, 47977776, 266378112, 1488801600};
    int num_cases;
    cin >> num_cases;
    for (int i = 0; i < num_cases; ++i) {
        int n;
        cin >> n;
        cout << results[n-1] << '\n';
    }
    return 0;
}
