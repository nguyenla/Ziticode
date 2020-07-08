#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
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

int main() {
    int n;
    string newfile;
    cin >> n;

    while (n != 0) {
        getline(cin, newfile); // throw away
        unordered_set<string> unique_files;
        vector<string> files;
        vector<char> hashes;
        for (int i = 0; i < n; ++i) {
            getline(cin, newfile);
            unique_files.insert(newfile);
            files.push_back(newfile);

            // XOR bytes
            char res = newfile[0];
            for (int i = 1; i < newfile.size(); ++i) {
                res ^= newfile[i];
            }
            hashes.push_back(res);
        }

        int num_collisions = 0;
        for (int i = 0; i < n - 1; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (hashes[i] == hashes[j] && files[i] != files[j]) ++num_collisions;
            }
        }
        cout << unique_files.size() << " " << num_collisions << endl;

        cin >> n;
    }
    return 0;
}
