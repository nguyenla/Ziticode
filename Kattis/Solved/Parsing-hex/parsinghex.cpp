#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

long convert(const string& hex) {
    string num = hex.substr(2);
    long res = 0;
    for (int i = 0; i < num.length(); ++i) {
        if (num[i] >= '0' && num[i] <= '9') {
            res = res * 16 + (num[i] - '0');
        }
        else if (num[i] >= 'a' && num[i] <= 'f') {
            res = res * 16 + 10 + (num[i] - 'a');
        }
        else {
            res = res * 16 + 10 + (num[i] - 'A');
        }
    }
    return res;
}

void process(const string& input) {
    int index = input.find("0");
    while (index != string::npos) {
        if (index >= input.length() - 1) return;
        if (!(input[index + 1] == 'x' || input[index + 1] == 'X')) {
            index = input.find("0", index + 1);
            continue;
        }

        int i = index + 2;
        while (i < input.length() && i < index + 10) {
            char c = input[i];
            if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')) {
                ++i;
            }
            else break;
        }
        if (i != index + 2) {
            string hex = input.substr(index, i - index);
            cout << hex << " " << convert(hex) << '\n';
        }
        index = input.find("0", index + 1);
    }
}

int main() {
    string line;
    while (getline(cin, line)) {
        process(line);
    }
    return 0;
}
