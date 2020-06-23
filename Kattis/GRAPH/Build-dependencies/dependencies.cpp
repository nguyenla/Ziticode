#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
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

int main() {
    int n;
    cin >> n;
    unordered_map<string, vector<string> > graphs;
    unordered_map<string, int> in_degrees;
    string line;
    getline(cin, line); // throw away

    for (int i = 0; i < n; ++i) {
        getline(cin, line);
        istringstream iss(line);
        string curfile;
        iss >> curfile;
        curfile = curfile.substr(0, curfile.size() - 1);

        string dependent;
        in_degrees[curfile] = 0;
        while (iss >> dependent) {
            if (graphs.find(dependent) == graphs.end()) {
                vector<string> dependents{curfile};
                graphs[dependent] = dependents;
            }
            else {
                graphs[dependent].emplace_back(curfile);
            }
            ++in_degrees[curfile];
        }
    }
    string modified;
    cin >> modified;

    // DFS to find all nodes reachable from modified
    stack<string> stk;
    unordered_set<string> reachable;
    stk.push(modified);
    while (!stk.empty()) {
        string cur = stk.top();
        reachable.insert(cur);
        stk.pop();
        if (graphs.find(cur) == graphs.end()) continue;

        auto dependents = graphs[cur];
        for (int i = 0; i < dependents.size(); ++i) {
            if (reachable.count(dependents[i]) == 0) {
                stk.push(dependents[i]);
            }
        }
    }

    // Reduce in-degrees to only include files in reachable
    for (const auto& item : graphs) {
        if (reachable.count(item.first) != 0) continue;
        for (int i = 0; i < item.second.size(); ++i) {
            // Disregard every edge from a non-reachable node to a reachable node
            if (reachable.count(item.second[i]) != 0) {
                --in_degrees[item.second[i]];
            }
        }
    }

    // Topological sort
    vector<string> orders;
    queue<string> first_nodes;
    first_nodes.push(modified);
    while (!first_nodes.empty()) {
        string cur = first_nodes.front();
        orders.push_back(cur);
        first_nodes.pop();

        // Reduce the indegrees of all dependencies of cur by 1
        if (graphs.find(cur) == graphs.end()) continue;
        auto dependents = graphs[cur];
        for (int i = 0; i < dependents.size(); ++i) {
            if (--in_degrees[dependents[i]] == 0) {
                first_nodes.push(dependents[i]);
            }
        }
    }
    for (int i = 0; i < orders.size(); ++i) {
        cout << orders[i] << "\n";
    }

    return 0;
}
