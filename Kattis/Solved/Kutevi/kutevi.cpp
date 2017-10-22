#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int lcd(int a, int b) {
    if (a < b) return lcd(b, a);
    if (a == 1 || b == 1) return 1;
    if (a % b == 0) return b;
    return lcd(b, a % b);
}

int main() {
    int n, k, a;
    cin >> n >> k;
    vector<int> input;
    input.push_back(360);

    bool check[360];
    fill(check, check + 360, false);

    for (int i = 0; i < n; ++i) {
        cin >> a;
        input.push_back(a);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n + 1; ++j) {
            int a = lcd(input[i], input[j]);
            for (int m = a; m < 360; m = m + a ) {
                check[m] = true;
            }
        }
    }

    for (int i = 0; i < k; ++i) {
        cin >> a;
        if (check[a]) {
            cout << "YES" << '\n';
        }
        else {
            cout << "NO" << '\n';
        }
    }



    return 0;
}
