#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

bool beforeOrEqual(int h1, double m1, int h2, double m2) {
    if (h1 < h2) return true;
    else if (h1 == h2 && m1 <= m2) return true;
    return false;
}

bool afterOrEqual(int h1, double m1, int h2, double m2) {
    if (h1 > h2) return true;
    else if (h1 == h2 && m1 >= m2) return true;
    return false;
}

template <> struct std::hash<pair<int, double>> {
    size_t operator()(const pair<int, double>& p) const {
        return hash<int>()(p.first) ^ hash<double>()(p.second);
    }
};

int main() {
    
    int cases, angle, from_h, from_m, to_h, to_m;
    string from, to;
    cin >> cases;

    for (int c = 0; c < cases; ++c) {
        cin >> from >> to >> angle;
        from_h = stoi(from.substr(0, 2));
        from_m = stoi(from.substr(3));
        to_h = stoi(to.substr(0, 2));
        to_m = stoi(to.substr(3));

        int hours = 0;
        double mins = 0;
        unordered_set<pair<int, double>> found;

        for (int i = from_h - 1; i <= to_h; ++i) {
            hours = i;
            int hour_angle = i % 12;
            double min_temp = 60 * hour_angle + 2 * angle;
            if (min_temp >= 60 * 11) {
                mins = min_temp - 60 * 11;
                ++hours;
            }
            else {
                mins = min_temp;
            }
            mins /= 11;
            if (afterOrEqual(hours, mins, from_h, from_m) && beforeOrEqual(hours, mins, to_h, to_m)) {
                auto ret = found.emplace(hours, mins);
            }

            if (angle == 90) {
                hours = i;
                min_temp += 360;
                if (min_temp >= 60 * 11) {
                    mins = min_temp - 60 * 11;
                    ++hours;
                }
                else {
                    mins = min_temp;
                }
                mins /= 11;
                if (afterOrEqual(hours, mins, from_h, from_m) && beforeOrEqual(hours, mins, to_h, to_m)) {
                    auto ret = found.emplace(hours, mins);
                }
            }
        }
        cout << found.size() << endl;
    }

    return 0;
}
