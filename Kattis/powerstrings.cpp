#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool is_unit(const string& small, const string& big) {
    // cout << big.length() << " : " << small.length() << '\n';
    int blen = big.length();
    int slen = small.length();

    for (size_t i = 0; i < slen; ++i) {
        for (size_t j = i + slen; j < blen; j += slen) {
            // cout << big[j] << " : " << small[i] << '\n';
            if (big[j] != small[i]) return false;
        }
    }
    return true;
}

int find_max_power(const string& input) {
    int n;
    int start_pos = 1;
    while ((n = input.find(input[0], start_pos)) != string::npos) {
        if (input.length() % n != 0) {
            start_pos = n + 1;
            continue;
        }
        string unit = input.substr(0, n);
        if (is_unit(unit, input)) { 
            return input.length() / unit.length();
        }

        start_pos = n + 1;
    }

    return 1;
}


int main() {
    string input;
    cin >> input;
    while (input != ".") {
        int max_power = find_max_power(input);
        cout << max_power << '\n';
        cin >> input;
    }
    return 0;
}
