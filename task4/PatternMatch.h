#include <string>
using namespace std;

// Naive pattern matching: returns index of first occurrence of 'pattern' in 'text', or -1.
int naiveSearch(const string& text, const string& pattern) {
    int n = text.size();
    int m = pattern.size();

    if (m == 0) return 0;      // convention: empty pattern matches at index 0
    if (m > n) return -1;      // pattern longer than text can't match

    for (int i = 0; i <= n - m; i++) {   // try every starting position in text
        int j = 0;
        while (j < m && text[i + j] == pattern[j]) {
            j++;                          // characters match, keep checking
        }
        if (j == m) return i;             // full pattern matched starting at i
    }
    return -1;                            // pattern never fully matched
}