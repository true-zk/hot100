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