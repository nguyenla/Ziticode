#include <algorithm>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Helper function to display vector
void print(const vector<int>& input) {
    for (const int num : input) {
        cout << num << " ";
    }
    cout << "\n";
}

// Get primes samller or equal to sqrt(n)
vector<int> getPrimes(int n) {
    vector<int> primes;
    int nsqrt = sqrt(n);
    vector<char> is_prime(nsqrt + 1, true);
    for (int i = 2; i <= nsqrt; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = i * i; j <= nsqrt; j += i)
                is_prime[j] = false;
        }
    }
    // cout << primes.size() << "\n";
    // print(primes);
    return primes;
}

// Count the number of integers <= n that are not divisible by any prime in the given primes list
int countPrimes(int n, const vector<int>& primes) {
    const int S = 10000; // block size
    int nsqrt = sqrt(n);
    vector<char> is_prime(nsqrt + 1, true);

    int result = 0;
    vector<char> block(S);
    for (int k = 0; k * S <= n; k++) {
        fill(block.begin(), block.end(), true);
        int start = k * S;
        for (int p : primes) {
            int start_index = (start + p - 1) / p;
            int j = max(start_index, p) * p - start;
            for (; j < S; j += p)
                block[j] = false;
        }
        if (k == 0) {
            block[0] = false;
            block[1] = false;
        }

        for (int i = 0; i < S && start + i <= n; i++) {
            if (block[i]) ++result;
        }
    }
    return result;
}


int main() {
    int n, q, x;
    cin >> n >> q;

    auto primes = getPrimes(n);
    cout << countPrimes(n, primes) << "\n";

    for (int i = 0; i < q; ++i) {
        cin >> x;
        bool isPrime = true;
        if (x == 1) isPrime = false;
        else {
            for (int j = 0; j < primes.size(); ++j) {
                if (x > primes[j] && x % primes[j] == 0) isPrime = false;
            }
        }
        if (isPrime) cout << "1\n";
        else cout << "0\n";
    }
    // cout << countPrimes(100000000) << "\n";

    return 0;
}
