#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    string line;
    char vowels[] = {'a', 'e', 'i', 'o', 'u'};
    getline(cin, line);
    
   
    for (size_t i = 0; i != line.length(); ++i) {
        if (find(begin(vowels), end(vowels), line[i]) != end(vowels)) {
            line.replace(i+1, 2, "");
        }
    }
    cout << line << '\n';
    return 0;
}
