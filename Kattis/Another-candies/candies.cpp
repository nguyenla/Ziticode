#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int num_cases, num_students;
    cin >> num_cases;
    for (size_t i = 0; i != num_cases; ++i) {
        cin >> num_students;
        unsigned long long total = 0, n;

        for (size_t j = 0; j != num_students; ++j) {
            cin >> n;
            total += (n % num_students);
        }
        if (total % num_students == 0) {
            cout << "YES" << '\n';
        }
        else {
            cout << "NO" << '\n';
        }
    }
    return 0;
}
