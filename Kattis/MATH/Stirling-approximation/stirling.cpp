#include <algorithm>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    vector<double> logs{0, 0}; // store ln(n!)
    for (int i = 2; i <= 100000; ++i) {
        logs.push_back(logs[i - 1] + log(i));
    }

    unordered_map<int, double> mp;
    for (int i = 1; i <= 100000; ++i) {
        mp[i] = exp(logs[i] + i - i * log(i) - 0.5 * log(2 * M_PI * i));
    }

    int n;
    cin >> n;
    while (n > 0) {
        cout << setprecision(10) << fixed << mp[n] << endl;
        cin >> n;
    }

    return 0;
}
