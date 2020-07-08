#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int a, b, c;
    while (cin >> a >> b >> c) {
        cout << "0.";
        for (int i = 0; i < c; ++i) {
            a *= 10;
            cout << a / b;
            a = a % b;
        }
        cout << endl;
    }
    return 0;
}
