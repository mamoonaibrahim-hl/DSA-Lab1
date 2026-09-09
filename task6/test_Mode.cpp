#include <iostream>
#include <vector>
#include <algorithm>
#include "Mode.h"
using namespace std;

void printSorted(vector<int> v) {
    sort(v.begin(), v.end());          // sort just for consistent, readable output
    cout << "{ ";
    for (int x : v) cout << x << " ";
    cout << "}";
}

int main() {
    // Test 1: Unique mode
    vector<int> arr1 = {1, 2, 2, 3, 4};
    cout << "Test 1 (unique mode): ";
    printSorted(findMode(arr1));
    cout << endl;   // expected: { 2 }

    // Test 2: Multiple modes
    vector<int> arr2 = {1, 1, 2, 2, 3};
    cout << "Test 2 (multiple modes): ";
    printSorted(findMode(arr2));
    cout << endl;   // expected: { 1 2 }

    // Test 3: Empty array
    vector<int> arr3 = {};
    cout << "Test 3 (empty array): ";
    printSorted(findMode(arr3));
    cout << (findMode(arr3).empty() ? "   PASS" : "   FAIL") << endl;

    return 0;
}