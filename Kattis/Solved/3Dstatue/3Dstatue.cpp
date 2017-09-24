#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int calculate(int n) {
    if (n == 1) return 1;
    if (n == 2) return 2;
    int power = 1;
    int x = 2;

    // find the largest power of 2 less than n
    while (x*2 < n) {
        x *= 2;
        ++power;
    }
    return power + 2;
}

int main() {
    int num_statues;
    cin >> num_statues;
    cout << calculate(num_statues);
    
    return 0;
}
