#include <algorithm>
#include <exception>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
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

// Display a vector of suffixes
void print(const vector<Suffix>& suffixes) {
    for (size_t i = 0; i < suffixes.size(); ++i) {
        cout << suffixes[i].start_index << " " << suffixes[i].first_rank << " " << suffixes[i].second_rank << "\n";
    }
    cout << "\n";
}

// Construct the suffix array for the given input
vector<int> getSuffixArray(const string& input) {
    size_t length = input.length();

    // Find smallest character
    char smallest_char = input[0];
    for (size_t i = 1; i < length; ++i) {
        smallest_char = (input.at(i) - smallest_char) < 0 ? input.at(i) : smallest_char;
    }

    // Vector of suffixes, with the ranks of the first two characters
    vector<Suffix> suffixes;
    for (size_t i = 0; i < length - 1; ++i) {
        suffixes.emplace_back(i, input.at(i) - smallest_char, input.at(i+1) - smallest_char);
    }
    suffixes.emplace_back(length - 1, input.at(length - 1) - smallest_char, -1);

    // Initial rank of suffixes based on only two first letters
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

// Find Burrows-Wheeler transformation of a string using suffix arrays
string find_bwt(const string& raw_input) {
    // This appending step is critical for the correctness of the algorithm
    // Otherwise, it will produce false output for "magna", "standard"
    string input(raw_input + raw_input);
    int length = raw_input.size();
    vector<int> suffix_array = getSuffixArray(input);

    // Ignore the indices >= raw input length
    stringstream result;
    for (int i = 0; i < suffix_array.size(); ++i) {
        if (suffix_array[i] == 0) {
            result << raw_input.at(length - 1);
        }
        else if (suffix_array[i] < length) {
            result << raw_input.at(suffix_array[i] - 1);
        }
    }
    return result.str();
}

int main() {
    string input;
    while (getline(cin, input)) {
        cout << find_bwt(input) << "\n";
    }
    return 0;
}
