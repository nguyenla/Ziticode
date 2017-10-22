#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int numOrders;
    cin >> numOrders;
    string line;
    while (numOrders > 0) {
        getline(cin, line); // get rid of the line after numOrders
        string customer, food;
        map<string, vector<string> > rec;

        for (int i = 0; i < numOrders; ++i) {
            getline(cin, line);
            stringstream oss(line);

            oss >> customer;
            while (oss >> food) {
                if (rec.find(food) != rec.end()) {
                    rec[food].push_back(customer);
                }
                else {
                    vector<string> temp;
                    temp.push_back(customer);
                    rec[food] = temp;
                }
            }
        }
        

        for (map<string, vector<string> >::iterator it = rec.begin();
                it != rec.end(); ++it)
        {
            vector<string> nameList = it->second;
            sort(nameList.begin(), nameList.end());
            cout << it->first << " ";
            for (int i = 0; i < nameList.size() - 1; ++i) {
                cout << nameList.at(i) << " ";
            }
            cout << nameList.at(nameList.size() - 1) << '\n';
        }
        cout << '\n';
        cin >> numOrders;
    }
    return 0;
}
