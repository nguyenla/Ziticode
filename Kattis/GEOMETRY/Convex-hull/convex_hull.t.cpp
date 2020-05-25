#include <iostream>
#include <math.h>
#include <sstream>
#include <stack>
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

bool isCW(const Point& base, const Point& p1, const Point& p2) {
    return (p1.y - base.y) * (p2.x - p1.x) - (p2.y - p1.y) * (p1.x - base.x) > 0;
}

bool isCCW(const Point& base, const Point& p1, const Point& p2) {
    // cout << "Check CCW:\n";
    // print(base);
    // print(p1);
    // print(p2);
    // cout << (p1.y - base.y) * (p2.x - p1.x) - (p2.y - p1.y) * (p1.x - base.x) << "\n";
    return (p1.y - base.y) * (p2.x - p1.x) - (p2.y - p1.y) * (p1.x - base.x) < 0;
}

bool isColinear(const Point& base, const Point& p1, const Point& p2) {
    // cout << "Check Colinear:\n";
    // print(base);
    // print(p1);
    // print(p2);
    // cout << (p1.y - base.y) * (p2.x - p1.x) - (p2.y - p1.y) * (p1.x - base.x) << "\n";
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

    // true means p1 is clockwise compared to p2 with respect to root
    bool operator()(const Point& p1, const Point& p2) {
        return isCW(root, p1, p2);
    }
};

void test() {
    Point p1(5, 1);
    Point p2(7, 3);
    Point p3(3, 3);
    Point p4(5, 3);
    Point p5(6, 5);
    Point p6(1, 1);
    vector<Point> points{p1, p2, p3, p4, p5};
    sort(points.begin(), points.end(), PolarComparator(p6));
    cout << "Polar-order: \n";
    for (const auto& point : points) {
        cout << "(" << point.x << ", " << point.y << ")\n";
    }

    sort(points.begin(), points.end(), y_comparator);
    cout << "Y-order: \n";
    for (const auto& point : points) {
        cout << "(" << point.x << ", " << point.y << ")\n";
    }

    Point p7(0, 0);
    Point p8(0, 10);
    Point p9(10, 0);
    cout << "Check CCW p7 p8 p9: " << isCCW(p7, p8, p9) << "\n";
    cout << "Check CW p7 p8 p9: " << isCW(p7, p8, p9) << "\n";
    cout << "Check CW p8 p9 p7: " << isCW(p8, p9, p7) << "\n";
}

// vector<Point> findConvexHull(const vector<Point>& points) {
// }

int main() {
    string line;
    int num_points, a, b;
    scanf("%d", &num_points);
    while (num_points > 0) {
        vector<Point> y_orders;
        for (int i = 0; i < num_points; ++i) {
            scanf("%d %d", &a, &b);
            y_orders.emplace_back(a, b);
        }
        sort(y_orders.begin(), y_orders.end(), y_comparator);
        Point bottom_left(y_orders[0]);

        // Sort all points other than bottom left by polar order
        vector<Point> polar_orders;
        for (int i = 1; i < y_orders.size(); ++i) {
            polar_orders.push_back(y_orders[i]);
        }
        // cout << "Polar order before: \n";
        // for (const auto& point : polar_orders) {
        //     print(point);
        // }
        // cout << "---------------------\n";

        sort(polar_orders.begin(), polar_orders.end(), PolarComparator(bottom_left));
        // cout << "Polar order after: \n";
        // for (const auto& point : polar_orders) {
        //     print(point);
        // }
        // cout << "---------------------\n";

        stack<Point> convex_hull;
        convex_hull.push(bottom_left);
        int index = 0;
        while (polar_orders[index] == bottom_left) {
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
                    // cout << "Colinear\n";
                    if (distance(p1, p2) <= distance(p1, p3)) {
                        convex_hull.push(p3);
                        ++index;
                    }
                }
            }
        }

        // Print convex hull
        cout << "Convex hull:\n";
        cout << convex_hull.size() << "\n";
        while (!convex_hull.empty()) {
            Point next = convex_hull.top();
            convex_hull.pop();
            cout << "(" << next.x << ", " << next.y << ")\n";
        }

        scanf("%d", &num_points);
    }


    return 0;
}
