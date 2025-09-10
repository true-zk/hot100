/*
    560. 和为 K 的子数组
    medium

    给你一个整数数组 nums 和一个整数 k ，请你统计并返回 该数组中和为 k 的子数组的个数 。
    子数组是数组中元素的连续非空序列。

    子数组和 == 可以前缀和 pre[i] = [0, i]的所有数的和，那么[j, i]的和：
    pre[i]−pre[j−1]==k
    pre[j−1]==pre[i]−k

    进一步，需要查pre[i]出现了多少次，用hashmap记录：
    {sum: cnt} key为pre[i]，value为出现的次数
    这样可以O(1)查询
    - 注意初始化，(0, 1)，和为0的情况，初始有一种即pre[i] - k == 0，这时候pre[j - 1]=0，即一个数也不加
*/

#include <vector>
#include <unordered_map>

using std::vector;
using std::unordered_map;


// Nums can be negative, so can not use slide window.


// prefixsum and double-loop O(n^2)
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int res = 0;
        int n = nums.size();
        vector<int> prefixsum {0}; // prefixsum[0] = 0
        for (int i = 0; i < n; ++i) {
            prefixsum.push_back(prefixsum[i] + nums[i]);
        }

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (prefixsum[j] - prefixsum[i] == k) {
                    ++res;
                }
            }
        }

        return res;
    }
};


// use hash map to save prefixsum!!!
// twoSum!!!!!!!!!!!!!!!!!!!!!!!!!!!
// pre[i] - pre[j - 1] == k
// pre[j - 1] == pre[i] - k
// res += map[pre[i] - k]

// map[0] = 1
class Solution {
public:
    int subarraySum(vector<int> &nums, int k) {
        int res = 0;
        int n = nums.size();
        // vector<int> prefixsum {nums[0]};
        int pre = 0;
        unordered_map<int, int> map;  // prefixsum: n_subarray
        map[0] = 1; // init, pre = 3 + 4, k = 7, pre - k = 0, need 1
        for (int i = 0; i < n; ++i) {
            pre += nums[i];
            if (map.count(pre - k)) {
                res += map[pre - k];
            }
            ++map[pre];
        }

        return res;
    }
};