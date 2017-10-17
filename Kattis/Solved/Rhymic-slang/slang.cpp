#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool end_with(const string& word, const string& suffix) {
    if (word.size() < suffix.size()) {
        return false;
    }
    return word.substr(word.size() - suffix.size(), suffix.size()) == suffix;
}

void split_by_space(vector<string> *res, const string& line) {
    istringstream iss(line);
    string word;
    while (iss >> word) {
        res->push_back(word);
    }
}

int main() {
    string common_word;
    cin >> common_word;

    int num_lists;
    cin >> num_lists;

    string line;
    getline(cin, line);

    vector<vector<string> > lists;
    // read in all the lists of rhymes that are relevant to the common word
    for (int i = 0; i < num_lists; ++i) {
        getline(cin, line);
        vector<string> list;
        split_by_space(&list, line);
        bool contains = false;
        for (int j = 0; j < list.size(); ++j) {
            if (end_with(common_word, list[j])) {
                contains = true;
                break;
            }
        }

        if (contains) {
            lists.push_back(list);
        }
    }

    // check the phrases that follow
    int num_phrases;
    cin >> num_phrases;
    getline(cin, line); // get rid of the current line
    for (int i = 0; i < num_phrases; ++i) {
        getline(cin, line);
        bool match = false;
        for (int j = 0; j < lists.size(); ++j) {
            vector<string> cur = lists.at(j);
            for (int k = 0; k < cur.size(); ++k) {
                if (end_with(line, cur.at(k))) {
                    match = true;
                }
            }
        }
        if (match) {
            cout << "YES\n";
        }
        else {
            cout << "NO\n";
        }
    }


    return 0;
}
