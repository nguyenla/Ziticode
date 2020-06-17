#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int high = 1000000;
    int low = 1;
    string s;
    
    while (low <= high) {
        int mid = (high + low) / 2;
        cout << mid << "\n";
        cin >> s;
        if (s == "correct") break;
        else if (s == "lower") high = mid - 1;
        else if (s == "higher") low = mid + 1;
        else cout << "Please input either 'higher', 'lower', or 'correct'\n";
    }


    return 0;
}
