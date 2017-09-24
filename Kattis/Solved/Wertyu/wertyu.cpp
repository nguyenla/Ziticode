#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string shiftleft(const string& line)
{
    string row1("`1234567890-=");
    string row2("QWERTYUIOP[]\\");
    string row3("ASDFGHJKL;'");
    string row4("ZXCVBNM,./");
    ostringstream output;

    for (int i = 0; i < line.length(); ++i) {
        if (line[i] == ' ') {
            output << " ";
        }
        else {
            int pos = row1.find(line[i]);
            if (pos != string::npos) {
                output << row1[pos-1];
            }

            pos = row2.find(line[i]);
            if (pos != string::npos) {
                output << row2[pos-1];
            }

            pos = row3.find(line[i]);
            if (pos != string::npos) {
                output << row3[pos-1];
            }

            pos = row4.find(line[i]);
            if (pos != string::npos) {
                output << row4[pos-1];
            }
        }
    }
    return output.str();
}

int main() {
    string line;
    while (getline(cin, line)) {
        cout << shiftleft(line) << '\n';
    }
    return 0;
}
