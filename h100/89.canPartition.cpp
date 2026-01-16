/*
    medium
    0-1backpack问题

    经典0-1背包：
        - 选，or不选，不能超过背包总容量
        - 优化目标：最大价值
        - dp[i][j] := 前i个物品，"容量"不超过j，取得的最大价值
        - 转移方程：选i(容量 - w[i], 价值 + v[i])，或者不选i (dp[i-1][j])
          dp[i][j] = max(dp[i-1][j], dp[i-1][j-w[i]] + v[i]), only when j >= w[i]
*/
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <limits>

using namespace std;


// 回溯实现，每个位置选或者不选
// 2^n，超时
class Solution {
public:

    void backtrack(vector<int> &nums, int idx, int lsum, int rsum, bool &valid) {
        if (valid) return;
        if (idx == nums.size() && lsum == rsum) {
            valid = true;
            return;
        }
        if (idx >= nums.size()) return;

        backtrack(nums, idx + 1, lsum + nums[idx], rsum, valid);
        backtrack(nums, idx + 1, lsum, rsum + nums[idx], valid);
    }

    bool canPartition(vector<int>& nums) {
        bool valid = false;
        backtrack(nums, 0, 0, 0, valid);
        return valid;
    }
};


// 选与不选 -> 0-1背包
// 优化目标：恰好等于元素和的一半（这个目标可以先求出来！）
// 即转换成，容量是half
class Solution2 {
public:
    bool canPartition(vector<int>& nums) {
        if (nums.size() == 1) return false;  // 只有一个元素，元素在[1, 100]，不可能划分
        int n = nums.size();
        int sumall = 0, maxnum = 0;
        for (auto &el: nums) {
            sumall += el;
            maxnum = max(maxnum, el);
        }
        if (sumall % 2 == 1) return false;     // a. 总和是奇数，不可能能分割为正整数和
        if (maxnum > sumall / 2) return false; // b. 最大元素 > half, 剩下的元素和 < half，不可能存在分割
        
        // b.隐含了nums[i] <= half 

        // 0-1背包
        int target = sumall / 2;
        // dp[i][j] := 选择到第i个数，和为j，存不存在这样的可能，存在=true, 不存在=false
        // nums[i] <= half, 保证了不会越界
        // 初始都为false
        vector<vector<int>> dp(n, vector<int>(target + 1, 0));
        // 1. dp[i][0] := 选择到第i个数，和为0，都存在，只要都不选就行，初始化为true
        for (int i = 0; i < n; ++i) {
            dp[i][0] = 1;
        }
        // 2. dp[0][nums[0]] := 选择到第0个数，和恰好为nums[0]，初始化为true
        for (int j = 0; j <= target; ++j) {
            dp[0][nums[0]] = true;
        }
        // dp[i][j] = 
        //  - 如果j >= nums[i]: 可选可不选：有一种true则为true：dp[i - 1][j] | dp[i - 1][j - nums[i]]
        //  - 如果j < nums[i]: 只能不选，dp[i - 1][j]
        for (int i = 1; i < n; ++i) {
            for (int j = 1; j <= target; ++j) {
                if (j >= nums[i]) {
                    dp[i][j] = dp[i - 1][j] | dp[i - 1][j - nums[i]];
                }
                else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }

        return dp[n - 1][target];
    }
};


// 进一步优化0-1背包，因为只依赖dp[i-1]，所以只保留dp[j]就行了，不需要二维
class Solution3 {
public:
    bool canPartition(vector<int>& nums) {
        if (nums.size() == 1) return false;
        int n = nums.size();
        int sumall = 0, maxel = 0;
        for (auto &el: nums) {
            sumall += el;
            maxel = max(maxel, el);
        }
        if (sumall % 2 == 1 || maxel > sumall / 2) return false;

        int half = sumall / 2;
        vector<int> dp(half + 1, 0);  // 初始化成false
        dp[0] = true;  // 容量为0，表示全不选为true
        for (int i = 0; i < n; ++i) {
            for (int j = half; j >= nums[i]; --j) {  // 从half -> nums[i]，保证了1.不会越界，2.先更新j再更新j-nums[i]
                dp[j] = dp[j] | dp[j - nums[i]];  // 等价于 dp[i][j] = dp[i-1][j] | dp[i-1][j-1]
            }
        }
        return dp[half];
    }
};


int main() {
    vector<int> nums;
    Solution2 sol;

    nums = {1,5,11,5};
    cout << sol.canPartition(nums) << endl;

    nums = {1,2,3,5};
    cout << sol.canPartition(nums) << endl;

    return 0;
}