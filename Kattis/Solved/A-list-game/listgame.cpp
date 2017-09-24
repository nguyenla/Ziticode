#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int num_prime_factors(int x) {
    int k = 0;
    while (x % 2 == 0) {
        ++k;
        x /= 2;
    }
    for (int i = 3; i * i <= x; i = i + 2) {
        while (x % i == 0) {
            ++k;
            x /= i;
        }
    }
    if (x != 1) ++k;
    return k;
}

int main() {
    int x;
    cin >> x;
    cout << num_prime_factors(x) << '\n';

    return 0;
}
