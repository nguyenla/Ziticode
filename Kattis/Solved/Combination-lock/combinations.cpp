#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int calculate_angle(int dial, int a, int b, int c) {
    int total = 720;
    total += ((dial + 40 - a) * 9) % 360;
    total += 360;
    total += ((b - a + 40) * 9) % 360;
    total += ((b + 40 - c) * 9) % 360;
    return total;
}

int main() {
    int dial, a, b, c;
    cin >> dial >> a >> b >> c;
    while (dial || a || b || c) {
        cout << calculate_angle(dial, a, b, c) << '\n';
        cin >> dial >> a >> b >> c;
    }
    return 0;
}
