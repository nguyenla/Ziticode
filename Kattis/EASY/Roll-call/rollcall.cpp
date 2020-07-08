#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct Name {
    Name() {}
    Name(const string& first, const string& last) : first(first), last(last) {}

    string first, last;
};

struct NameComp {
    bool operator()(const Name& name1, const Name& name2) {
        if (name1.last == name2.last) return name1.first < name2.first;
        return name1.last < name2.last;
    }
} name_comp;

// Helper function to display vector
template <class T>
void print(const vector<T>& input) {
    for (const T& elem : input) {
        cout << elem << " ";
    }
    cout << "\n";
}

int main() {
    vector<Name> names;
    unordered_map<string, int> first_names;
    string first, last;
    while (cin >> first >> last) {
        names.emplace_back(first, last);
        if (first_names.find(first) == first_names.end()) {
            first_names[first] = 1;
        }
        else {
            first_names[first] = first_names[first] + 1;
        }
    }
    sort(names.begin(), names.end(), name_comp);
    for (int i = 0; i < names.size(); ++i) {
        if (first_names[names[i].first] > 1) {
            cout << names[i].first << " " << names[i].last << endl;
        }
        else {
            cout << names[i].first << endl;
        }
    }
    return 0;
}
