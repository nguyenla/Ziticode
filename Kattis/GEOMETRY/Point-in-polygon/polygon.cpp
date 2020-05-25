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

    bool operator==(const Point& p) {
        return x == p.x && y == p.y;
    }

    double x;
    double y;
};

void print(const Point& point) {
    cout << "(" << point.x << ", " << point.y << ")\n";
}

// Check if 3 points are colinear
bool isColinear(const Point& base, const Point& p1, const Point& p2) {
    return (p1.y - base.y) * (p2.x - p1.x) - (p2.y - p1.y) * (p1.x - base.x) == 0;
}

// 0: colinear, -1: CCW, 1: CW
int getOrientation(const Point& base, const Point& p1, const Point& p2) {
    int orient = (p1.y - base.y) * (p2.x - p1.x) - (p2.y - p1.y) * (p1.x - base.x);
    if (orient < 0) return -1;
    else if (orient > 0) return 1;
    else return 0;
}

bool isOnSegment(const Point& point, const Point& p1, const Point& p2) {
    if (!isColinear(point, p1, p2)) return false;
    if (point.x <= max(p1.x, p2.x) && point.x >= min(p1.x, p2.x) &&
            point.y <= max(p1.y, p2.y) && point.y >= min(p1.y, p2.y)) {
        return true;
    }
    else return false;
}

// Check if segments p1-p2 and p3-p4 intersect
bool doIntersect(const Point& p1, const Point& p2, const Point& p3, const Point& p4) {
    int o1 = getOrientation(p1, p2, p3);
    int o2 = getOrientation(p1, p2, p4);
    int o3 = getOrientation(p3, p4, p1);
    int o4 = getOrientation(p3, p4, p2);

    if (o1 != o2 && o3 != o4) return true;

    // Special cases: if there are three colinear points
    if (o1 == 0 && isOnSegment(p3, p1, p2)) return true;
    if (o2 == 0 && isOnSegment(p4, p1, p2)) return true;
    if (o3 == 0 && isOnSegment(p1, p3, p4)) return true;
    if (o4 == 0 && isOnSegment(p2, p3, p4)) return true;

    return false;
}

int checkPointInPolygon(const vector<Point>& polygon, const Point& point, const Point& external) {
    int count = 0;
    bool onPolygon = false;
    int j = polygon.size() - 1;
    for (int i = 0; i < polygon.size(); ++i) {
        onPolygon = onPolygon || isOnSegment(point, polygon[j], polygon[i]);
        if (doIntersect(point, external, polygon[j], polygon[i])) {
            if (isOnSegment(polygon[i], point, external)) {
                if (getOrientation(point, external, polygon[j]) == 1) {
                    ++count;
                }
            }
            else if (isOnSegment(polygon[j], point, external)) {
                if (getOrientation(point, external, polygon[i]) == 1) {
                    ++count;
                }
            }
            else if (!(isOnSegment(polygon[j], point, external) && isOnSegment(polygon[i], point, external))) {
                ++count;
            }
        }
        j = i;
    }

    if (onPolygon) return 0; // on
    if (count % 2 == 0) {
        return -1; // out
    }
    else {
        return 1; // in
    }
}

int main() {
    int num_vertices, a, b;
    cin >> num_vertices;
    while (num_vertices != 0) {
        vector<Point> polygon;
        for (int i = 0; i < num_vertices; ++i) {
            scanf("%d %d", &a, &b);
            polygon.emplace_back(a, b);
        }

        int num_points;
        cin >> num_points;
        int count = 0;
        for (int i = 0; i < num_points; ++i) {
            scanf("%d %d", &a, &b);
            Point point(a, b);
            Point external(10001, 10009); // Known to be outside the polygon
            int check1 = checkPointInPolygon(polygon, point, external);
            if (check1 == 0) {
                cout << "on\n";
            }
            else if (check1 < 0) {
                cout << "out\n";
            }
            else {
                cout << "in\n";
            }
        }
        cin >> num_vertices;
    }

    return 0;
}
