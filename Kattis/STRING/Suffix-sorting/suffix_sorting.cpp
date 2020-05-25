#include <algorithm>
#include <exception>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

struct Suffix {
    int start_index;
    int first_rank;
    int second_rank;

    Suffix(const int index) : start_index(index), first_rank(0), second_rank(0) {}

    Suffix(const int index, const int first_rank, const int second_rank) :
        start_index(index), first_rank(first_rank), second_rank(second_rank) {}
};

struct SuffixComparator {
    bool operator()(const Suffix& lhs, const Suffix& rhs) {
        return lhs.first_rank == rhs.first_rank ? lhs.second_rank < rhs.second_rank
            : lhs.first_rank < rhs.first_rank;
    }
};

vector<int> getSuffixArray(const string& input) {
    size_t length = input.length();

    // find smallest character
    char smallest_char = input[0];
    for (size_t i = 1; i < length; ++i) {
        smallest_char = (input.at(i) - smallest_char) < 0 ? input.at(i) : smallest_char;
    }

    vector<Suffix> suffixes;
    for (size_t i = 0; i < length - 1; ++i) {
        suffixes.emplace_back(i, input.at(i) - smallest_char, input.at(i+1) - smallest_char);
    }
    suffixes.emplace_back(length - 1, input.at(length - 1) - smallest_char, -1);

    SuffixComparator suffix_comp;
    sort(suffixes.begin(), suffixes.end(), suffix_comp);

    for (size_t step = 2; step < length; step *= 2) {
        int ranks[length];
        int count = 0;
        for (size_t i = 0; i < length; ++i) {
            if (i == 0) {
                ranks[suffixes[i].start_index] = count;
            }
            else if (suffixes[i].first_rank == suffixes[i-1].first_rank &&
                    suffixes[i].second_rank == suffixes[i-1].second_rank) {
                ranks[suffixes[i].start_index] = count;
            }
            else {
                ranks[suffixes[i].start_index] = ++count;
            }
        }

        // Assign first_rank to the suffixes: 0, 1, 2, ...
        for (size_t i = 0; i < length; ++i) {
            int cur_suffix_start_index = suffixes[i].start_index;
            suffixes[i].first_rank = ranks[cur_suffix_start_index];
            suffixes[i].second_rank = (cur_suffix_start_index  + step) >= length ? -1
                : ranks[cur_suffix_start_index + step];
        }
        sort(suffixes.begin(), suffixes.end(), suffix_comp);
    }

    vector<int> result;
    for (size_t i = 0; i < length; ++i) {
        result.push_back(suffixes[i].start_index);
    }
    return result;
}


// Helper function to display vector
void print(const vector<int>& input) {
    for (const int num : input) {
        cout << num << " ";
    }
    cout << "\n";
}

int main() {
    string input;
    // cin >> input_length;
    while (getline(cin, input)) {
        auto suffix_array = getSuffixArray(input);

        int num_queries, pos;
        cin >> num_queries;
        for (int i = 0; i < num_queries; ++i) {
            cin >> pos;
            cout << suffix_array[pos];
            if (i < num_queries - 1) {
                cout << " ";
            }
        }
        cout << "\n";
        getline(cin, input); // get rid of end of line
    }

    return 0;
}
