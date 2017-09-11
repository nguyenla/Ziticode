#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int num_case;
    cin >> num_case;
    for (size_t i = 1; i <= num_case; ++i) {
        map<int, int> mp;
        int num_guests, x;
        cin >> num_guests;
        for (size_t j = 0; j != num_guests; ++j) {
            cin >> x;
            if (mp.find(x) == mp.end()) {
                mp[x] = 1;
            }
            else {
                mp.erase(mp.find(x));
            }
        }
        
        cout << "Case #" << i << ": ";
        for (map<int, int>::iterator it = mp.begin(); it != mp.end(); ++it) {
            if (it->second == 1) {
                cout << it->first << '\n';
                break;
            }
        }
    }

    return 0;
}
