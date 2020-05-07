#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int length;
    while (cin >> length) {
        vector<int> input(length, 0);
        vector<int> diffs(length, 0);
        cin >> input[0];
        for (int i = 1; i < length; ++i) {
            cin >> input[i];
            int diff = abs(input[i] - input[i-1]);
            if (diff > 0 && diff < length) {
                ++diffs[diff];
            }
        }

        bool jolly = true;
        for (int i = 1; i < length; ++i) {
            if (diffs[i] == 0) {
                jolly = false;
                break;
            }
        }

        if (jolly) cout << "Jolly\n";
        else cout << "Not jolly\n";
    }
    return 0;
}
