#include <algorithm>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Helper function to display vector
template <class T>
void print(const vector<T>& input) {
    for (const T& elem : input) {
        cout << elem << " ";
    }
    cout << "\n";
}

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

double distance(const Point& p1, const Point& p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

struct Edge {
    Edge(const int v1, const int v2, const double w) : v1(v1), v2(v2), weight(w) {}
    Edge() : v1(0), v2(0), weight(0) {}

    string tostring() const {
        return to_string(v1) + " -> " + to_string(v2) + ": " + to_string(weight);
    }
        
    int v1;
    int v2;
    double weight;
};

struct EdgeComparator {
    bool operator()(const Edge& e1, const Edge& e2) {
        return e1.weight < e2.weight;
    }
} edge_comp;

// Functions for union-find
void make_set(int v, vector<int>& parents, vector<int>& ranks) {
    parents[v] = v;
    ranks[v] = 0;
}

int find_set(int v, vector<int>& parents) {
    if (v == parents[v]) return v;
    parents[v] = find_set(parents[v], parents);
    return parents[v];
}

void union_set(int v1, int v2, vector<int>& parents, vector<int>& ranks) {
    int v1_root = find_set(v1, parents);
    int v2_root = find_set(v2, parents);
    if (v1_root != v2_root) {
        // Make the smaller set a subset of the bigger set
        if (ranks[v1_root] < ranks[v2_root]) swap(v1_root, v2_root);
        parents[v2_root] = v1_root;
        if (ranks[v1_root] == ranks[v2_root]) ++ranks[v1_root];
    }
}

// Kruskal's algorithm with union-find
// edges are sorted by weight in ascending order
double kruskal(const int n, const vector<Edge>& edges) {
    vector<int> parents(n);
    vector<int> ranks(n, 0);
    vector<Edge> mst;
    double total_weight = 0;

    // Start with a separate set for each vertex
    for (int i = 0; i < n; ++i) {
        make_set(i, parents, ranks);
    }

    for (const auto& edge : edges) {
        if (find_set(edge.v1, parents) != find_set(edge.v2, parents)) {
            mst.push_back(edge);
            union_set(edge.v1, edge.v2, parents, ranks);
            total_weight += edge.weight;
        }
    }
    return total_weight;
}

double getMinBridgeLength(const vector<Point>& islands) {
    vector<Edge> edges;
    for (int i = 0; i < islands.size() - 1; ++i) {
        for (int j = i + 1; j < islands.size(); ++j) {
            edges.emplace_back(i, j, distance(islands[i], islands[j]));
        }
    }
    sort(edges.begin(), edges.end(), edge_comp);
    return kruskal(islands.size(), edges);
}

int main() {
    int cases, num_islands;
    double x, y;
    cin >> cases;

    while (cases-- > 0) {
        cin >> num_islands;
        vector<Point> islands;
        for (int i = 0; i < num_islands; ++i) {
            cin >> x >> y;
            islands.emplace_back(x, y);
        }
        cout << setprecision(10) << fixed << getMinBridgeLength(islands) << endl;
    }

    return 0;
}
