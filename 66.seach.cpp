/*
    medium
*/

#include <iostream>
#include <vector>
#include <utility>

using namespace std;


// 数组从mid一分为二，一部分有序，一部分不一定，
// 落在有序部分则完成
// 落在另一部分，继续一分为二
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        if (n == 1) return nums[0] == target ? 0 : -1;

        int l = 0, r = n - 1;
        int mid;
        while (l <= r)
        {
            mid = l + (r - l) / 2;
            if (nums[mid] == target) return mid;
            // 处理旋转
            // left half part 有序
            if (nums[l] <= nums[mid]) {
                if (nums[l] <= target && target < nums[mid]) {
                    r = mid - 1;
                }
                else {
                    l = mid + 1;
                }
            }
            // right half part 有序
            else {
                if (nums[mid] < target && target <= nums[r]) {
                    l = mid + 1;
                }
                else {
                    r = mid - 1;
                }
            }
        }
        return  -1;
    }
};


int main() {
    Solution sol;

    vector<int> nums1 = {4,5,6,7,0,1,2};
    int target1 = 0;
    cout << "测试1: " << sol.search(nums1, target1) << endl; // 4

    vector<int> nums2 = {4,5,6,7,0,1,2};
    int target2 = 3;
    cout << "测试2: " << sol.search(nums2, target2) << endl; // -1

    vector<int> nums3 = {1};
    int target3 = 0;
    cout << "测试3: " << sol.search(nums3, target3) << endl; // -1

    vector<int> nums4 = {1,3};
    int target4 = 3;
    cout << "测试4: " << sol.search(nums4, target4) << endl; // 1

    return 0;
}