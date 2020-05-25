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

    Point(const int x, const int y) : x(x), y(y) {}

    bool operator==(const Point& p) {
        return x == p.x && y == p.y;
    }

    int x;
    int y;
};

void print(const Point& point) {
    cout << "(" << point.x << ", " << point.y << ")\n";
}

double distance(const Point& p1, const Point& p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// Return the cross product of vectors p1->p2 and p1->p3
double cross_product(const Point& p1, const Point& p2, const Point& p3) {
    return 1.0 * ((p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x));
}

// Return the area of the triangle formed by three given points
double area_triangle(const Point& p1, const Point& p2, const Point& p3) {
    return abs(cross_product(p1, p2, p3)) / 2;

bool isCW(const Point& base, const Point& p1, const Point& p2) {
    return (p1.y - base.y) * (p2.x - p1.x) - (p2.y - p1.y) * (p1.x - base.x) > 0;
}

bool isCCW(const Point& base, const Point& p1, const Point& p2) {
    return (p1.y - base.y) * (p2.x - p1.x) - (p2.y - p1.y) * (p1.x - base.x) < 0;
}

bool isColinear(const Point& base, const Point& p1, const Point& p2) {
    return (p1.y - base.y) * (p2.x - p1.x) - (p2.y - p1.y) * (p1.x - base.x) == 0;
}

int main() {
    int num_points, a, b;
    scanf("%d", &num_points);

    while (num_points > 0) {
        vector<Point> points;
        for (int i = 0; i < num_points; ++i) {
            scanf("%d %d", &a, &b);
            points.emplace_back(a, b);
        }

        // Calculate area
        double area = 0.0;
        for (int i = 1; i < num_points - 1; ++i) {
            area += cross_product(points[0], points[i], points[i+1]) / 2;
        }

        // if (isCCW(points[0], points[1], points[2])) {
        if (area > 0) {
            cout << "CCW ";
        }
        else {
            cout << "CW ";
        }
        cout << setprecision(1) << fixed << abs(area) << "\n";

        scanf("%d", &num_points);
    }

    return 0;
}
