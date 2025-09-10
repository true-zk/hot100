/*
    53. 最大子数组和
    medium

    给你一个整数数组 nums ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。
    子数组是数组中的一个连续部分。

    dp求解比较简单：当前的最大值是前面接上当前和不接的最大值
    dp[i] = max(dp[i - 1] + nums[i], nums[i])
    res = max(res, dp[i])
 */
#include <vector>

using namespace std;


class Solution {
public:
    struct Status {
        int lsum, rsum, msum, isum;
    };

    Status pushUp(Status l, Status r) {
        int isum = l.isum + r.isum;
        int lsum = max(l.lsum, l.isum + r.lsum);
        int rsum = max(r.rsum, r.isum + l.rsum);
        int msum = max(max(l.msum, r.msum), l.rsum + r.lsum);
        return (Status) {lsum, rsum, msum, isum};
    }

    Status get(vector<int>& nums, int l, int r) {
        if (l == r) {
            return (Status) {nums[l], nums[l], nums[l], nums[l]};
        }

        int m = (l + r) / 2;
        Status ls = get(nums, l, m);
        Status rs = get(nums, m + 1, r);
        return pushUp(ls, rs);
    }

    int maxSubArray(vector<int>& nums) {
        return get(nums, 0, nums.size() - 1).msum;
    }
};


// dp
// dp[i] 到i为止的最长序列
// dp[i] = max(dp[i-1] + nums[i], nums[i])
// 只依赖前一个元素，滚动数组
// 由于有可能结尾不是最大的，因为中间有切断的可能，额外记录最大值
class Solution2 {
public:
    int maxSubArray(vector<int> &nums) {
        int n = nums.size();
        int pre = nums[0];
        int maxres = nums[0];
        for (int i = 1; i < n; ++i) {
            pre = max(nums[i], pre + nums[i]);
            maxres = max(maxres, pre);
        }
        return maxres;
    }
};