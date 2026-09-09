#include <vector>
using namespace std;
typedef vector<vector<int>> Matrix;

// Standard O(n^3) matrix multiplication, used for comparison/verification.
Matrix standardMultiply(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}

// Helper: add two matrices
Matrix add(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

// Helper: subtract two matrices
Matrix subtract(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}

// Splits parent matrix into a n/2 x n/2 quadrant, starting at (rowOffset, colOffset)
Matrix getQuadrant(const Matrix& M, int rowOffset, int colOffset, int size) {
    Matrix Q(size, vector<int>(size));
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            Q[i][j] = M[i + rowOffset][j + colOffset];
    return Q;
}

// Combines 4 quadrants back into one matrix of size 2*size
Matrix combine(const Matrix& C11, const Matrix& C12, const Matrix& C21, const Matrix& C22) {
    int size = C11.size();
    int n = size * 2;
    Matrix C(n, vector<int>(n));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j]               = C11[i][j];
            C[i][j + size]        = C12[i][j];
            C[i + size][j]        = C21[i][j];
            C[i + size][j + size] = C22[i][j];
        }
    }
    return C;
}

// Strassen's algorithm: recursively multiplies two n x n matrices (n = 2^k)
// using 7 multiplications instead of 8.
Matrix strassenMultiply(const Matrix& A, const Matrix& B) {
    int n = A.size();

    if (n == 1) {                              // base case: 1x1 "matrix"
        return Matrix{{A[0][0] * B[0][0]}};
    }

    int half = n / 2;
    // Split A and B into quadrants
    Matrix A11 = getQuadrant(A, 0, 0, half),    A12 = getQuadrant(A, 0, half, half);
    Matrix A21 = getQuadrant(A, half, 0, half), A22 = getQuadrant(A, half, half, half);
    Matrix B11 = getQuadrant(B, 0, 0, half),    B12 = getQuadrant(B, 0, half, half);
    Matrix B21 = getQuadrant(B, half, 0, half), B22 = getQuadrant(B, half, half, half);

    // 7 recursive multiplications (Strassen's formulas)
    Matrix M1 = strassenMultiply(add(A11, A22), add(B11, B22));
    Matrix M2 = strassenMultiply(add(A21, A22), B11);
    Matrix M3 = strassenMultiply(A11, subtract(B12, B22));
    Matrix M4 = strassenMultiply(A22, subtract(B21, B11));
    Matrix M5 = strassenMultiply(add(A11, A12), B22);
    Matrix M6 = strassenMultiply(subtract(A21, A11), add(B11, B12));
    Matrix M7 = strassenMultiply(subtract(A12, A22), add(B21, B22));

    // Combine results into the 4 result quadrants
    Matrix C11 = add(subtract(add(M1, M4), M5), M7);
    Matrix C12 = add(M3, M5);
    Matrix C21 = add(M2, M4);
    Matrix C22 = add(subtract(add(M1, M3), M2), M6);

    return combine(C11, C12, C21, C22);
}