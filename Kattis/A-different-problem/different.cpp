#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    unsigned long long a,b;
    while (cin >> a >> b) {
        if (a > b) {
            cout << a-b << '\n';
        }
        else {
            cout << b-a << '\n';
        }
    }
    return 0;
}
