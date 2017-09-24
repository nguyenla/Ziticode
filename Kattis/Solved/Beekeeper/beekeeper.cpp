#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int count_double_vowels(const string& word)
{
    char vowel_array[] = {'a', 'e', 'i', 'o', 'u', 'y'};
    set<char> vowels(vowel_array, vowel_array + 6);
    
    int count = 0;
    for (int i = 0; i < word.length() - 1; ++i) {
        if (vowels.find(word[i]) != vowels.end() && word[i+1] == word[i]) {
            ++count;
            ++i;
        }
    }
    return count;
}

string get_word_with_most_double_vowels(const vector<string>& words)
{
    int max = 0;
    string word = words[0];
    for (int i = 0; i < words.size(); ++i) {
        int count = count_double_vowels(words[i]);
        if (max < count) {
            max = count;
            word = words[i];
        }
    }
    return word;
}

int main() {
    int n;
    cin >> n;
    while (n > 0) {
        vector<string> words;
        string word;
        for (int i = 0; i < n; ++i) {
            cin >> word;
            words.push_back(word);
        }
        cout << get_word_with_most_double_vowels(words) << '\n';
        cin >> n;
    }
    return 0;
}
