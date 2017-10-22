#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


// trim from end
string rtrim(string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), 
                [] (int ch) { return !std::isspace(ch);}).base(), s.end());
    return s;
}

void print_rotate(const vector<string>& figure, int maxLength)
{
    int fsize = figure.size();
    char matrix[maxLength][fsize];
    int a = 0;
    int b = 0;
    for (int i = 0; i < maxLength; ++i) {
        for (int j = figure.size() - 1; j >= 0; --j) {
            if (i >= figure[j].length()) {
                matrix[a][b] = ' ';
            }
            else if (figure[j][i] == ' ') {
                matrix[a][b] = ' ';
            }
            else if (figure[j][i] == '+') {
                matrix[a][b] = '+';
            }
            else if (figure[j][i] == '-') {
                matrix[a][b] = '|';
            }
            else if (figure[j][i] == '|') {
                matrix[a][b] = '-';
            }
            ++b;
        }
        b = 0;
        ++a;
    }

    for (int i = 0; i < maxLength; ++i) {
        string temp;
        for (int j = 0; j < fsize; ++j) {
            temp += matrix[i][j];
        }
        cout << rtrim(temp) << '\n';
    }
}

int main() {
    int numLines;
    cin >> numLines;
    while (numLines > 0) {
        string line;
        getline(cin, line); // ignore till end of line

        vector<string> figure;
        int maxLength = 0;

        for (int i = 0; i < numLines; ++i) {
            getline(cin, line);
            figure.push_back(line);
            maxLength = maxLength < line.length() ? line.length() : maxLength;
        }
        print_rotate(figure, maxLength);
        cin >> numLines;
        if (numLines > 0) {
            cout << '\n';
        }
    }

    return 0;
}

