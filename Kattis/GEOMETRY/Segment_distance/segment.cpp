#include <algorithm>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Point {
    Point() {}

    Point(const Point& p) {
        x = p.x;
        y = p.y;
    }

    Point(const double x, const double y) : x(x), y(y) {}

    bool operator==(const Point& p) const {
        return x == p.x && y == p.y;
    }

    double x;
    double y;
};

// Smallest to largest: bottom left point to top right
struct PointXYComparator {
    bool operator()(const Point& p1, const Point& p2) {
        if (p1.x != p2.x) {
            return p1.x < p2.x;
        }
        else {
            return p1.y < p2.y;
        }
    }
} xy_comparator;

void print(const Point& point) {
    cout << "(" << point.x << ", " << point.y << ")\n";
}

double distance(const Point& p1, const Point& p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}



int main() {
    int num_cases, x1, y1, x2, y2, x3, y3, x4, y4;
    cin >> num_cases;
    while (num_cases-- > 0) {
        scanf("%d %d %d %d %d %d %d %d", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);
        Point p1(x1, y1);
        Point p2(x2, y2);
        Point p3(x3, y3);
        Point p4(x4, y4);

        double distance = findSegmentDistance(p1, p2, p3, p4);
        cout << setprecision(2) << fixed << distance << "\n";
    }

    return 0;
}
