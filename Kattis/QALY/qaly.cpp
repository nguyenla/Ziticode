#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int main() {
    int n;
    cin >> n;
    double sum = 0;
    for (int i = 0; i < n; ++i) {
        double quality, year;
        cin >> quality >> year;
        sum += quality * year;
    }
    cout.precision(3);
    cout << fixed <<  sum;
    return 0;
}
