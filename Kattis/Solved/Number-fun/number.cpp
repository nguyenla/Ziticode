#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool check(int a, int b, int c) {
    if (a + b == c || a * b == c) {
        return true;
    }
    if (a-b == c || b-a == c) {
        return true;
    }
    if (a % b == 0 && a/b == c) {
        return true;
    }
    if (b % a == 0 && b/a == c) {
        return true;
    }
    return false;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int a,b,c;
        cin >> a >> b >> c;
        if (check(a, b, c)) {
            cout << "Possible" << '\n';
        }
        else {
            cout << "Impossible" << '\n';
        }
    }
    return 0;
}

