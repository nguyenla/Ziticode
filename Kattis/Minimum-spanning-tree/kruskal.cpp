#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Edge {
    Edge(const int v1, const int v2, const int w) : v1(v1), v2(v2), weight(w) {}
    Edge() : v1(0), v2(0), weight(0) {}

    string tostring() const {
        return to_string(v1) + " -> " + to_string(v2) + ": " + to_string(weight);
    }
        
    int v1;
    int v2;
    int weight;
};

struct EdgeComparator {
    bool operator()(const Edge& e1, const Edge& e2) {
        return e1.weight < e2.weight;
    }
} edge_comp;

struct EdgeComparatorLex {
    bool operator()(const Edge& e1, const Edge& e2) {
        if (e1.v1 != e2.v1) return e1.v1 < e2.v1;
        return e1.v2 < e2.v2;
    }
} edge_comp_lex;

// Helper function to display vector
template <class T>
void print(const vector<T>& input) {
    for (const T& elem : input) {
        cout << elem << " ";
    }
    cout << "\n";
}

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

// Edges sorted by weight in ascending order
void solve(const int n, const vector<Edge>& edges) {
    // Kruskal's algorithm with union-find
    vector<int> parents(n);
    vector<int> ranks(n, 0);
    vector<Edge> mst;
    int total_weight = 0;
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
    if (mst.size() == n - 1) {
        sort(mst.begin(), mst.end(), edge_comp_lex);
        cout << total_weight << endl;
        for (const auto edge : mst) {
            cout << edge.v1 << " " << edge.v2 << endl;
        }
    }
    else {
        cout << "Impossible" << endl;
    }
}

int main() {
    int n, m, v1, v2, w;
    cin >> n >> m;
    while (n != 0 || m != 0) {
        vector<Edge> edges;
        for (int i = 0; i < m; ++i) {
            cin >> v1 >> v2 >> w;
            if (v1 < v2) edges.emplace_back(v1, v2, w);
            else edges.emplace_back(v2, v1, w);
        }
        sort(edges.begin(), edges.end(), edge_comp);
        solve(n, edges);
        // for (const auto& e : edges) {
        //     cout << e.tostring() << endl;
        // }
        cin >> n >> m;
    }
    return 0;
}
