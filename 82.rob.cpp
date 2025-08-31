/*
    medium
    dp
*/
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 1) return nums[0];
        if (nums.size() == 2) return max(nums[0], nums[1]);
        int n = nums.size();
        vector<int> dp(n);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);  // 注意边界
        for (int i = 2; i < n; ++i) {
            dp[i] = max(dp[i-1], dp[i-2] + nums[i]);
        }

        return dp[n - 1];
    }
};


// 还有种空间优化，因为只依赖前两家，可以不用数组


int main() {
    vector<int> input;
    Solution sol;

    input = {2,1,1,2};
    cout << sol.rob(input) << endl;

    input = {2,7,9,3,1};
    cout << sol.rob(input) << endl;
    return 0;
}