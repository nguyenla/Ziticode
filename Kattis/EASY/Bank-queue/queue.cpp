#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Customer {
    Customer() : cash(0), time(-1) {}
    Customer(const int c, const int t) : cash(c), time(t) {}

    int cash;
    int time;
};

struct CustomerComparator {
    bool operator()(const Customer& c1, const Customer& c2) {
        if (c1.cash == c2.cash) return c1.time > c2.time;
        return c1.cash > c2.cash;
    }
} customer_comp;

// Helper function to display vector
template <class T>
void print(const vector<T>& input) {
    for (const T& elem : input) {
        cout << elem << " ";
    }
    cout << "\n";
}

int main() {
    int n, t, cash, time;
    vector<Customer> customers;
    cin >> n >> t;

    int max_time = 0;
    for (int i = 0; i < n; ++i) {
        cin >> cash >> time;
        customers.emplace_back(cash, time);
        max_time = max(max_time, time);
    }
    sort(customers.begin(), customers.end(), customer_comp);

    int total_cash = 0;
    vector<Customer> served(max_time + 1);
    for (const auto& cus : customers) {
        // cout << cus.cash << ", " << cus.time << endl;
        int cur_time = min(cus.time, t);
        if (cur_time > t) continue;
        while (cur_time >= 0) {
            if (served[cur_time].time == -1) {
                served[cur_time].cash = cus.cash;
                served[cur_time].time = cus.time;
                total_cash += cus.cash;
                // cout << "Total cash: " << total_cash << endl;
                break;
            }
            else --cur_time;
        }
    }
    cout << total_cash << endl;

    return 0;
}
