#include <algorithm>
#include <iostream>
#include <math.h>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

// Sort points in counter clockwise order
struct Point {
    Point() {}

    Point(const Point& p) {
        x = p.x;
        y = p.y;
    }

    Point(const long x, const long y) : x(x), y(y) {}
    
    string toString() const {
        ostringstream oss;
        oss << "(" << x << ", " << y << ")";
        return oss.str();
    }

    bool operator==(const Point& p) {
        return x == p.x && y == p.y;
    }

    long x;
    long y;
};

void print(const Point& point) {
    cout << point.x << " " << point.y << "\n";
}

double distance(const Point& p1, const Point& p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

bool isCW(const Point& base, const Point& p1, const Point& p2) {
    return (p1.y - base.y) * (p2.x - p1.x) - (p2.y - p1.y) * (p1.x - base.x) > 0;
}

bool isCCW(const Point& base, const Point& p1, const Point& p2) {
    long temp = (p1.y - base.y) * (p2.x - p1.x) - (p2.y - p1.y) * (p1.x - base.x);
    if (temp == 0) {
        return distance(base, p1) < distance(base, p2);
    }
    return temp < 0;
}

bool isColinear(const Point& base, const Point& p1, const Point& p2) {
    return (p1.y - base.y) * (p2.x - p1.x) - (p2.y - p1.y) * (p1.x - base.x) == 0;
}

// Smallest to largest: bottom left point to top right
struct XYComparator {
    bool operator()(const Point& p1, const Point& p2) {
        if (p1.x != p2.x) {
            return p1.x < p2.x;
        }
        else {
            return p1.y < p2.y;
        }
    }
} xy_comparator;

// Smallest to largest: order of polar angle from root point
struct CCWComparator {
    CCWComparator(const Point& root) : root(root) {}

    Point root;

    // true means root - p1 - p2 is a counter-clockwise turn
    bool operator()(const Point& p1, const Point& p2) {
        return isCCW(root, p1, p2);
    }
};

struct DecreasingDistanceComparator {
    DecreasingDistanceComparator(const Point& root) : root(root) {}

    Point root;

    // true means p1 is further from root
    bool operator()(const Point& p1, const Point& p2) {
        return distance(root, p1) > distance(root, p2);
    }
};

int main() {
    string line;
    int num_points;
    long a, b;
    char included;
    scanf("%d", &num_points);
    vector<Point> y_orders;
    for (int i = 0; i < num_points; ++i) {
        scanf("%ld %ld %c", &a, &b, &included);
        if (included == 'Y') {
            y_orders.emplace_back(a, b);
        }
    }
    sort(y_orders.begin(), y_orders.end(), xy_comparator);

    Point bottom_left(y_orders[0]);
    vector<Point> ccw_orders;
    for (int i = 1; i < y_orders.size(); ++i) {
        ccw_orders.push_back(y_orders[i]);
    }
    sort(ccw_orders.begin(), ccw_orders.end(), CCWComparator(bottom_left));

    vector<Point> colinear_last;
    Point last_point = ccw_orders[ccw_orders.size() - 1];
    
    // Output
    cout << y_orders.size() << "\n";
    print(bottom_left);
    for (int i = 0; i < ccw_orders.size(); ++i) {
        if (!isColinear(bottom_left, ccw_orders[i], last_point)) {
            print(ccw_orders[i]);
        }
        else {
            colinear_last.push_back(ccw_orders[i]);
        }
    }

    // Sort colinear_last by decreasing distance from bottom left point
    sort(colinear_last.begin(), colinear_last.end(), DecreasingDistanceComparator(bottom_left));
    for (int i = 0; i < colinear_last.size(); ++i) {
        print(colinear_last[i]);
    }

    return 0;
}
