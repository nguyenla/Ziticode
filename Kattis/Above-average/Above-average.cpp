#include <algorithm>
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    int num_input;

    cin >> num_input;

    while (num_input != 0) {
        int num_students = 0;
        double sum_score = 0;

        cin >> num_students;
        int score[num_students];

        for (int i = 0; i < num_students; ++i) {
            cin >> score[i];
            sum_score += score[i];
        }

        double above_ave = 0;
        const double average = sum_score / num_students;
        for (int j = 0; j < num_students; ++j) {
            if (score[j] > average) above_ave += 1;
        }

        cout << setprecision(3) << fixed << 100 * above_ave / num_students  << "%\n";
        --num_input;
    }

    return 0;
}
