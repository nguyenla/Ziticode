#include <algorithm>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include <map>
#include <utility>
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

// Get primes smaller or equal to sqrt (n)
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
    return primes;
}

vector<int> primeFactorization(const int input, const vector<int>& primes) {
    int n = input;
    vector<int> factors;

    for (int i = 0; i < primes.size(); ++i) {
        while (n % primes[i] == 0) {
            n = n / primes[i];
            factors.push_back(primes[i]);
        }
    }
    if (n > 1) factors.push_back(n);
    return factors;
}

vector<string> solve(const vector<int>& input) {
    auto primes = getPrimes(2147483647);
    vector<string> res;

    for (int i = 0; i < input.size(); ++i) {
        int cur = input[i];
        bool is_neg = cur < 0 ? true : false;
        cur = abs(cur);
        auto factors = primeFactorization(cur, primes);

        map<int, int> mp;
        for (int j = 0; j < factors.size(); ++j) {
            if (mp.find(factors[j]) == mp.end()) {
                mp[factors[j]] = 1;
            }
            else {
                ++mp[factors[j]];
            }
        }

        string rep = "";
        if (is_neg) rep += "-1";
        for (const auto& item : mp) {
            if (rep != "") rep += " ";
            rep += to_string(item.first);
            if (item.second > 1) rep += "^" + to_string(item.second);
        }
        res.push_back(rep);
    }

    return res;
}

int main() {
    int x;
    vector<int> input;

    while (cin >> x) {
        input.push_back(x);
    }

    auto output = solve(input);
    
    for (const auto& line : output) {
        cout << line << endl;
    }
    return 0;
}
