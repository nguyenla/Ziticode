#include <algorithm>
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

struct StringComp {
    bool operator()(const string& s1, const string& s2) {
        string x(s1), y(s2);
        transform(x.begin(), x.end(), x.begin(), ::tolower);
        transform(y.begin(), y.end(), y.begin(), ::tolower);
        return x < y;
    }
} string_comp;

int main() {
    int r, c;
    string line;
    cin >> r >> c;
    getline(cin, line); // throw away
    while (r != 0 || c != 0) {
        vector<string> input;
        for (int i = 0; i < r; ++i) {
            getline(cin, line);
            input.push_back(line);
        }

        vector<string> vertical;
        for (int j = 0; j < c; ++j) {
            string temp;
            for (int i = 0; i < r; ++i) {
                temp += input[i][j];
            }
            vertical.push_back(temp);
        }
        stable_sort(vertical.begin(), vertical.end(), string_comp);

        // Form output
        vector<string> output;
        for (int i = 0; i < r; ++i) {
            string temp;
            for (int j = 0; j < c; ++j) {
                temp += vertical[j][i];
            }
            cout << temp << endl;
        }

        cin >> r >> c;
        getline(cin, line); // throw away
        if (r != 0 || c != 0) cout << endl;
    }
    return 0;
}
