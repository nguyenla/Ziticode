#include <algorithm>
#include <complex>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using CD = complex<double>;

template<class T>
void print(const vector<T>& v) {
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }
    cout << "\n";
}

// Fast Fourier Transform
void fft(vector<CD>& pol, bool invert_mode) {
    int n = pol.size(); // degree n should always be even
    if (n == 1) return; // base case

    vector<CD> odd, even;
    for (int i = 0; i < n; ++i) {
        if (i % 2 == 0) even.push_back(pol[i]);
        else odd.push_back(pol[i]);
    }
    fft(odd, invert_mode);
    fft(even, invert_mode);

    CD w(1);
    double angle = M_PI * 2 / n;
    if (invert_mode) angle *= -1;
    CD w_n(cos(angle), sin(angle)); // n_th root of unity

    for (int i = 0; i < n / 2; ++i) {
        pol[i] = even[i] + w * odd[i];
        pol[i + n / 2] = even[i] - w * odd[i];

        if (invert_mode) {
            pol[i] /= 2; // Why?
            pol[i + n/2] /= 2;
        }
        w *= w_n;
    }
}

// Multiply two polynomials using Fast Fourier Transform
vector<long> multiply(const vector<long>& pol_1, const vector<long>& pol_2) {
    vector<CD> p1(pol_1.begin(), pol_1.end());
    vector<CD> p2(pol_2.begin(), pol_2.end());
    // n: min power of 2 that is at least equal to the degree of the product
    int n = 1;
    while (n < p1.size() + p2.size()) {
        n <<= 1;
    }
    p1.resize(n);
    p2.resize(n);

    // Evaluation: transform to point-value representation
    fft(p1, false);
    fft(p2, false);

    // Multiply
    vector<CD> product;
    for (int i = 0; i < n; ++i) {
        product.push_back(p1[i] * p2[i]);
    }

    // Interpolation: transform back to coefficient representation (invert mode)
    fft(product, true);

    vector<long> results;
    for (int i = 0; i < product.size(); ++i) {
        long coef = round(product[i].real());
        results.push_back(coef);
    }
    return results;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int d1, d2;
        string line;
        long num;

        // Read polynomial 1
        cin >> d1;
        getline(cin, line); // throw away
        getline(cin, line);
        stringstream iss1(line);
        vector<long> pol_1;
        for (int j = 0; j <= d1; ++j) {
            iss1 >> num;
            pol_1.push_back(num);
        }

        // Read polynomial 2
        cin >> d2;
        getline(cin, line); // throw away
        getline(cin, line);
        stringstream iss2(line);
        vector<long> pol_2;
        for (int j = 0; j <= d2; ++j) {
            iss2 >> num;
            pol_2.push_back(num);
        }
        
        auto result = multiply(pol_1, pol_2);

        int degree = pol_1.size() + pol_2.size() - 2;
        cout << degree << "\n";
        for (int i = 0; i <= degree; ++i) {
            cout << result[i] << " ";
        }
        cout << "\n";
    }
    

    return 0;
}
