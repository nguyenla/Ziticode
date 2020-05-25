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

// Comparator by x coordinate
struct PointXComparator {
    bool operator()(const Point& p1, const Point& p2) {
        return p1.x < p2.x;
    }
} x_comparator;

// Comparator by y coordinate
struct PointYComparator {
    bool operator()(const Point& p1, const Point& p2) {
        return p1.y < p2.y;
    }
} y_comparator;

void print(const Point& point) {
    cout << "(" << point.x << ", " << point.y << ")\n";
}

double findDistance(const Point& p1, const Point& p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

struct Segment {
    Segment(const Point& p1, const Point& p2) : p1(p1), p2(p2) {
        distance = findDistance(p1, p2);
    }

    Point p1;
    Point p2;
    double distance;
};

// Could return empty vector
vector<Point> findClosestMidStrip(const vector<Point>& strip, const double dist) {
    vector<Point> result;
    double min_dist = dist;
    for (int i = 0; i < strip.size() - 1; ++i) {
        for (int j = i + 1; j < strip.size() && strip[j].y - strip[i].y < min_dist; ++j) {
            double temp_dist = findDistance(strip[i], strip[j]);
            if (temp_dist < min_dist) {
                if (result.size() == 0) {
                    result.push_back(strip[i]);
                    result.push_back(strip[j]);
                }
                else {
                    result[0] = strip[i];
                    result[1] = strip[j];
                }
                min_dist = temp_dist;
            }
        }
    }
    return result;
}

vector<Point> findClosestPairHelper(vector<Point> x_sorted, vector<Point> y_sorted) {
    // Base cases
    if (y_sorted.size() < 2) {
        vector<Point> empty;
        return empty;
    }
    if (y_sorted.size() == 2) {
        return y_sorted;
    }
    else if (y_sorted.size() == 3) {
        double d1 = findDistance(y_sorted[0], y_sorted[1]);
        double d2 = findDistance(y_sorted[0], y_sorted[2]);
        double d3 = findDistance(y_sorted[1], y_sorted[2]);
        if (d1 <= d2 && d1 <= d3) return vector<Point>{y_sorted[0], y_sorted[1]};
        else if (d2 <= d1 && d2 <= d3) return vector<Point>{y_sorted[0], y_sorted[2]};
        else return vector<Point>{y_sorted[1], y_sorted[2]};
    }
    else {
        auto size = x_sorted.size();
        vector<Point> left_xsorted, left_ysorted, right_xsorted, right_ysorted;
        Point mid = x_sorted[size / 2];

        for (int i = 0; i < size; ++i) {
            if (y_sorted[i].x <= mid.x && i <= size / 2) {
                left_xsorted.push_back(y_sorted[i]);
                left_ysorted.push_back(y_sorted[i]);
            }
            else {
                right_xsorted.push_back(y_sorted[i]);
                right_ysorted.push_back(y_sorted[i]);
            }
        }

        auto left_closest = findClosestPairHelper(left_xsorted, left_ysorted);

        auto right_closest = findClosestPairHelper(right_xsorted, right_ysorted);

        vector<Point> closest;
        double min_dist = 1000000000;
        if (left_closest.size() == 2) {
            closest = left_closest;
            min_dist = findDistance(left_closest[0], left_closest[1]);
        }
        if (right_closest.size() == 2) {
            double right_dist = findDistance(right_closest[0], right_closest[1]);
            if (right_dist < min_dist) {
                closest = right_closest;
                min_dist = right_dist;
            }
        }

        // Go by y-sorted order, add points with x-coordinate no more than min_dist
        // away from x-coordinate of mid
        vector<Point> mid_strip;
        for (int i = 0; i < size; ++i) {
            if (abs(y_sorted[i].x - mid.x) < min_dist) {
                mid_strip.push_back(y_sorted[i]);
            }
        }
        auto mid_closest = findClosestMidStrip(mid_strip, min_dist);
        if (mid_closest.size() > 1 && findDistance(mid_closest[0], mid_closest[1]) < min_dist) {
            closest = mid_closest;
        }

        return closest;
    }
}

vector<Point> findClosestPair(const vector<Point>& points) {
    vector<Point> x_sorted;
    vector<Point> y_sorted;
    for (const auto& p : points) {
        x_sorted.push_back(p);
        y_sorted.push_back(p);
    }
    sort(x_sorted.begin(), x_sorted.end(), x_comparator);
    sort(y_sorted.begin(), y_sorted.end(), y_comparator);
    return findClosestPairHelper(x_sorted, y_sorted);
}


int main() {
    int num_points;
    double x, y;
    cin >> num_points;
    while (num_points > 0) {
        vector<Point> points;
        for (int i = 0; i < num_points; ++i) {
            scanf("%lf %lf", &x , &y);
            points.emplace_back(x, y);
        }
        auto closest = findClosestPair(points);
        if (closest.size() == 2) {
            cout << setprecision(2) << fixed << closest[0].x << " " << closest[0].y << " "
                 << closest[1].x << " " << closest[1].y << "\n";
        }

        cin >> num_points;
    }

    return 0;
}
