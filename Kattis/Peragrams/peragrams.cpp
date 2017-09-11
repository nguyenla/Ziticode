#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    string line;
    cin >> line;

    map<char, int> mp;
    typedef map<char, int>::iterator IT;

    for (size_t i = 0; i != line.length(); ++i) {
        if (mp.find(line[i]) == mp.end()) {
            mp[line[i]] = 1;
        }
        else {
            mp[line[i]] = mp[line[i]] + 1;
        }
    }

    int num_odd = 0;
    for (IT it = mp.begin(); it != mp.end(); ++it) {
        if (it -> second % 2 == 1) {
            ++num_odd;
        }
    }

    if (num_odd <= 1) {
        cout << 0 << '\n';
    }
    else {
        cout << num_odd - 1 << '\n';
    }

    return 0;
}
