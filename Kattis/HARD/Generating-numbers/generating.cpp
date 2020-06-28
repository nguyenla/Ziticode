#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
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

int getMaxPermutation(const int n) {
    string s = to_string(n);
    sort(s.begin(), s.end(), greater<char>());
    return stoi(s);
}

int solve(const int n, unordered_map<int, int>& mp) {
    if (mp.find(n) != mp.end()) return mp[n];
    if (n <= 9) {
        mp[n] = n - 1;
        return mp[n];
    }
    int n_length = to_string(n).size();
    int start = 9;
    int count = 8;

    // First: find the number of operations to reach 100..00
    while (to_string(start).size() < n_length) {
        while (start % 10 != 9) {
            mp[++start] = ++count;
            if (mp.find(n) != mp.end()) return mp[n];
        }
        int max_perm = getMaxPermutation(start);
        if (start == max_perm) {
            mp[++start] = ++count;
            if (mp.find(n) != mp.end()) return mp[n];
        }
        else {
            start = max_perm;
            mp[start] = ++count;
            if (mp.find(n) != mp.end()) return mp[n];
        }
    }
    
    string n_string = to_string(n);
    int num_zeros = 0;
    int num_ones = 0;
    int sum = 0;

    // Count number of 0's, 1's, and the number of increments required
    for (int i = 0; i < n_length; ++i) {
        if (n_string[i] == '1') ++num_ones;
        else if (n_string[i] == '0') ++num_zeros;

        if (i == 0) sum = sum + (n_string[i] - '1');
        else sum = sum + (n_string[i] - '0');
    }

    // Case 1: All 0's except first digit
    if (num_zeros == n_length - 1) {
        if (mp.find(n) != mp.end()) {
            return mp[n];
        }
        return solve(n - 1, mp) + 1;
    }
    // Case 2: No 0's and no 1's
    else if (num_zeros == 0 && num_ones == 0) {
        mp[n] = count + sum + (n_length - 1);
    }
    // Case 3: There are 1's but no 0's
    else if (num_zeros == 0 && num_ones > 0) {
        if (n_string[0] == '1') {
            mp[n] = count + sum - 1 + (n_length - 1);
        }
        else {
            count = count + sum + (n_length - 1);
            // One fewer swap if the last digit is not 1
            if (num_ones > 1 || n_string[n_length - 1] != '1') --count;
            mp[n] = count;
        }
    }
    // Case 4: There are 0's and no 1's
    else if (num_zeros > 0 && num_ones == 0) {
        if (n_string[n_length - 1] != '0') {
            // Need `sum` increments, and (n_length - num_zeros - 1) swaps
            mp[n] = count + sum + (n_length - num_zeros - 1);
        }
        else {
            // One more swap that the case above
            mp[n] = count + sum + (n_length - num_zeros);
        }
    }
    // Case 5: There are both 0's and 1's
    else {
        if ((n_string[n_length - 1] == '0') || (n_string[n_length - 1] == '1' && num_ones == 1)) {
            // Need `sum` increments, and (n_length - num_zeros - 1) swaps
            mp[n] = count + sum + (n_length - num_zeros - 1);
        }
        else {
            // One fewer swap that the case above
            mp[n] = count + sum + (n_length - num_zeros - 2);
        }
    }
    return mp[n];
}

int main() {
    int cases, n;
    cin >> cases;

    // Store number of ops to get to a number n
    unordered_map<int, int> mp;

    for (int i = 0; i < cases; ++i) {
        cin >> n;
        int res = solve(n, mp);
        cout << res << endl;
    }

    return 0;
}
