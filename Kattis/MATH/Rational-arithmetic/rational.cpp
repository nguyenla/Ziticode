#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

long gcd(const long& a, const long& b) {
    if (a == 0) return b;
    if (b == 0) return a;
    if (!(a > 0 && b > 0)) return gcd(abs(a), abs(b));
    if (a < b) return gcd(b, a);
    if (b == 1) return 1;
    long remaining = a % b;
    if (remaining == 0) return b;
    return gcd(b, remaining);
}

struct Fraction {
    Fraction() : x(0), y(1) {}

    Fraction(const long& num, const long& den) : x(num), y(den) {}

    Fraction(const Fraction& frac) {
        x = frac.x;
        y = frac.y;
    }

    void simplify() {
        long factor = gcd(x, y);
        x /= factor;
        y /= factor;
        if (y < 0) {
            x *= -1;
            y *= -1;
        }
    }

    Fraction operator+(const Fraction& f) const {
        long sum_x = x * f.y + y * f.x;
        long sum_y = y * f.y;
        Fraction sum(sum_x, sum_y);
        sum.simplify();
        return sum;
    }

    Fraction operator-(const Fraction& f) const {
        Fraction temp(f);
        temp.x *= -1;
        return *this + temp;
    }

    Fraction operator*(const Fraction& f) const {
        Fraction product(x * f.x, y * f.y);
        product.simplify();
        return product;
    }

    Fraction operator/(const Fraction& f) const {
        Fraction quotient(x * f.y, y * f.x);
        quotient.simplify();
        return quotient;
    }

    string toString() const {
        return to_string(x) + " / " + to_string(y);
    }

    long x; // numerator
    long y; // denominator
};

ostream& operator<<(ostream& os, const Fraction& f) {
    os << f.toString();
    return os;
}


int main() {
    int cases;
    cin >> cases;
    long x1, y1, x2, y2;
    char op;
    string line;
    getline(cin, line);

    for (int i = 0; i < cases; ++i) {
        getline(cin, line);
        stringstream iss(line);
        iss >> x1 >> y1 >> op >> x2 >> y2;
        Fraction f1(x1, y1);
        Fraction f2(x2, y2);
        
        switch (op) {
            case '+':
                cout << f1 + f2 << "\n";
                break;
            case '-':
                cout << f1 - f2 << "\n";
                break;
            case '*':
                cout << f1 * f2 << "\n";
                break;
            case '/':
                cout << f1 / f2 << "\n";
                break;
            default:
                break;
        }
    }

    return 0;
}
