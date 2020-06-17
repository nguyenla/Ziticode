#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    int cases, n;
    cin >> cases;
    for (int i = 1; i <= cases; ++i) {
        cin >> n;
        string line;
        vector<long> v1, v2;
        long x;

        getline(cin, line); // throw away
        getline(cin, line);
        istringstream iss1(line);
        for (int j = 0; j < n; ++j) {
            iss1 >> x;
            v1.push_back(x);
        }
        sort(v1.begin(), v1.end());

        getline(cin, line);
        istringstream iss2(line);
        for (int j = 0; j < n; ++j) {
            iss2 >> x;
            v2.push_back(x);
        }
        sort(v2.rbegin(), v2.rend());

        long sum = 0;
        for (int j = 0; j < n; ++j) {
            sum += v1[j] * v2[j];
        }

        cout << "Case #" << i << ": ";
        cout << sum;
        cout << "\n";
    }


    return 0;
}
