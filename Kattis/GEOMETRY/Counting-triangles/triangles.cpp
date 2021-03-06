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

    string toString() const {
        return "(" + to_string(x) + ", " + to_string(y) + ")";
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

// 2 points (x1, y1) and (x2, y2) represent a line
struct Line {
    Line() {}
    Line(const double& x1, const double& y1, const double& x2, const double& y2) : p1(x1, y1), p2(x2, y2) {}

    string toString() const {
        return p1.toString() + ", " + p2.toString();
    }

    Point p1, p2;
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
    double orient = (p1.y - base.y) * (p2.x - p1.x) - (p2.y - p1.y) * (p1.x - base.x);
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

vector<Point> findIntersection(const Point& p1, const Point& p2, const Point& p3, const Point& p4) {
    vector<Point> res;
    if (!doIntersect(p1, p2, p3, p4)) return res;
    // Equation of segment p1 - p2 is of form: a1.x1 + b1.y1 = c1
    double a1 = p2.y - p1.y;
    double b1 = p1.x - p2.x;
    double c1 = a1 * p1.x + b1 * p1.y;

    // Equation of segment p3 - p4 is of form: a2.x3 + b2.y3 = c2
    double a2 = p4.y - p3.y;
    double b2 = p3.x - p4.x;
    double c2 = a2 * p3.x + b2 * p3.y;

    // determinant
    double det = a1 * b2 - a2 * b1;

    // Need to check for infinite number of points
    if (det == 0) {
        vector<Point> points{p1, p2, p3, p4};
        sort(points.begin(), points.end(), xy_comparator);

        // Add the two middle points, which mark the intersection segments
        if (points[1] == points[2]) { 
            res.push_back(points[1]);
        }
        else {
            res.push_back(points[1]);
            res.push_back(points[2]);
        }
        return res;
    }
    else {
        double x = (b2 * c1 - b1 * c2) * 1.0 / det;
        double y = (a1 * c2 - a2 * c1) * 1.0 / det;
        if (abs(x) < 0.005) x = 0.0;
        if (abs(y) < 0.005) y = 0.0;
        res.emplace_back(x, y);
        return res;
    }
}

int findNumTriangles(const vector<Line>& lines) {
    int num_triangles = 0;
    for (int i = 0; i < lines.size() - 2; ++i) {
        for (int j = i + 1; j < lines.size() - 1; ++j) {
            for (int k = j + 1; k < lines.size(); ++k) {
                auto intersect1 = findIntersection(lines[i].p1, lines[i].p2, lines[j].p1, lines[j].p2);
                auto intersect2 = findIntersection(lines[j].p1, lines[j].p2, lines[k].p1, lines[k].p2);
                auto intersect3 = findIntersection(lines[k].p1, lines[k].p2, lines[i].p1, lines[i].p2);

                if (intersect1.empty() || intersect2.empty() || intersect3.empty()) continue;
                if (isColinear(intersect1[0], intersect2[0], intersect3[0])) continue;
                if (intersect1[0] == intersect2[0] || intersect2[0] == intersect3[0] 
                        || intersect3[0] == intersect1[0]) continue;

                ++num_triangles;

            }
        }
    }
    return num_triangles;
}

int main() {
    int n;
    double x1, y1, x2, y2;

    cin >> n;
    while (n > 0) {
        vector<Line> lines;
        for (int i = 0; i < n; ++i) {
            cin >> x1 >> y1 >> x2 >> y2;
            lines.emplace_back(x1, y1, x2, y2);
        }

        cout << findNumTriangles(lines) << endl;
        cin >> n;
    }

    return 0;
}
