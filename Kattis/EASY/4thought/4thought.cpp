#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    for (size_t i = 0; i != n; ++i) {
        int aim;
        cin >> aim;
        switch (aim) {
            case 0:
                cout << "4 - 4 + 4 - 4 = 0" << '\n';
                break;
            case 1:
                cout << "4 - 4 + 4 / 4 = 1" << '\n';
                break;
            case 2:
                cout << "4 / 4 + 4 / 4 = 2" << '\n';
                break;
            case 4:
                cout << "4 / 4 / 4 + 4 = 4" << '\n';
                break;
            case 7:
                cout << "4 + 4 - 4 / 4 = 7" << '\n';
                break;
            case 8:
                cout << "4 + 4 + 4 - 4 = 8" << '\n';
                break;
            case 9:
                cout << "4 + 4 + 4 / 4 = 9" << '\n';
                break;
            case 15:
                cout << "4 * 4 - 4 / 4 = 15" << '\n';
                break;
            case 16:
                cout << "4 * 4 * 4 / 4 = 16" << '\n';
                break;
            case 17:
                cout << "4 * 4 + 4 / 4 = 17" << '\n';
                break;
            case 24:
                cout << "4 * 4 + 4 + 4 = 24" << '\n';
                break;
            case 32:
                cout << "4 * 4 + 4 * 4 = 32" << '\n';
                break;
            case 60:
                cout << "4 * 4 * 4 - 4 = 60" << '\n';
                break;
            case 68:
                cout << "4 * 4 * 4 + 4 = 68" << '\n';
                break;
            case 256:
                cout << "4 * 4 * 4 * 4 = 256" << '\n';
                break;
            case -1:
                cout << "4 - 4 - 4 / 4 = -1" << '\n';
                break;
            case -4:
                cout << "4 / 4 / 4 - 4 = -4" << '\n';
                break;
            case -7:
                cout << "4 / 4 - 4 - 4 = -7" << '\n';
                break;
            case -8:
                cout << "4 - 4 - 4 - 4 = -8" << '\n';
                break;
            case -15:
                cout << "4 / 4 - 4 * 4 = -15" << '\n';
                break;
            case -16:
                cout << "4 - 4 - 4 * 4 = -16" << '\n';
                break;
            case -60:
                cout << "4 - 4 * 4 * 4 = -60" << '\n';
                break;
            default:
                cout << "no solution\n";

        }
    }
    return 0;
}
