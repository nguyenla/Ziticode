#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string getFoxSound(const string& recording, const map<string, string>& mp)
{
    istringstream rec(recording);
    ostringstream output;

    string sound;
    while (rec >> sound) {
        map<string, string>::const_iterator it = mp.find(sound);
        if (it == mp.end()) {
            output << sound << " ";
        }
    }
    return output.str();
}

int main() 
{
    int n;
    cin >> n;
    string line;
    getline(cin, line); // throw away the rest of the line
    
    for (size_t i = 0; i != n; ++i) {
        string recording;
        getline(cin, recording);
        map<string, string> mp;
        string animal, sound;
        while (cin >> animal) {
            if (animal == "what") {
                getline(cin, line); // throw away the rest of the question
                // print out the fox's sounds
                cout << getFoxSound(recording, mp) << '\n';
                break;
            }
            else {
                cin >> line >> sound;
                mp[sound] = animal;
            }
        }
    }
    return 0;
}
