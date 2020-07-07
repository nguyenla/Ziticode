#include <algorithm>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

// Convex Hull computation using Graham's scan
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

double distance(const Point& p1, const Point& p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

bool isCW(const Point& base, const Point& p1, const Point& p2) {
    return (p1.y - base.y) * (p2.x - p1.x) - (p2.y - p1.y) * (p1.x - base.x) > 0;
}

bool isCCW(const Point& base, const Point& p1, const Point& p2) {
    return (p1.y - base.y) * (p2.x - p1.x) - (p2.y - p1.y) * (p1.x - base.x) < 0;
}

bool isColinear(const Point& base, const Point& p1, const Point& p2) {
    return (p1.y - base.y) * (p2.x - p1.x) - (p2.y - p1.y) * (p1.x - base.x) == 0;
}

// Smallest to largest: bottom left point to top right
struct PointYComparator {
    bool operator()(const Point& p1, const Point& p2) {
        if (p1.y != p2.y) {
            return p1.y < p2.y;
        }
        else {
            return p1.x < p2.x;
        }
    }
} y_comparator;

// Smallest to largest: order of polar angle from root point
struct PolarComparator {
    PolarComparator(const Point& root) : root(root) {}

    Point root;

    // true means root - p1 - p2 is a clockwise turn
    bool operator()(const Point& p1, const Point& p2) {
        if (isColinear(root, p1, p2)) {
            return distance(root, p1) < distance(root, p2);
        }
        return isCW(root, p1, p2);
    }
};

// Return a vector of Point on the convex hull
vector<Point> findConvexHull(const vector<Point>& y_orders) {
    Point bottom_left(y_orders[0]);

    // Sort all points other than bottom left by polar order
    vector<Point> polar_orders;
    for (int i = 1; i < y_orders.size(); ++i) {
        polar_orders.push_back(y_orders[i]);
    }
    sort(polar_orders.begin(), polar_orders.end(), PolarComparator(bottom_left));

    // Shortcut if there are 3 points or fewer
    if (y_orders.size() <= 3) {
        polar_orders.push_back(bottom_left);
        return polar_orders;
    }

    stack<Point> convex_hull;
    convex_hull.push(bottom_left);
    int index = 0;
    while (index < polar_orders.size() && polar_orders[index] == bottom_left) {
        ++index;
    }

    if (index < polar_orders.size()) {
        convex_hull.push(polar_orders[index]);
        ++index;
    }

    while (index < polar_orders.size()) {
        Point p3 = polar_orders[index];
        if (convex_hull.size() < 2) {
            convex_hull.push(p3);
            continue;
        }
        else {
            Point p2 = convex_hull.top();
            convex_hull.pop();
            Point p1 = convex_hull.top();

            if (isCW(p1, p2, p3)) {
                convex_hull.push(p2);
                convex_hull.push(p3);
                ++index;
            }
            else if (isColinear(p1, p2, p3)) {
                if (distance(p1, p2) <= distance(p1, p3)) {
                    convex_hull.push(p3);
                    ++index;
                }
            }
        }
    }

    // Check if the last two points and the base point are collinear
    if (convex_hull.size() >= 3) {
        Point last = convex_hull.top();
        convex_hull.pop();
        Point second_last = convex_hull.top();
        if (isColinear(bottom_left, second_last, last)) {
            if (distance(bottom_left, second_last) <= distance(bottom_left, last)) {
                convex_hull.pop();
                convex_hull.push(last);
            }
        }
        else {
            convex_hull.push(last);
        }
    }

    // Put points into a vector
    vector<Point> hull;
    while (!convex_hull.empty()) {
        Point next = convex_hull.top();
        convex_hull.pop();
        hull.push_back(next);
    }
    return hull;
}

double findPerimeter(const vector<Point>& points) {
    if (points.size() <= 1) return 0;
    double res = 0;
    for (int i = 0; i < points.size() - 1; ++i) {
        res = res + distance(points[i], points[i + 1]);
    }
    return res + distance(points[0], points[points.size() - 1]);
}

int main() {
    string line;
    double x, y;
    while (getline(cin, line)) {
        istringstream iss(line);
        vector<Point> y_orders;
        while (iss >> x >> y) {
            y_orders.emplace_back(x, y);
        }
        // Sort by y-coordinates, then x-coordinates
        sort(y_orders.begin(), y_orders.end(), y_comparator);

        auto convex_hull = findConvexHull(y_orders);
        double perimeter = findPerimeter(convex_hull);
        cout << setprecision(10) << fixed << 100 * y_orders.size() / (1 + perimeter) << endl;
    }

    return 0;
}
