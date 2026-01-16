/*
    easy
    Limitation: 时间O(n) 空间O(1)
*/
#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>


using namespace std;


// bit 位运算
// 异或两次相等的是0
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            res ^= nums[i];
        }
        return res;
    }
};


int main() {
    Solution sol;
    vector<int> nums1 = {2, 2, 1};
    cout << sol.singleNumber(nums1) << endl; // 1

    vector<int> nums2 = {4, 1, 2, 1, 2};
    cout << sol.singleNumber(nums2) << endl; // 4

    vector<int> nums3 = {1};
    cout << sol.singleNumber(nums3) << endl; // 1

    return 0;
}