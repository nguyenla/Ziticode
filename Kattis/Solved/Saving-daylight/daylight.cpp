#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    string line;
    while (getline(cin, line)) {
        istringstream ss(line);
        string month, date, year, sunrise, sunset;
        ss >> month >> date >> year >> sunrise >> sunset;

        int index = sunrise.find(":");
        int h1 = stoi(sunrise.substr(0, index));
        int m1 = stoi(sunrise.substr(index + 1, 2));

        index = sunset.find(":");
        int h2 = stoi(sunset.substr(0, index));
        int m2 = stoi(sunset.substr(index + 1, 2));

        int h3 = h2 - h1;
        int m3 = m2 - m1;
        if (m3 < 0) {
            m3 += 60;
            --h3;
        }
        cout << month << " " << date << " " << year << " " << h3 << " hours " << m3 << " minutes\n";
    }
    return 0;
}
