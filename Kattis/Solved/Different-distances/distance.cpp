#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

int main() {
    double x1, y1, x2, y2, p;
    cin >> x1;
    while (x1 != 0) {
        cin >> y1 >> x2 >> y2 >> p;

        double a = abs(x2 - x1);
        double b = abs(y2 - y1);
        double powa = pow(a, p);
        double powb = pow(b, p);
        double exp = 1 / p;
        double res = pow(powa + powb, exp);
        cout << setprecision(16) << res << '\n';
        cin >> x1;
    }
    return 0;
}
