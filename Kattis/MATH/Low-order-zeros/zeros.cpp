#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

int findLowestOrderZero(const int n, map<int, int>& store) {
    if (store.find(n) != store.end()) {
        return store[n];
    }
    map<int, int> mp = {{2, 6}, {4, 2}, {6, 8}, {8, 4}};

    int res = 1;
    for (int i = 2; i <= n; ++i) {
        int root = i;
        while (root % 10 == 0) root /= 10;
        while (root % 5 == 0) {
            if (mp.find(res) == mp.end()) {
                cout << "Cannot find res = " << res << endl;
                break;
            }
            res = mp[res];
            root /= 5;
        }

        res = (res * root);
        while (res % 10 == 0) {
            res /= 10;
        }
        res = res % 10;
        store[i] = res;
    }
    return res;
}

int main() {
    int n;
    cin >> n;
    map<int, int> store;
    findLowestOrderZero(1000000, store); // populate store

    while (n != 0) {
        cout << findLowestOrderZero(n, store) << endl;
        cin >> n;
    }
    return 0;
}
