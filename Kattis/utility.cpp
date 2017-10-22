#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// trim from end
string rtrim(string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), 
                [] (int ch) { return !std::isspace(ch);}).base(), s.end());
    return s;
}

int main() {
    return 0;
}
