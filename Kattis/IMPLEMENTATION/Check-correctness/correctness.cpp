#include <algorithm>
#include <bitset>
#include <iostream>
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

long long solve(long long a, long long b, char op) {
    if (op == '+') return ((a % 100000) + (b % 10000)) % 10000;
    else if (op == '*') return ((a % 100000) * (b % 10000)) % 10000;

    // op == '^'
    string bin = bitset<33>(b).to_string();
    vector<int> powers;
    powers.push_back(1);
    powers.push_back(a % 10000);
    for (int i = 2; i <= 33; ++i) {
        powers.push_back((powers[i - 1] * powers[i - 1]) % 10000);
    }

    int res = 1;
    for (int i = 0; i < bin.length(); ++i) {
        int pos = bin.length() - 1 - i;
        if (bin[pos] == '1') {
            // cout << pos << " " << powers[i + 1] << endl;
            res = (powers[i + 1] * res) % 10000;
        }
    }
    
    return res;
}

int main() {
    string line;
    long long a, b;
    char op;

    while (getline(cin, line)) {
        istringstream iss(line);
        iss >> a >> op >> b;
        // cout << a << " " << op << " " << b << endl;
        cout << solve(a, b, op) << endl;
    }
    return 0;
}
