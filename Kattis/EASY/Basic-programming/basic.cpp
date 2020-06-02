#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// Helper function to display vector
void print(const vector<int>& input) {
    for (const int num : input) {
        cout << num << " ";
    }
    cout << "\n";
}

bool func1(const vector<int>& input) {
    unordered_map<int, int> um;
    for (int i = 0; i < input.size(); ++i) {
        um[input[i]] = 1;
    }
    bool found = false;
    for (int i = 0; i < input.size(); ++i) {
        int target = 7777 - input[i];
        if (um.find(target) != um.end()) {
            found = true;
        }
    }
    return found;
}

bool func2(const vector<int>& input) {
    for (int i = 0; i < input.size() - 1; ++i) {
        if (input[i] == input[i + 1]) return false;
    }
    return true;
}

int func3(const vector<int>& input) {
    double size = input.size();
    size /= 2;
    int count = 1;
    int cur_i = 1;
    int cur = input[0];
    while (cur_i < input.size()) {
        if (input[cur_i] == input[cur_i - 1]) {
            ++count;
            ++cur_i;
        }
        else {
            if (count > size) return cur;
            else {
                cur = input[cur_i];
                count = 1;
                ++cur_i;
            }
        }
    }
    if (count > size) return cur;
    else return -1;
}

string func4(const vector<int>& input) {
    int size = input.size();
    if (size % 2 == 0) {
        return to_string(input[size / 2 - 1]) + " " + to_string(input[size / 2]);
    }
    else {
        return to_string(input[size / 2]);
    }
}

vector<int> func5(const vector<int>& input) {
    vector<int> res;
    for (int i = 0; i < input.size(); ++i) {
        if (input[i] >= 100 && input[i] <= 999) {
            res.push_back(input[i]);
        }
        else if (input[i] > 999) break;
    }
    return res;
}

int main() {
    int n, t, a;
    cin >> n >> t;
    vector<int> input;

    for (int i = 0; i < n; ++i) {
        cin >> a;
        input.push_back(a);
    }
    sort(input.begin(), input.end());
    switch (t) {
        case 1:
            if (func1(input)) cout << "Yes\n";
            else cout << "No\n";
            break;
        case 2:
            if (func2(input)) cout << "Unique\n";
            else cout << "Contains duplicate\n";
            break;
        case 3:
            cout << func3(input) << "\n";
            break;
        case 4:
            cout << func4(input) << "\n";
            break;
        case 5:
            print(func5(input));
            break;
        default:
            break;
    }

    return 0;
}
