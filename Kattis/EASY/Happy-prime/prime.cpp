#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

bool isHappyPrime(const int k, const vector<bool>& primes) {
    int num = k;
    unordered_set<int> seen;
    while (seen.find(num) == seen.end()) {
        seen.insert(num);
        int sum = 0;
        while (num != 0) {
            sum += (num % 10) * (num % 10);
            num /= 10;
        }
        num = sum;
        // cout << "Sum: " << sum << "\n";
        if (num == 1 && primes[k]) return true;
    }
    return false;
}

int main() {
    int cases;
    cin >> cases;
    int k = 0, m = 0;

    vector<bool> primes(10001, true);
    primes[0] = false;
    primes[1] = false;
    for (int i = 2; i * i < 10001; ++i) {
        if (!primes[i]) continue;
        for (int j = 2 * i; j < 10001; j += i) {
            primes[j] = false;
        }
    }

    for (int i = 1; i <= cases; ++i) {
        cin >> k >> m;
        string ans = isHappyPrime(m, primes) ? "YES" : "NO";
        cout << k << " " << m << " " << ans << "\n";
    }

    return 0;
}
