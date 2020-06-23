#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

/*
 * Shortest path from single source, negative cycle
 */

static const int INF = 1000000000;

struct Edge {
    int source;
    int dest;
    int weight;

    Edge(const int s, const int d, const int w) : source(s), dest(d), weight(w) {}
    Edge() {}
};

// Helper function to display vector
template <class T>
void print(const vector<T>& input) {
    for (const T num : input) {
        cout << num << " ";
    }
    cout << "\n";
}

// n: num vertices, s: source
vector<int> bellman_ford(int n, const vector<Edge>& edges, int s) {
    vector<int> pred(n, -1); // predecessor
    vector<int> res(n, INF); // shortest path length from source
    res[s] = 0;

    // Bellman-Ford runs at most n-1 times
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < edges.size(); ++j) {
            if (res[edges[j].source] < INF) {
                if (res[edges[j].dest] > res[edges[j].source] + edges[j].weight) {
                    res[edges[j].dest] = max(-INF, res[edges[j].source] + edges[j].weight);
                    pred[edges[j].dest] = edges[j].source;
                }
            }
        }
    }

    // Detect negative cycles
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < edges.size(); ++j) {
            if (res[edges[j].source] == -INF) res[edges[j].dest] = -INF;
            if (res[edges[j].source] != INF && res[edges[j].source] + edges[j].weight < res[edges[j].dest]) {
                res[edges[j].dest] = -INF;
            }
        }
    }

    // print(res);
    // print(neg_cycle);
    return res;
}

int main() {
    int n, m, q, s;
    string line;
    cin >> n >> m >> q >> s;
    getline(cin, line); // throw away

    while (n || m || q || s) {
        vector<Edge> edges;

        int v1, v2, w;
        for (int i = 0; i < m; ++i) {
            getline(cin, line);
            istringstream iss(line);
            iss >> v1 >> v2 >> w;
            edges.emplace_back(v1, v2, w);
        }
        auto paths = bellman_ford(n, edges, s);

        // vector<int> queries;
        int d;
        for (int i = 0; i < q; ++i) {
            cin >> d;
            if (paths[d] == -INF) cout << "-Infinity\n";
            else if (paths[d] == INF) cout << "Impossible\n";
            else cout << paths[d] << "\n";
        }
        cin >> n >> m >> q >> s;
        if (n || m || q || s) cout << "\n";
        getline(cin, line); // throw away
    }

    return 0;
}
