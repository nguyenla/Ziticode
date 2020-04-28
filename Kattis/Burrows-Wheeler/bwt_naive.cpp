#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Rotation {
    int start_pos;

    Rotation(const int index) : start_pos(index) {}
};

struct RotationComparator {
    const string& text;

    RotationComparator(const string& text) : text(text) {}
    bool operator()(const Rotation& lhs, const Rotation& rhs) {
        string left(text.substr(lhs.start_pos) + text.substr(0, lhs.start_pos));
        string right(text.substr(rhs.start_pos) + text.substr(0, rhs.start_pos));

        return left < right;
    }
};

string bw_transform(const string& input) {
    vector<Rotation> rotations;
    for (size_t i = 0; i < input.size(); ++i) {
        rotations.emplace_back(i);
    }

    RotationComparator rotcom(input);
    sort(rotations.begin(), rotations.end(), rotcom);
    stringstream output;
    for (const auto& rot : rotations) { 
        const int index = rot.start_pos == 0 ? input.size() - 1 : rot.start_pos - 1;
        output << input[index];
    }
    return output.str();
}

int main() {
    string line;
    while (getline(cin, line)) {
        cout << bw_transform(line) << "\n";
    }
    return 0;
}
