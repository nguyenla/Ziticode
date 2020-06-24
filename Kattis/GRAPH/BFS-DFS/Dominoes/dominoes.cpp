#include <algorithm>
#include <iostream>
#include <queue>
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

int solve(const vector<vector<int>>& graph, const vector<int>& fallen) {
    int size = graph.size();
    vector<int> visited(size, false);
    int total_fallen = 0;
    queue<int> bfs;

    for (int i = 0; i < fallen.size(); ++i) {
        bfs.push(fallen[i]);
    }

    while (!bfs.empty()) {
        int next = bfs.front();
        bfs.pop();
        if (visited[next]) continue;
        visited[next] = true;
        ++total_fallen;
        for (int j = 0; j < graph[next].size(); ++j) {
            int d = graph[next][j];
            if (visited[d]) continue;
            bfs.push(d);
        }

    }
    return total_fallen;
}

int main() {
    int cases, n, m, l, src, des;
    cin >> cases;

    for (int c = 0; c < cases; ++c) {
        cin >> n >> m >> l;
        vector<vector<int>> graph(n + 1);
        for (int i = 0; i < m; ++i) {
            cin >> src >> des;
            graph[src].push_back(des);
        }

        int d = 0;
        vector<int> fallen;
        for (int i = 0; i < l; ++i) {
            cin >> d;
            fallen.push_back(d);
        }

        cout << solve(graph, fallen) << endl;
    }
    return 0;
}
