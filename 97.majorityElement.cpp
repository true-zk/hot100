/*
    easy
    Limitation: 时间O(n) 空间O(1)
*/
#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>
#include <random>


using namespace std;


// 最简单的解法，排序取中间值
// O(nlogn)
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        return nums[nums.size() / 2];
    }
};


// 随机化，随便挑一个 概率是>n/2的正确性
// 理论最坏是无穷，期望是O(n)
class Solution2 {
public:
    int majorityElement(vector<int> &nums) {
        mt19937 rng(random_device{}());
        uniform_int_distribution<int> dist(0, nums.size() - 1);  // [0, n-1]
        while (true)
        {
            int candidate = nums[dist(rng)];
            int cnt = 0;
            for (int el: nums) {
                if (el == candidate) ++cnt;
            }
            if (cnt > nums.size() / 2) return candidate;
        }
        return -1;
    }
};


// Boyer-Moore投票算法：
// 众数是1,其他是-1
// 全加起来，和肯定>0
class Solution3 {
public:
    int majorityElement(vector<int> &nums) {
        int cnt = 0;
        int candidate = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (cnt == 0) {
                candidate = nums[i];
                ++cnt;
            }
            else {
                if (candidate == nums[i]) ++cnt;
                else --cnt;
            }
        }
        return candidate;
    }
};


int main() {
    Solution sol1;
    Solution2 sol2;
    Solution3 sol3;

    vector<int> nums1 = {3, 3, 4};
    cout << sol1.majorityElement(nums1) << endl; // 3
    cout << sol2.majorityElement(nums1) << endl; // 3
    cout << sol3.majorityElement(nums1) << endl; // 3

    vector<int> nums2 = {2, 2, 1, 1, 1, 2, 2};
    cout << sol1.majorityElement(nums2) << endl; // 2
    cout << sol2.majorityElement(nums2) << endl; // 2
    cout << sol3.majorityElement(nums2) << endl; // 2

    return 0;
}