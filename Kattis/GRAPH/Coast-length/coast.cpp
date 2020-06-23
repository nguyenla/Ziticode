#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Point {
    Point(const int x, const int y) : x(x), y(y) {}

    Point() : x(0), y(0) {}

    int x;
    int y;
};

// Helper function to display vector
template <class T>
void print(const vector<T>& input) {
    for (const T& elem : input) {
        cout << elem << " ";
    }
    cout << "\n";
}

string p2string(const int x, const int y) {
    return "(" + to_string(y) + ", " + to_string(x) + ")";
}

int main() {
    int m, n;
    cin >> n >> m;
    string line;
    getline(cin, line);

    vector<vector<char>> map;
    for (int i = 0; i < n; ++i) {
        getline(cin, line);
        // cout << line << endl;
        vector<char> temp;
        for (int j = 0; j < m; ++j) {
            temp.push_back(line[j]);
        }
        map.push_back(temp);
    }

    // 0: unprocessed, 1: added, 2: visited
    vector<vector<int>> visited;
    for (int i = 0; i < n; ++i) {
        vector<int> row(m, 0);
        visited.push_back(row);
    }

    // Mark sea squares as '-'
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (visited[i][j] == 2) continue;

            // Only start from a '0' square on the edge
            if (!(i == 0 || j == 0 || i == n - 1 || j == m - 1)) continue;
            if (map[i][j] != '0') continue;

            // BFS to find all sea squares
            queue<Point> sea;
            sea.emplace(j, i);
            while (!sea.empty()) {
                Point cur = sea.front();
                sea.pop();
                if (visited[cur.y][cur.x] == 2) continue;
                visited[cur.y][cur.x] = 2;
                map[cur.y][cur.x] = '-';

                // Add unvisited neighbors to the queue
                Point up(cur.x, cur.y - 1), down(cur.x, cur.y + 1), left(cur.x - 1, cur.y), right(cur.x + 1, cur.y);
                if (cur.y - 1 >= 0 && !visited[cur.y - 1][cur.x] && map[cur.y - 1][cur.x] == '0') {
                    visited[cur.y - 1][cur.x] = 1;
                    sea.push(up);
                }
                if (cur.y + 1 <= n-1 && !visited[cur.y + 1][cur.x] && map[cur.y + 1][cur.x] == '0') {
                    visited[cur.y + 1][cur.x] = 1;
                    sea.push(down);
                }
                if (cur.x - 1 >= 0 && !visited[cur.y][cur.x - 1] && map[cur.y][cur.x - 1] == '0') {
                    visited[cur.y][cur.x - 1] = 1;
                    sea.push(left);
                }
                if (cur.x + 1 <= m-1 && !visited[cur.y][cur.x + 1] && map[cur.y][cur.x + 1] == '0') {
                    visited[cur.y][cur.x + 1] = 1;
                    sea.push(right);
                }
            }
        }
    }

    // Re-use visited
    for (int i = 0; i < n; ++i) {
        fill(visited[i].begin(), visited[i].end(), 0);
    }
    int total_len = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (visited[i][j]) continue;
            if (map[i][j] != '1') continue;

            // BFS to find coast length of the current island
            queue<Point> island;
            island.emplace(j, i);

            while (!island.empty()) {
                Point cur = island.front();
                island.pop();
                if (visited[cur.y][cur.x] == 2) continue;
                visited[cur.y][cur.x] = 2;
                
                if (cur.y - 1 < 0  || map[cur.y - 1][cur.x] == '-') ++total_len;
                if (cur.y + 1 >= n || map[cur.y + 1][cur.x] == '-') ++total_len;
                if (cur.x - 1 < 0  || map[cur.y][cur.x - 1] == '-') ++total_len;
                if (cur.x + 1 >= m || map[cur.y][cur.x + 1] == '-') ++total_len;

                // Add unvisited neighbors to the queue
                Point up(cur.x, cur.y - 1), down(cur.x, cur.y + 1), left(cur.x - 1, cur.y), right(cur.x + 1, cur.y);
                if (cur.y - 1 >= 0 && !visited[cur.y - 1][cur.x] && map[cur.y - 1][cur.x] == '1') {
                    visited[cur.y - 1][cur.x] = 1;
                    island.push(up);
                }

                if (cur.y + 1 <= n - 1 && !visited[cur.y + 1][cur.x] && map[cur.y + 1][cur.x] == '1') {
                    visited[cur.y + 1][cur.x] = 1;
                    island.push(down);
                }

                if (cur.x - 1 >= 0 && !visited[cur.y][cur.x - 1] && map[cur.y][cur.x - 1] == '1') {
                    visited[cur.y][cur.x - 1] = 1;
                    island.push(left);
                }

                if (cur.x + 1 <= m - 1 && !visited[cur.y][cur.x + 1] && map[cur.y][cur.x + 1] == '1') {
                    visited[cur.y][cur.x + 1] = 1;
                    island.push(right);
                }
            }
        }
    }
    cout << total_len << "\n";

    return 0;
}
