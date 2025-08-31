/*
    medium
    dp
*/
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <limits>

using namespace std;


//
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        int maxv = nums[0];
        int pos = max(0, nums[0]);
        int neg = min(0, nums[0]);

        for (int i = 1; i < n; ++i) {
            if (nums[i] >= 0) {
                pos = max(nums[i], nums[i] * pos);
                neg = neg * nums[i];
            }
            else if (nums[i] < 0) {
                int prepos = pos;
                pos = nums[i] * neg;
                neg = min(nums[i], prepos * nums[i]);  // 负负得正之后不是归零，而是nums[i]
            }
            maxv = max(maxv, pos);
        }
        return maxv;
    }
};


int main() {
    vector<int> nums;
    Solution sol;

    nums = {7, -2, -4};
    cout << sol.maxProduct(nums) << endl;

    return 0;
}