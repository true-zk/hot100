/*
    medium
*/

#include <iostream>
#include <vector>
#include <utility>

using namespace std;


class Solution {
public:
    int findMin(vector<int>& nums) {
        if (nums.size() == 1) return nums[0];
        int minres = 5001;
        int n = nums.size();
        int l = 0, r = n - 1;
        int mid;
        while (l <= r)
        {
            mid = l + (r - l) / 2;
            // left part is in order.
            if (nums[l] <= nums[mid]) {
                minres = min(minres, nums[l]);
                // 后面应该搜索右半边
                l = mid + 1;
            }
            // right part is in order.
            else {
                minres = min(minres, nums[mid]);
                r = mid - 1;
            }
        }
        return minres;
    }
};


int main() {
    Solution sol;

    vector<int> nums1 = {4,5,6,7,0,1,2};
    cout << "测试1: " << sol.findMin(nums1) << endl; // 0

    vector<int> nums2 = {7,0,1,2,4,5,6};
    cout << "测试2: " << sol.findMin(nums2) << endl; // 0

    vector<int> nums3 = {1};
    cout << "测试3: " << sol.findMin(nums3) << endl; // 1

    vector<int> nums4 = {1,3};
    cout << "测试4: " << sol.findMin(nums4) << endl; // 1

    return 0;
}