#include <algorithm>
#include <bitset>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;


long compute(const long d, const vector<long>& precomputed) {
    string binary = bitset<64>(d - 1).to_string();
    // cout << binary << "\n";
    long res = 8;
    for (int i = 0; i < binary.size() ; ++i) {
        if (binary[binary.size() - 1 - i] == '0') continue;
        res = (res * precomputed[i]) % 1000000007;
    }
    return res;
}

int main() {
    long t, d;
    cin >> t;

    vector<long> precomputed(65);
    precomputed[0] = 9;
    for (int i = 1; i < precomputed.size(); ++i) {
        precomputed[i] = (precomputed[i - 1] * precomputed[i - 1]) % 1000000007;
    }

    for (int i = 0; i < t; ++i) {
        cin >> d;
        cout << compute(d, precomputed) << "\n";
    }
    return 0;
}
