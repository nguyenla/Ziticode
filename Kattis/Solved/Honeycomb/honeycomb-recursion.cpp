#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

long long num_walks(int n, long long* walks)
{
    if (walks[n] < 0)
    {
        walks[n-3] = num_walks(n-3, walks);
        walks[n-2] = num_walks(n-2, walks);
        walks[n-1] = num_walks(n-1, walks);
        walks[n] = (walks[n-1] * n + 24 * walks[n-2] * n + 36 * walks[n-3] * n 
                - 24 * walks[n-2] - 72 * walks[n-3]) * (n - 1)/ (n * n);
    }
    return walks[n];
}

int main() {
    long long walks[15];
    walks[0] = 1;
    walks[1] = 0;
    walks[2] = 6;
    for (int i = 3; i < 15; i++) walks[i] = -1;
    int n;
    cin >> n;
    while(n--)
    {
        int path;
        cin >> path;
        cout << num_walks(path, walks) << '\n';
    }
    return 0;
}
