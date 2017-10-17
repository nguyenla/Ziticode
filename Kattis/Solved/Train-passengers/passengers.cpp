#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int capacity, on_train = 0, num_stations;
    cin >> capacity >> num_stations;
    int left, enter, wait;
    
    bool possible(true);
    for (int i = 0; i < num_stations; ++i) {
        cin >> left >> enter >> wait;
        if (i == 0 && left != 0) {
            possible = false;
            break;
        }

        if (i == num_stations - 1 && (enter != 0 || left != on_train ||  wait != 0)) {
            possible = false;
            break;
        }

        on_train = on_train - left + enter;
        if (on_train > capacity || (on_train < capacity && wait > 0) || on_train < 0) {
            possible = false;
            break;
        }
    }
    if (possible) {
        cout << "possible" << '\n';
    }
    else {
        cout << "impossible" << '\n';
    }
    return 0;
}
