#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int a, b, c, x, y, z;
    string line;
    cin >> x >> y >> z;
    map<char, int> mp;
    
    if (x <= y && y <= z) {
        a = x;
        b = y; 
        c = z;
    }
    else if (x <=z && z <= y) {
        a = x;
        b = z;
        c = y;
    }
    else if (z <= x && x <= y) {
        a = z;
        b = x;
        c = y;
    }
    else if (z <= y && y <= x) {
        a = z;
        b = y;
        c = x;
    }
    else if (y <= x && x <= z) {
        a = y;
        b = x;
        c = z;
    }
    else {
        a = y;
        b = z;
        c = x;
    }

    getline(cin, line);
    getline(cin, line);

    for (size_t i = 0; i != line.length(); ++i) {
        if (line[i] == 'A') {
            cout << a << " ";
        }
        else if (line[i] == 'B') {
            cout << b << " ";
        }
        else {
            cout << c << " ";
        }
    }
    
    return 0;
}
