#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, b;
    vector<int> books;
    cin >> n;
    for (size_t i = 0; i != n; ++i) {
        cin >> b;
        books.push_back(b);
    }

    sort(books.begin(), books.end(), std::greater<int>());
    unsigned long long total = 0;
    for (size_t i = 0; i != n; ++i) {
        if (i % 3 != 2) {
            total += books[i];
        }
    }
    cout << total << '\n';

    return 0;
}
