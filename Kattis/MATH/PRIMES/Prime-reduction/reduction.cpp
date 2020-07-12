#include <algorithm>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include <unordered_map>
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

bool isPrime(const int n, const vector<int>& primes) {
    bool is_prime = true;
    for (int i = 0; i < primes.size(); ++i) {
        if (primes[i] >= n) break;
        if (n % primes[i] == 0) is_prime = false;
    }
    return is_prime;
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
    auto primes = getPrimes(1000000000);
    vector<string> res;

    for (int i = 0; i < input.size(); ++i) {
        int cur = input[i];
        int num_check = 1;
        
        while (!isPrime(cur, primes)) {
            auto factors = primeFactorization(cur, primes);

            int sum_factors = 0;
            for (const auto& f : factors) sum_factors += f;
            cur = sum_factors;
            ++num_check;
        }
        res.push_back(to_string(cur) + " " + to_string(num_check));
    }

    return res;
}

int main() {
    int x;
    vector<int> input;
    cin >> x;

    while (x != 4) {
        input.push_back(x);
        cin >> x;
    }

    auto output = solve(input);
    for (const auto& line : output) {
        cout << line << endl;
    }
    return 0;
}
