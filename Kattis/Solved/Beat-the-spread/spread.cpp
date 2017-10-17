#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int num_cases, sum, diff;
    cin >> num_cases;
    for (int i = 0; i < num_cases; ++i) {
        cin >> sum >> diff;
        if (((sum + diff) % 2 != 0) || sum < diff) {
            cout << "impossible\n";
        }
        else {
            cout << (sum + diff) / 2 << " " << (sum - diff) / 2 << '\n'; 
        }
    }
    return 0;
}
