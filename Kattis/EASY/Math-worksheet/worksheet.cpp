#include <algorithm>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Helper function to display vector
template <class T>
void print(const vector<T>& input) {
    for (const T& elem : input) {
        cout << elem << " ";
    }
    cout << "\n";
}

int main() {
    int n, a, b;
    char op;
    cin >> n;

    while (n != 0) {
        vector<string> nums;
        int max_length = 0;

        for (int i = 0; i < n; ++i) {
            cin >> a >> op >> b;
            if (op == '*') {
                nums.push_back(to_string(a * b));
            }
            else if (op == '+') {
                nums.push_back(to_string(a + b));
            }
            else if (op == '-') {
                nums.push_back(to_string(a - b));
            }
            int length = nums[nums.size() - 1].size();
            // cout << length << endl;
            max_length = max(max_length, length);
        }

        // cout << max_length << endl;
        int num_cols = 51 / (max_length + 1);
        // cout << "Num cols: " << num_cols << endl;

        // vector<string>;
        int num_entries = 0;
        while (num_entries < nums.size()) {
            ostringstream oss;
            bool is_first = true;

            for (int i = 0; i < num_cols; ++i) {
                if (num_entries == nums.size()) break;
                if (!is_first) oss << " ";
                else is_first = false;

                // padding
                for (int j = 0; j < max_length - nums[num_entries].size(); ++j) {
                    oss << " ";
                }
                oss << nums[num_entries];
                ++num_entries;
            }
            cout << oss.str() << endl;
        }

        cin >> n;
        if (n > 0) cout << endl;
    }
    return 0;
}
