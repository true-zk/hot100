#include <vector>
#include <iostream>

using namespace std;


class Solution {
public:
    int lowerbound(vector<int> &arr, int l, int r, int tgt) {
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (arr[mid] >= tgt) {
                r = mid - 1;
            }
            else {
                l = mid + 1;
            }
        }
        return l;
    }
};


int main() {
    Solution sol;
    vector<int> arr = {1, 2, 4, 4, 5, 7};
    cout << sol.lowerbound(arr, 0, arr.size() - 1, 4) << endl; // 2
    cout << sol.lowerbound(arr, 0, arr.size() - 1, 3) << endl; // 2
    cout << sol.lowerbound(arr, 0, arr.size() - 1, 8) << endl; // 6
    cout << sol.lowerbound(arr, 0, arr.size() - 1, 0) << endl; // 0
    return 0;
}