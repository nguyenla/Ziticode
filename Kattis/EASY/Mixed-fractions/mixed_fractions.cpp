#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    while (a != 0 && b != 0) {
        cout << (a/b) << " " << (a%b) << " / " << b << "\n";
        cin >> a >> b;
    }
    return 0;
}
