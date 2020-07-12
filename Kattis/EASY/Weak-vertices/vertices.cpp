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
    int n;
    string line;
    cin >> n;
    getline(cin, line); // throw away

    while (n != -1) {
        vector<vector<int>> graph;
        int x = -1;
        for (int i = 0; i < n; ++i) {
            getline(cin, line);
            vector<int> row;
            istringstream iss(line);
            for (int j = 0; j < n; ++j) {
                iss >> x;
                row.push_back(x);
            }
            graph.push_back(row);
            // print(row);
        }

        // Find weak vertices
        vector<int> weak;
        for (int i = 0; i < n; ++i) {
            bool is_weak = true;
            for (int j = 0; j < n - 1; ++j) {
                for (int k = 0; k < n; ++k) {
                    if (graph[i][j] == 1 && graph[i][k] == 1 && graph[j][k] == 1) is_weak = false;
                }
            }
            if (is_weak) weak.push_back(i);
        }

        print(weak);
        cin >> n;
        getline(cin, line); // throw away
    }
    return 0;
}
