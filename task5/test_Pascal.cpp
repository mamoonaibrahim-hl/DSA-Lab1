#include <iostream>
#include <vector>
#include "Pascal.h"
using namespace std;

void printTriangle(const vector<vector<int>>& t) {
    for (const auto& row : t) {
        for (int val : row) cout << val << " ";
        cout << endl;
    }
}

int main() {
    cout << "n = 0:" << endl;
    auto t0 = generatePascal(0);
    printTriangle(t0);
    cout << (t0.empty() ? "PASS (no rows)" : "FAIL") << endl << endl;

    cout << "n = 1:" << endl;
    auto t1 = generatePascal(1);
    printTriangle(t1);
    cout << ((t1.size() == 1 && t1[0] == vector<int>{1}) ? "PASS" : "FAIL") << endl << endl;

    cout << "n = 5:" << endl;
    auto t5 = generatePascal(5);
    printTriangle(t5);
    vector<int> expectedRow5 = {1, 4, 6, 4, 1};
    cout << (t5[4] == expectedRow5 ? "PASS (row 5 == {1,4,6,4,1})" : "FAIL") << endl;

    return 0;
}