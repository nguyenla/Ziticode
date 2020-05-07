#include <algorithm>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct Position {
    int x;
    int y;

    Position() {}
    Position(int x, int y) : x(x), y(y) {}
};

double distance(Position pos1, Position pos2) {
    return sqrt((pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y));
}

int main() {
    int num;
    unordered_map<int, Position> positions;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cin >> num;
            positions[num] = Position(i, j);
        }
    }
    double sum_distances = 0;
    for (int i = 2; i <= 9; ++i) {
        sum_distances += distance(positions[i], positions[i-1]);
    }
    cout << setprecision(10) << sum_distances << "\n";
    return 0;
}
