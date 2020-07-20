#include <algorithm>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const long MAX_INT = 1000000000;

// Mulitply mat1 by mat2, and store the product in mat1
void multiply(long mat1[2][2], long mat2[2][2]) {
    long a = (mat1[0][0] * mat2[0][0] + mat1[0][1] * mat2[1][0]) % MAX_INT;
    long b = (mat1[0][0] * mat2[0][1] + mat1[0][1] * mat2[1][1]) % MAX_INT;
    long c = (mat1[1][0] * mat2[0][0] + mat1[1][1] * mat2[1][0]) % MAX_INT;
    long d = (mat1[1][0] * mat2[0][1] + mat1[1][1] * mat2[1][1]) % MAX_INT;
    mat1[0][0] = a;
    mat1[0][1] = b;
    mat1[1][0] = c;
    mat1[1][1] = d;
}

void power(long mat[2][2], long n) {
    if (n <= 1) return;

    long temp[2][2];
    temp[0][0] = mat[0][0];
    temp[0][1] = mat[0][1];
    temp[1][0] = mat[1][0];
    temp[1][1] = mat[1][1];

    power(mat, n / 2);
    multiply(mat, mat);
    if (n % 2 != 0) {
        multiply(mat, temp);
    }
}

long fibonacci(const long n) {
    if (n == 0) return 0;
    else if (n == 1) return 1;

    long mat[2][2] = {{1, 1}, {1, 0}};
    power(mat, n - 1);
    return mat[0][0];
}

int main() {
    int n, k;
    long x;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> k >> x;
        cout << k << " " << fibonacci(x) << endl;
    }

    return 0;
}
