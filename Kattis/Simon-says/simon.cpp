#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    string line;
    getline(cin, line); // throw away the rest of the first line

    for (int i = 0; i != n; ++i) {
        getline(cin, line);
        if (line.length() >= 11 && line.substr(0, 10) == "Simon says") {
            cout << line.substr(11, line.length() - 11) << '\n';
        }
    }
    return 0;
}
