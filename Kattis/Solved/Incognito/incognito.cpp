#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int num_cases;
    cin >> num_cases;

    for (int i = 0; i < num_cases; ++i) {
        int num_items;
        cin >> num_items;
        string item, category;
        map<string, int> mp;

        for (int j = 0; j < num_items; ++j) {
            cin >> item >> category;
            if (mp.find(category) != mp.end()) {
                mp[category] = mp[category] + 1;
            }
            else {
                mp[category] = 1;
            }
        }
        long long res = 1;
        
        for (map<string, int>::iterator it = mp.begin(); it != mp.end(); ++it) {
            res = res * (it->second + 1);
        }
        cout << res - 1 << '\n';
    }
    return 0;
}
