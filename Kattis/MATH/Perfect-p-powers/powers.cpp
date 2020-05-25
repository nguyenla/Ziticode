#include <iostream>
#include <map>
#include <math.h>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


int main() {
    long n;
    cin >> n;

    while (n != 0) {
        long abs_n = abs(n);
        double log_n = log(abs_n) / log(2);
        bool is_neg = n < 0;
        bool found = false;

        for (int i = log_n; i >= 2; --i) {
            double base = pow(2, log_n / i);
            long low = floor(base);
            long high = ceil(base);
            if (pow(low, i) == abs_n || pow(high, i) == abs_n) {
                if (is_neg && i % 2 == 0) continue;
                cout << i << "\n";
                found = true;
                break;
            }
        }
        if (!found) cout << "1\n";

        cin >> n;
    }
    return 0;
}
