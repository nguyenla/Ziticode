#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    while (n != 0) {
        int bits[32];
        for (int i = 0; i < 32; ++i) {
            bits[i] = -1;
        }
        string command;
        for (int i = 0; i < n; ++i) {
            int a, b;
            cin >> command >> a;
            if (command == "SET") {
                bits[a] = 1;
            }
            else if (command == "CLEAR") {
                bits[a] = 0;
            }
            else if (command == "AND") {
                cin >> b;
                if (bits[a] == 0 || bits[b] == 0) {
                    bits[a] = 0;
                }
                else if (bits[a] == -1 || bits[b] == -1) {
                    bits[a] = -1;
                }
                else {
                    bits[a] = 1;
                }
            }
            else if (command == "OR") {
                cin >> b;
                if (bits[a] == 1 || bits[b] == 1) {
                    bits[a] = 1;
                }
                else if (bits[a] == -1 || bits[b] == -1) {
                    bits[a] = -1;
                }
                else {
                    bits[a] = 0;
                }
            }
        }
        
        for (int i = 31; i >= 0; --i) {
            if (bits[i] == -1) cout << "?";
            else cout << bits[i];
        }
        cout << '\n';

        cin >> n;
    }
    return 0;
}
