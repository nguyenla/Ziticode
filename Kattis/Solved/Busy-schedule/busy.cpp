#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Time {
    int hour_;
    int min_;
    bool isAM_;

    Time(int hour, int minute, int isAM) :
        hour_(hour), min_(minute), isAM_(isAM) {}

};

ostream& operator<< (ostream& out, const Time& time) {
    out << time.hour_ << ":";
    if (time.min_ < 10) out << "0";
    out << time.min_ << " ";
    if (time.isAM_) out << "a.m.";
    else out << "p.m.";
    return out;
}

struct Comparator {
    bool operator() (const Time& a, const Time& b) {
        if (a.isAM_ && !b.isAM_) return true;
        if (!a.isAM_ && b.isAM_) return false;

        if (a.hour_ == 12 && b.hour_ != 12) return true;
        if (b.hour_ == 12 && a.hour_ != 12) return false;
        if (a.hour_ == 12 && b.hour_ == 12) return a.min_ < b.min_;

        if (a.hour_ < b.hour_) return true;
        if (a.hour_ > b.hour_) return false;
        return a.min_ < b.min_;
    }
};


int main() {
    int n;
    cin >> n;
    while (n != 0) {
        string time;
        getline(cin, time);
        vector<Time> schedule;
        for (int i = 0; i < n; ++i) {
            getline(cin, time);
            int colon = time.find(':');
            int space = time.find(' ');
            int hour = stoi(time.substr(0, colon));
            int min = stoi(time.substr(colon + 1, 2));
            bool am = time[space + 1] == 'a' ? true : false;
            Time input(hour, min, am);
            schedule.push_back(input);
        }
        Comparator comp;
        sort(schedule.begin(), schedule.end(), comp);
        
        for (int i = 0; i < n; ++i) {
            cout << schedule[i] << '\n';
        }
        cin >> n;
        if (n != 0) cout << '\n';
    }
    return 0;
}
