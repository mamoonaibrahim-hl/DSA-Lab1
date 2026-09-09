#include <vector>
using namespace std;

// Generates Pascal's Triangle with 'n' rows
vector<vector<int>> generatePascal(int n) {
    vector<vector<int>> triangle;

    for (int row = 0; row < n; row++) {
        vector<int> currentRow(row + 1);
        currentRow[0] = currentRow[row] = 1;          // edges of the row are always 1

        for (int k = 1; k < row; k++) {
            // Each inner value = sum of the two values above it
            currentRow[k] = triangle[row - 1][k - 1] + triangle[row - 1][k];
        }
        triangle.push_back(currentRow);
    }
    return triangle;
}