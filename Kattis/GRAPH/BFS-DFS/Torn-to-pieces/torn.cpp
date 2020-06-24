#include <algorithm>
#include <iostream>
#include <queue>
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

vector<string> solve(const unordered_map<string, unordered_set<string>>& graph, const string& src, const string& des) {
    vector<string> res;
    queue<string> bfs;
    unordered_map<string, string> prev;
    unordered_set<string> visited;
    bfs.push(src);

    while (!bfs.empty()) {
        string next = bfs.front();
        bfs.pop();
        if (visited.count(next) != 0) continue;
        visited.insert(next);

        if (graph.find(next) == graph.end()) continue; // No station connected to this station

        for (const auto& station : graph.at(next)) {
            if (visited.count(station) != 0) continue;
            prev[station] = next;
            bfs.push(station);
        }
    }

    if (visited.count(des) == 0) return res;
    string cur(des);
    while (prev.find(cur) != prev.end() && prev[cur] != src) {
        res.push_back(cur);
        cur = prev[cur];
    }
    res.push_back(cur);
    res.push_back(src);

    return res;
}

int main() {
    int n;
    string line, src, des;
    cin >> n;
    getline(cin, line); // throw away

    unordered_map<string, unordered_set<string>> graph;
    for (int i = 0; i < n; ++i) {
        getline(cin, line);
        istringstream iss(line);
        iss >> src;

        if (graph.find(src) == graph.end()) {
            unordered_set<string> stations;
            graph[src] = stations;
        }
        if (graph.find(des) == graph.end()) {
            unordered_set<string> stations;
            graph[des] = stations;
        }

        while (iss >> des) {
            graph[src].insert(des);
            graph[des].insert(src);
        }
    }

    cin >> src >> des;
    auto res = solve(graph, src, des);
    if (res.empty()) cout << "no route found" << endl;
    else {
        for (int i = res.size() - 1; i >= 1; --i) {
            cout << res[i] << " ";
        }
        cout << res[0] << endl;
    }
    return 0;
}
