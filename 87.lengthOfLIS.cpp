/*
    medium
    dp
    Limitation： O(nlogn)
*/
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <limits>

using namespace std;


// 普通dp O(n^2)
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            int tmp = 1;
            for (int j = 0; j < i; ++j) {
                if (nums[j] < nums[i]) {
                    tmp = max(tmp, dp[j] + 1);
                }
            }
            dp[i] = tmp;
        }
        // 最大结果不一定在结束位置
        return *max_element(dp.begin(), dp.end());
    }
};


// 二分 + 贪心优化 
// 贪心：如果要序列尽量长，就要选尽量小的值使其上升？
// 维护d[i]，表示长度为 i 的子序列的 末尾元素最小值
// 初始: len = 1 (当前最大长度), d[1] = nums[0]
// d[i]是单增的：如果 i < j，一定d[i] < d[j]
// 遍历nums，更新d[len]和len，
// - nums[i] >  d[len]: len = len + 1, d[len] = nums[i]
// - nums[i] <= d[len]: 说明nums[i]是之前的更小的尾元素，找到 d[k] < nums[i], 将d[k+1] = nums[i]
// 根据d[i]的单调性，更新的时候用二分 降低到nlogn 
class Solution2 {
public:
    int lowerbound(vector<int> &arr, int l, int r, int tgt) {
        int mid;
        while (l < r)  // 这里==的时候就出循环了，不是判断是不是只是找下界
        {
            mid = l + (r - l) / 2;
            if (arr[mid] >= tgt) {
                r = mid;
            }
            else {
                l = mid + 1;
            }
        }
        return l;
    }

    int lengthOfLIS(vector<int> &nums) {
        int n = nums.size();
        vector<int> d(n + 1, 0);
        int len = 1;
        d[len] = nums[0];
        for (int i = 1; i < n; ++i) {
            if (nums[i] > d[len]) {
                ++len;
                d[len] = nums[i];
            }
            else {  // 二分
                int lb = lowerbound(d, 1, len, nums[i]);  // 第一个 >= nums[i]的下标
                d[lb] = nums[i];
            }
        }
        return len;
    }
};


int main() {
    vector<int> nums;
    Solution2 sol;

    nums = {1,3,6,7,9,4,10,5,6};
    cout << sol.lengthOfLIS(nums) << endl;

    nums = {0,1,0,3,2,3};
    cout << sol.lengthOfLIS(nums) << endl;

    nums = {7,7,7,7,7,7,7};
    cout << sol.lengthOfLIS(nums) << endl;

    return 0;
}