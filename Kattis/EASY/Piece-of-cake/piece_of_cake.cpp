#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, h, v;
    cin >> n >> h >> v;
    cout << max(max(h * v, (n-h)*(n-v)), max(h * (n-v), v * (n-h))) * 4 << "\n";
    return 0;
}
