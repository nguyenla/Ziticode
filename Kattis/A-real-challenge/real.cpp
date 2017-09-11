#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    long area;
    cin >> area;
    double length = 4 * sqrt(area);
    printf("%.7f", length);
    return 0;
}
