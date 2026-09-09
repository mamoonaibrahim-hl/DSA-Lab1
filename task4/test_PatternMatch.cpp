#include <iostream>
#include "PatternMatch.h"
using namespace std;

void runTest(const string& text, const string& pattern, int expected) {
    int result = naiveSearch(text, pattern);
    cout << "text=\"" << text << "\", pattern=\"" << pattern <<" "
         << result << (result == expected ? "  PASS" : "  FAIL") << endl;
}

int main() {
    runTest("hello world", "hello", 0);     // Pattern at the beginning
    runTest("hello world", "world", 6);     // Pattern at the end
    runTest("hello world", "xyz", -1);      // Pattern not present
    runTest("hello world", "", 0);          // Empty pattern
    return 0;
}