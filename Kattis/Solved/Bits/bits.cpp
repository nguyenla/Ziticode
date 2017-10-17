#include <bitset>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string int_to_binary(int n) {
    if (n == 0) return "0";
    const string result = bitset<32>(n).to_string();
    return result.substr(result.find("1",0));
}

int count_ones(const string& input) {
    int count = 0;
    for (int i = 0; i < input.size(); ++i) {
        if (input[i] == '1') {
            ++count;
        }
    }
    return count;
}


int main() {
    int num_cases;
    string num;
    cin >> num_cases;

    for (int i = 0; i < num_cases; ++i) {
        cin >> num;
        int max_ones = 0;
        for (int j = 1; j <= num.size(); ++j) {
            int num_ones = count_ones(int_to_binary(stoi(num.substr(0, j))));
            max_ones = (num_ones > max_ones) ? num_ones : max_ones;
        }
        cout << max_ones << '\n';
    }
    return 0;
}
