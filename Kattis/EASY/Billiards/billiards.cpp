#include <algorithm>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include <vector>

using namespace std;


int main() {
    long a, b, s, m, n;
    cin >> a >> b >> s >> m >> n;
    while (a || b || s || m || n) {
        double distance = sqrt((a * m * a * m) + (b * n * b * n)) / s;
        double vert = b * n;
        double angle = atan(vert / a / m) * 180 / M_PI;
        cout << setprecision(2) << fixed << angle << " " << distance << "\n";

        cin >> a >> b >> s >> m >> n;
    }
    return 0;
}
