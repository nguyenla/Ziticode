#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string getSignProfile(const double& a, const double& b, const double& c, const double& d) {
    // Degree = 0
    if (a == 0 && b == 0 && c == 0) {
        if (d < 0) return "-";
        else return "+";
    }

    // Degree = 1
    if (a == 0 && b == 0) {
        if (c < 0) return "+-";
        else return "-+";
    }

    // Degree = 2
    if (a == 0) {
        double discriminant = c * c - 4 * b * d;
        if (b > 0) {
            if (discriminant > 0) return "+-+";
            else return "+";
        }
        else if (b < 0) {
            if (discriminant > 0) return "-+-";
            else return "-";
        }
    }

    // Degree = 3
    double discriminant = (18 * a * b * c * d) - (4 * b * b * b * d)
        + (b * b * c * c) - (4 * a * c * c * c) - (27 * a * a * d * d);
    // cout << discriminant << endl;

    if (discriminant == 0) {
        // triple root or double root
        if (a < 0) return "+-";
        else return "-+";
    }
    else if (discriminant > 0) {
        if (a < 0) return "+-+-";
        else return "-+-+";
    }
    else {
        if (a < 0) return "+-";
        else return "-+";
    }
}

int main() {
    double a, b, c, d;
    cin >> d >> c >> b >> a;

    while (a != 0 || b != 0 || c != 0 || d != 0) {
        cout << getSignProfile(a, b, c, d) << endl;
        cin >> d >> c >> b >> a;
    }

    return 0;
}
