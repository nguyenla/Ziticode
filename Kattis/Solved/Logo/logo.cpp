#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

#define pi 3.14159265358979323846 
using namespace std;

int main() {
    int cases, n, arg;
    string command;
    cin >> cases;
    int curAngle = 0;
    double curX = 0, curY = 0;
    cout << std::fixed;

    for (int i = 0; i < cases; ++i) {
        cin >> n;
        for (int j = 0; j < n; ++j) {
            cin >> command >> arg;
            if (command == "lt") {
                curAngle = (curAngle + arg) % 360;
            }
            else if (command == "rt") {
                curAngle = (curAngle - arg) % 360;
            }
            else if (command == "fd") {
                curX += arg * cos(pi * curAngle / 180);
                curY += arg * sin(pi * curAngle / 180);
            }
            else if (command == "bk") {
                curX -= arg * cos(pi * curAngle / 180);
                curY -= arg * sin(pi * curAngle / 180);
            }
        }
        long res = std::round(sqrt(pow(curX, 2) + pow(curY, 2)));
        cout << res << '\n';

    }
    return 0;
}
