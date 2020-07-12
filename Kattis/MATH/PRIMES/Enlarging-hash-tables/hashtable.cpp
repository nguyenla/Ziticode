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

// Get primes smaller or equal to sqrt (n)
vector<long> getPrimes(long n) {
    vector<long> primes;
    long nsqrt = sqrt(n);
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

bool isPrime(const long n, const vector<long>& primes) {
    bool is_prime = true;
    for (int i = 0; i < primes.size(); ++i) {
        if (primes[i] >= n) break;
        if (n % primes[i] == 0) is_prime = false;
    }
    return is_prime;
}

long findNextSize(const long n, const vector<long>& primes) {
    long start = 2 * n + 1;
    while (!isPrime(start, primes)) ++start;
    return start;
}

int main() {
    long n;
    cin >> n;
    vector<long> input;
    while (n != 0) {
        input.push_back(n);
        cin >> n;
    }

    auto primes = getPrimes(2147483647);

    for (int i = 0; i < input.size(); ++i) {
        bool is_prime = isPrime(input[i], primes);
        cout << findNextSize(input[i], primes);
        if (is_prime) cout << endl;
        else cout << " (" << input[i] << " is not prime)" << endl;
    }
    return 0;
}
