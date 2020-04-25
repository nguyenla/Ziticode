#include <algorithm>
#include <exception>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Trie {
    private:
        map<char, Trie*> d_children;
        char d_label;
        bool d_is_end; // indicate whether this is the last character in a word
        int d_num_words_with_prefix;

    public:
        Trie() : d_label('0'), d_is_end(false), d_num_words_with_prefix(0) {
            map<char, Trie*> d_children;
        }

        ~Trie() {
            for (const auto& child : d_children) {
                delete child.second;
            }
        }

        Trie(const char label) : d_label(label), d_is_end(false), d_num_words_with_prefix(0) {
            map<char, Trie*> d_children;
        }

        Trie& operator = (const Trie& trie_input) {
            d_label                 = trie_input.label();
            d_is_end                = trie_input.isEndOfWord();
            d_num_words_with_prefix = trie_input.numWordsWithPrefix();
            map<char, Trie*> d_children;
            for (const auto& child : trie_input.children()) {
                d_children[child.first] = child.second;
            }
            return *this;
        }

        Trie(const Trie& trie_input) : 
            d_label(trie_input.label()),
            d_is_end(trie_input.isEndOfWord()),
            d_num_words_with_prefix(trie_input.numWordsWithPrefix()) 
        {
            map<char, Trie*> d_children;
            for (const auto& child : trie_input.children()) {
                d_children[child.first] = child.second;
            }
        }

        // Accessor functions
        char label() const {
            return d_label;
        }

        map<char, Trie*> children() const {
            return d_children;
        }

        int numWordsWithPrefix() const {
            return d_num_words_with_prefix;
        }

        bool isEndOfWord() const {
            return d_is_end;
        }

        void setWordEnd() {
            d_is_end = true;
        }

        void insertChild(const char ch) {
            d_children[ch] = new Trie(ch);
        }

        void incrementNumWordsWithPrefix() {
            ++d_num_words_with_prefix;
        }

        Trie* getChild(const char ch) const {
            if (d_children.find(ch) == d_children.end()) {
                return nullptr;
            }
            else {
                return d_children.at(ch);
            }
        }

        void insert(const string& word) {
            Trie* cur = this;
            for (const auto& ch : word) {
                cur->incrementNumWordsWithPrefix();
                if (cur->getChild(ch)== nullptr) {
                    cur->insertChild(ch);
                }
                cur = cur->getChild(ch);
            }
            cur->incrementNumWordsWithPrefix();
            cur->setWordEnd();
        }


        bool find(const string& word) {
            Trie* cur = this;
            for (const auto& ch : word) {
                const auto child = cur->getChild(ch);
                if (child == nullptr) {
                    return false;
                }
                cur = child;
            }
            return cur->isEndOfWord();
        }

        int findNumWordsWithPrefix(const string& word) {
            Trie* cur = this;
            for (const auto& ch : word) {
                // cout << "Checking " << ch << "\n";
                const auto child = cur->getChild(ch);
                if (child == nullptr) {
                    return 0;
                }
                else {
                    cur = child;
                }
            }
            return cur->numWordsWithPrefix();
        }

        // A quick way to visualize the Trie for debugging
        void display() const {
            cout << "\nRoot: " << d_label << ", num_words_with_prefix=" << d_num_words_with_prefix<< "\n";
            if (d_children.size() > 0) {
                cout << "Children: ";
                int count = 1;
                for (const auto& child : d_children) {
                    cout << "(" << count << ", " << child.first << "), ";
                    ++count;
                }

                // Recursively display the children nodes
                for (const auto& child : d_children) {
                    child.second->display();
                }
            }
        }
};

int main() {
    size_t num_inputs;
    cin >> num_inputs;
    Trie trie('0');
    for (size_t i = 0; i < num_inputs; ++i) {
        string word;
        cin >> word;
        cout << trie.findNumWordsWithPrefix(word) << "\n";
        trie.insert(word);
    }
    // trie.display();

    return 0;
}
