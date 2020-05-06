#include <algorithm>
#include <exception>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

// For Suffix Array construction
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

// For Suffix Tree construction
struct SuffixTreeNode {
    int depth;
    int start_index;
    int end_index;
    map<char, SuffixTreeNode*> children;
    SuffixTreeNode* parent;

    SuffixTreeNode() {}

    SuffixTreeNode(const int depth, const int start, const int end) :
        depth(depth), start_index(start), end_index(end) {}

    ~SuffixTreeNode() {
        for (auto item : children) {
            delete item.second;
        }
        parent = NULL;
    }

    SuffixTreeNode* createChild(const string& input, const int depth, const int start, const int end) {
        SuffixTreeNode* new_node = new SuffixTreeNode(depth, start, end);
        new_node->parent = this;
        this->children[input[start]] = new_node;
        return new_node;
    }

    SuffixTreeNode* breakEdge(const string& input, const int suffix, const int offset) {
        char first_char = input[this->depth + suffix];
        SuffixTreeNode* prev_node = this->children[first_char];

        // Create new middle node and link with current node
        SuffixTreeNode* mid_node = new SuffixTreeNode();
        mid_node->depth = this->depth + offset;
        mid_node->start_index = this->depth + suffix;
        mid_node->end_index = mid_node->start_index + offset - 1;
        mid_node->parent = this;
        this->children[first_char] = mid_node;

        // Update prev node
        prev_node->start_index = prev_node->start_index + offset;
        prev_node->parent = mid_node;
        mid_node->children[input[prev_node->start_index]] = prev_node;

        // Create new child node 
        SuffixTreeNode* new_node = new SuffixTreeNode();
        new_node->start_index = mid_node->end_index + 1;
        new_node->end_index = input.size() - 1;
        new_node->depth = mid_node->depth + new_node->end_index - new_node->start_index + 1;
        new_node->parent = mid_node;
        mid_node->children[input[new_node->start_index]] = new_node;

        return new_node;
    }

    int findLongestRepeatedSubstringLength() {
        int max_length = 0;
        if (this->children.size() == 0) {
            return max_length;
        }
        else {
            for (const auto& child : children) {
                max_length = max(max_length, child.second->findLongestRepeatedSubstringLength());
            }
            return max(max_length, this->depth);
        }
    }

    void printNode() {
        cout << "depth=" << this->depth << ", start=" << this->start_index << ", end=" << this->end_index << "\n";
    }

    void print(const string& input) {
        cout << "----------BEGIN TREE---------------------[\n";
        printNode();
        for (const auto& child : children) {
            cout << "Child corresponding to path " 
                 << input.substr(child.second->start_index, child.second->end_index + 1) << "\n";
            child.second->print(input);
        }
        cout << "]----------END TREE----------------------\n";
    }
};

// Helper function to display vector
void print(const vector<int>& input) {
    for (const int num : input) {
        cout << num << " ";
    }
    cout << "\n";
}

// Build Suffix Array for a string
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


// Helper function to find vector `result`, with result[input[i]] = i
vector<int> inverseArray(const vector<int>& input) {
    vector<int> result(input.size(), 0);
    for (int i = 0; i < input.size(); ++i) {
        result[input[i]] = i;
    }
    return result;
}

int findLCPOfSuffixes(const string& input, const int s1, const int s2, const int equal) {
    int lcp = max(0, equal);
    while (s1 + lcp < input.size() && s2 + lcp < input.size()) {
        if (input[s1 + lcp] == input[s2 + lcp])
            ++lcp;
        else
            break;
    }
    return lcp;
}

vector<int> computeLCPArray(const string& input, const vector<int>& suffix_array) {
    vector<int> lcp_array(input.size() - 1, 0);
    int lcp = 0;
    auto inverse_suffix = inverseArray(suffix_array);
    int cur_suffix = 0;

    for (int i = 0; i < input.size(); ++i) {
        // Position of the suffix beginning at this index in the suffix array
        int pos_in_sa = inverse_suffix[i]; 
        if (pos_in_sa == input.size() - 1) {
            lcp = 0;
            cur_suffix = (cur_suffix + 1) % input.size();
            continue;
        }
        // Advance to the next suffix in the suffix array
        int next_suffix = suffix_array[pos_in_sa + 1];
        lcp = findLCPOfSuffixes(input, cur_suffix, next_suffix, lcp - 1);
        lcp_array[pos_in_sa] = lcp;
        cur_suffix = (cur_suffix + 1) % input.size();
    }

    return lcp_array;
}

SuffixTreeNode* constructSuffixTree(const string& input) {
    using SFTN = SuffixTreeNode;
    int last_index = input.size() - 1;
    auto suffix_array = getSuffixArray(input);
    auto lcp_array = computeLCPArray(input, suffix_array);
    SFTN* root = new SFTN(0, -1, -1);

    // First node is formed from the first suffix, depth = 1
    SFTN* first_node = new SFTN(input.size() - suffix_array[0], suffix_array[0], last_index);
    first_node->parent = root;
    root->children[input[suffix_array[0]]] = first_node;

    // Iterate through the rest of suffix_array and lcp_array
    SFTN* cur_node = first_node;
    for (int i = 1; i < suffix_array.size(); ++i) { 
        int cur_lcp = lcp_array[i - 1];
        int cur_suffix = suffix_array[i];

        // Traverse up to the first node with depth <= lcp_array[i]
        while (cur_node->depth > cur_lcp) {
            cur_node = cur_node->parent;
        }

        if (cur_node->depth == cur_lcp) {
            // Simple case: create a new leaf
            SFTN* new_node = cur_node->createChild(input,
                    (last_index - cur_suffix + 1),
                    cur_node->depth + cur_suffix, last_index);
        }
        else {
            // Break the edge if there exists one
            cur_node = cur_node->breakEdge(input, cur_suffix, cur_lcp - cur_node->depth);
        }
    }

    return root;
}

int main() {
    int input_length;
    string input;
    cin >> input_length;
    while (cin >> input) {
        /*
        auto suffix_array = getSuffixArray(input);
        cout << "Suffix array of input: " << input << " is: \n";
        for (int i = 0; i < suffix_array.size(); ++i) {
            cout << input.substr(suffix_array[i]) << "\n";
        }
        cout << "---------------------------\n";

        auto lcp_array = computeLCPArray(input, suffix_array);
        cout << "LCP Array of input: " << input << " is: \n";
        print(lcp_array);
        cout << "----------------------------------------------------------\n";

        auto suffix_tree = constructSuffixTree(input);
        suffix_tree->print(input);
        */
        auto suffix_tree = constructSuffixTree(input);
        cout << suffix_tree->findLongestRepeatedSubstringLength() << "\n";

        cin >> input_length;
    }

    return 0;
}
