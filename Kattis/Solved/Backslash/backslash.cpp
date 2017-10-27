#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string escape(const string& input) {
    string res("");
    for (int i = 0 ; i < input.length(); ++i) {
        char c = input[i];
        if ((c >= '!' && c <= '*') || ( c >= '[' && c <= ']')) {
            res = res + "\\";
        }
        res = res + c;
    }
    return res;
}

int main() {
    int num;
    string line;

    while (cin >> num) {
        getline(cin, line); // thrown away
        getline(cin, line);
        for (int i = 0; i < num; ++i) {
            line = escape(line);
        }
        cout << line << '\n';
    }
    return 0;
}
