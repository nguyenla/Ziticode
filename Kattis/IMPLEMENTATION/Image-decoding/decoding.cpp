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

vector<string> convertToImage(const vector<string>& input) {
    vector<string> res;
    char cur;
    int x;

    int num_char = -1;
    bool is_valid = true;
    for (int i = 0; i < input.size(); ++i) {
        istringstream iss(input[i]);
        string line = "";
        int total = 0;
        iss >> cur;
        while (iss >> x) {
            total += x;
            for (int j = 0; j < x; ++j) {
                line += cur;
            }
            cur = cur == '#' ? '.' : '#';
        }
        if (i == 0) num_char = total;
        else {
            if (total != num_char) is_valid = false;
        }
        res.push_back(line);
    }
    if (!is_valid) res.push_back("Error decoding image");

    return res;
}

int main() {
    int n;
    string line;
    cin >> n;
    getline(cin, line); // throw away


    while (n != 0) {
        vector<string> input;
        for (int i = 0; i < n; ++i) { 
            getline(cin, line);
            input.push_back(line);
        }

        auto output = convertToImage(input);
        for (int i = 0; i < output.size(); ++i) {
            cout << output[i] << endl;
        }

        cin >> n;
        getline(cin, line); // throw away
        if (n != 0) cout << endl;
    }
    return 0;
}
