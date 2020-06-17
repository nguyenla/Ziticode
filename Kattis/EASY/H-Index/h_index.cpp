#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Helper function to display vector
void print(const vector<int>& input) {
    for (const int num : input) {
        cout << num << " ";
    }
    cout << "\n";
}

int h_index(const vector<int>& papers) {
    int n = papers.size();
    vector<int> count(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        if (papers[i] > n) ++count[n];
        else ++count[papers[i]];
    }

    int h_index = 0;

    for (int i = n; i >= 0; --i) {
        h_index += count[i];
        if (h_index >=i) return i;
    }
    return 0;
}

int main() {
    int num_papers, p;
    cin >> num_papers;
    vector<int> papers;
    for (int i = 0; i < num_papers; ++i) {
        cin >> p;
        papers.push_back(p);
    }
    sort(papers.begin(), papers.end());
    cout << h_index(papers) << "\n";
    return 0;
}
