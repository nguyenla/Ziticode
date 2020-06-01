#include <algorithm>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include <vector>

using namespace std;


int main() {
    long t, w, g, h, r;
    cin >> t;

    for (int i = 0; i < t; ++i) {
        cin >> w >> g >> h >> r;
        long height_diff = abs(g - h);
        // Min distance is always straight line distance
        double mindist = sqrt(height_diff * height_diff + w * w);

        // Use first derivative to minimize the cable length
        // max_a: the projection on to the ground of the left part of the cable
        double maxdist = mindist;
        if (!(r == g || r == h)) {
            double max_a = w * abs(r - g);
            max_a /= abs(h + g - 2 * r);

            maxdist = sqrt((g - r) * (g - r) + max_a * max_a)
                + sqrt((h - r) * (h - r) + (w - max_a) * (w - max_a));
        }

        cout << setprecision(8) << fixed << mindist << " " << maxdist << "\n";
    }

    return 0;
}
