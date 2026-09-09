#include <iostream>
#include <vector>
#include "FindIndices.h"
using namespace std;

//prints a vector of integers for output
void printVector(const vector<int>& v) {
    cout << "{ ";
    for (int x : v) cout << x << " ";
    cout << "}";
}

int main() {
    //Test 1: Multiple occurrences
    vector<int> arr1 = {2, 4, 6, 4, 8, 4, 10};
    vector<int> result1 = findAllIndices(arr1, 4);
    cout << "Test 1 (multiple occurrences): ";
    printVector(result1);
    cout << (result1 == vector<int>{1, 3, 5} ? "   PASS" : "   FAIL") << endl;

    //Test 2: Key not present
    vector<int> arr2 = {1, 2, 3, 4, 5};
    vector<int> result2 = findAllIndices(arr2, 99);
    cout << "Test 2 (key not present): ";
    printVector(result2);
    cout << (result2.empty() ? "   PASS" : "   FAIL") << endl;

    // Test 3: Empty array
    vector<int> arr3 = {};
    vector<int> result3 = findAllIndices(arr3, 5);
    cout << "Test 3 (empty array): ";
    printVector(result3);
    cout << (result3.empty() ? "   PASS" : "   FAIL") << endl;

    return 0;
}