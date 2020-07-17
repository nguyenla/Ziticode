#include <algorithm>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
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

// Add all cities that are in a cycle to the set 'cycles'
void dfs(const string& city, const unordered_map<string, vector<string>>& graph,
        unordered_set<string>& cycles, unordered_set<string>& visited, bool& has_cycle) {
    visited.insert(city);
    for (const string& dest : graph.at(city)) {
        if (!has_cycle) {
            if (visited.count(dest) > 0) {
                has_cycle = true;
                return;
            }
            else {
                dfs(dest, graph, cycles, visited, has_cycle);
            }
        }
    }
    visited.erase(city);
    if (has_cycle) cycles.insert(city);
}

void solve(const unordered_map<string, vector<string>>& graph, const vector<string>& queries) {
    unordered_set<string> cycles, visited;
    bool has_cycle = false;

    for (int i = 0; i < queries.size(); ++i) {
        if (cycles.count(queries[i]) > 0) {
            cout << queries[i] << " safe" << endl;
            continue;
        }

        has_cycle = false;
        visited.clear();

        // DFS recursive traversal
        dfs(queries[i], graph, cycles, visited, has_cycle);
        if (has_cycle) cout << queries[i] << " safe" << endl;
        else cout << queries[i] << " trapped" << endl;
    }
}

int main() {
    int n;
    string origin, dest;
    cin >> n;
    unordered_map<string, vector<string>> graph;

    for (int i = 0; i < n; ++i) {
        cin >> origin >> dest;
        if (graph.find(origin) == graph.end()) {
            vector<string> temp{dest};
            graph[origin] = temp;
        }
        else {
            graph[origin].push_back(dest);
        }

        if (graph.find(dest) == graph.end()) {
            vector<string> temp;
            graph[dest] = temp;
        }
    }
    string line;
    getline(cin, line); // throw away
    vector<string> queries;

    while (getline(cin, line)) {
        queries.push_back(line);
    }
    solve(graph, queries);

    return 0;
}
