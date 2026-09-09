#include <vector>
#include <unordered_map>
using namespace std;

// Returns all mode(s) (most frequent value(s)) of the array.
// Empty array returns an empty vector.
vector<int> findMode(const vector<int>& arr) {
    vector<int> modes;
    if (arr.empty()) return modes;                 // handle empty array

    unordered_map<int, int> freq;                   // value -> frequency
    for (int x : arr) freq[x]++;

    int maxFreq = 0;
    for (auto& pair : freq) {
        maxFreq = max(maxFreq, pair.second);         // find highest frequency
    }

    for (auto& pair : freq) {
        if (pair.second == maxFreq) {
            modes.push_back(pair.first);             // collect all values with max frequency
        }
    }
    return modes;
}