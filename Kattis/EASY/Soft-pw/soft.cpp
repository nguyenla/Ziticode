#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

bool isDigit(char c) {
    return (c - '0' < 10) && (c - '0' >= 0);
}

bool isUpperCase(char c) {
    return (c - 'A' >= 0) && (c - 'Z' <= 0);
}

bool isLowerCase(char c) {
    return (c - 'a' >= 0) && (c - 'z' <= 0);
}

bool isSoftPW(const string& s, const string& p) {
    if (p == s) {
        return true;
    }
    else if (s.length() == p.length()) {
        for (int i = 0; i < s.length(); ++i) {
            if (isDigit(s[i]) && isDigit(p[i]) && s[i] == p[i]) continue; 
            if (isUpperCase(s[i]) && isLowerCase(p[i]) && p[i] - s[i] == 32) continue;
            if (isUpperCase(p[i]) && isLowerCase(s[i]) && s[i] - p[i] == 32) continue;
            return false;
        }
        return true;
    }
    else if (s.length() == p.length() + 1) {
        int sl = s.length();
        if (s.substr(1) == p && s[0] - '0' < 10) return true;
        if (s.substr(0, sl - 1) == p && s[sl - 1] - '0' < 10) return true;
        return false;
    }
    else return false;
}

int main() {
    string p, s;
    cin >> s >> p;
    if (isSoftPW(s, p)) cout << "Yes\n";
    else cout << "No\n";

    return 0;
}
