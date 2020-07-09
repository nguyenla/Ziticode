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

void solve(const vector<int>& buttons, const int time) {
    if (time == 0) {
        cout << "0 0\n";
        return;
    }
    vector<int> shortest(3601, -1);
    queue<int> q;
    q.push(0);

    int count = 1;
    while (!q.empty()) {
        int qsize = q.size();
        for (int i = 0; i < qsize; ++i) {
            int cur = q.front();
            q.pop();
            for (const auto b : buttons) {
                int next = max(0, min(3600, b + cur));
                if (shortest[next] != -1) continue;
                q.push(next);
                shortest[next] = count;
                if (next == time) {
                    cout << count << " 0\n";
                    return;
                }
            }
        }
        ++count;
    }

    // Find closest to time
    for (int i = 0; i <= 3600; ++i) {
        if (shortest[time + i] != -1) {
            cout << shortest[time + i] << " " << i << endl;
            return;
        }
    }
}

int main() {
    int cases, n, time, b;
    cin >> cases;
    
    for (int t = 0; t < cases; ++t) {
        cin >> n >> time;
        vector<int> buttons;
        for (int i = 0; i < n; ++i) {
            cin >> b;
            buttons.push_back(b);
        }
        solve(buttons, time);
    }
    return 0;
}
