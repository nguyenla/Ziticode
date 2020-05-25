#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int n, d;
    cin >> n;
    string line;
    getline(cin, line); // throw away
    getline(cin, line);
    stringstream iss(line);

    vector<int> gis;
    iss >> d;
    gis.push_back(d);

    for (int i = 1; i < n; ++i) {
        iss >> d;
        if (d > gis[gis.size() - 1]) gis.push_back(d);
    }

    cout << gis.size() << "\n";
    for (int i = 0; i < gis.size() - 1; ++i) {
        cout << gis[i] << " ";
    }
    cout << gis[gis.size() - 1] << "\n";

    return 0;
}
