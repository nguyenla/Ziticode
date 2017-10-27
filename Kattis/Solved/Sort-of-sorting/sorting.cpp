#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Comparator {
    bool operator() (const string& a, const string& b) {
        if (a[0] < b[0]) return true;
        if (a[0] > b[0]) return false;
        return a[1] < b[1];
    }
};


int main() {
    int n;
    cin >> n;
    while (n != 0) {
        string name;
        vector<string> names;
        for (int i = 0; i < n; ++i) {
            cin >> name;
            names.push_back(name);
        }
        Comparator comp;
        stable_sort(names.begin(), names.end(), comp);
        
        for (int i = 0; i < n; ++i) {
            cout << names[i] << '\n';
        }
        cin >> n;
        if (n != 0) cout << '\n';
    }
    return 0;
}
