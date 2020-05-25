#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    while (n-- > 0) {
        int m;
        cin >> m;
        int max_index = 1;
        double max_torque = 0;
        double a, b, c;
        for (int i = 1; i <= m; ++i) {
            cin >> a >> b >> c;
            double x = b / (2 * a);
            double torque =  a * (-1) * x * x + (b * x) + c;
            if (i == 1) {
                max_torque = torque;
            }
            else if (torque > max_torque) {
                max_index = i;
                max_torque = torque;
            }
        }
        cout << max_index << "\n";
    }

    return 0;
}
