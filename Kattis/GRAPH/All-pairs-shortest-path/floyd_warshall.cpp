#include <algorithm>
#include <iostream>
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

int main() {
    int n, m, q;
    int u, v, d;
    cin >> n >> m >> q;
    const int INF = 1000000000;
    while (n != 0 || m != 0 || q != 0) {
        vector<vector<int>> graph;
        for (int i = 0; i < n; ++i) {
            vector<int> temp(n, INF);
            graph.push_back(temp);
        }

        for (int i = 0; i < n; ++i) graph[i][i] = 0;

        // Read in all the edges
        for (int i = 0; i < m; ++i) {
            cin >> u >> v >> d;
            graph[u][v] = min(graph[u][v], d);
        }

        // Floyd - Warshall algorithm
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (graph[i][k] < INF && graph[k][j] < INF &&
                            graph[i][k] + graph[k][j] < graph[i][j]) {
                        graph[i][j] = graph[i][k] + graph[k][j];
                    }
                }
            }
        }

        // Finding negative cycles
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < n; ++k) {
                    if (graph[k][k] < 0 && graph[i][k] != INF && graph[k][j] != INF) {
                        graph[i][j] = -INF;
                    }
                }
            }
        }

        // Processing queries
        for (int i = 0; i < q; ++i) {
            cin >> u >> v;
            if (graph[u][v] == INF) cout << "Impossible" << endl;
            else if (graph[u][v] == -INF) cout << "-Infinity" << endl;
            else cout << graph[u][v] << endl;
        }

        cin >> n >> m >> q;
        if (n != 0 || m != 0 || q != 0) cout << endl;
    }
    return 0;
}
