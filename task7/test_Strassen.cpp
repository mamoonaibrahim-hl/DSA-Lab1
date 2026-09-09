#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Strassen.h"
using namespace std;

void printMatrix(const Matrix& M) {
    for (auto& row : M) {
        for (int val : row) cout << val << " ";
        cout << endl;
    }
}

Matrix randomMatrix(int n) {
    Matrix M(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            M[i][j] = rand() % 10;      // small random values, easy to eyeball
    return M;
}

int main() {
    srand((unsigned)time(0));

    // Test 1: 2x2 matrix multiplication
    Matrix A2 = {{1, 2}, {3, 4}};
    Matrix B2 = {{5, 6}, {7, 8}};
    Matrix strassenResult2 = strassenMultiply(A2, B2);
    Matrix standardResult2 = standardMultiply(A2, B2);
    cout << "Test 1 (2x2): " << (strassenResult2 == standardResult2 ? "PASS" : "FAIL") << endl;
    printMatrix(strassenResult2);
    cout << endl;

    // Test 2: 4x4 matrix multiplication
    Matrix A4 = {{1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16}};
    Matrix B4 = {{16,15,14,13}, {12,11,10,9}, {8,7,6,5}, {4,3,2,1}};
    Matrix strassenResult4 = strassenMultiply(A4, B4);
    Matrix standardResult4 = standardMultiply(A4, B4);
    cout << "Test 2 (4x4): " << (strassenResult4 == standardResult4 ? "PASS" : "FAIL") << endl;
    printMatrix(strassenResult4);
    cout << endl;

    // Test 3: Random values, compared with naive multiplication
    int n = 8;   // must be power of 2
    Matrix Arand = randomMatrix(n);
    Matrix Brand = randomMatrix(n);
    Matrix strassenResultRand = strassenMultiply(Arand, Brand);
    Matrix standardResultRand = standardMultiply(Arand, Brand);
    cout << "Test 3 (8x8 random): "
         << (strassenResultRand == standardResultRand ? "PASS" : "FAIL") << endl;

    return 0;
}