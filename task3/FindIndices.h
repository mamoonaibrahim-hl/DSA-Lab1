#include <vector>
using namespace std;

// Returns a vector containing all indices in 'arr' where 'arr[i] == key'.
// Time Complexity O(n) single pass through the array.
// Space Complexity O(k) k = number of matches found.
vector<int> findAllIndices(const vector<int>& arr, int key) {
    vector<int> indices;               // stores matching positions
    for (int i = 0; i < (int)arr.size(); i++) {
        if (arr[i] == key) {
            indices.push_back(i);      // record index of match
        }
    }
    return indices;                    // empty if no match / empty array
}