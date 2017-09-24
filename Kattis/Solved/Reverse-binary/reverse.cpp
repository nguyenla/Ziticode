#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> bits;
    while (n > 0) {
        bits.push_back(n % 2);
        n /= 2;
    }
    int k = bits.size() - 1;
    for (size_t i = 0; i != bits.size(); ++i) {
        n += pow(2, k) * bits[i];
        --k;
    }
    cout << n << '\n';
    return 0;
}
