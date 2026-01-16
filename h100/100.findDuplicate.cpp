/*
    medium
    Limitation: O(n)，O(1)空间，不修改
    证明至少存在一个重复数字：鸽巢
*/
#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>
#include <random>


using namespace std;


// 这个下标的方法要交换，会破坏原数组，要做得拷贝一份数组O(n)空间
// 整数都在[1, n]之内(n种可能)，nums.size() == n + 1
// 鸽巢原理必定有重复值
// 因为限定死了[1, n]和n + 1，直接利用下标
// 如果a[i] != i，不断交换a[i]和a[a[i]]，
// 在a[n + 1]的肯定是重复的
// 那么如果交换的时候发现了a[i] == a[a[i]]肯定也直接找到，退出了
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            while (nums[i] != i + 1)
            {
                if (nums[i] == nums[nums[i] - 1]) return nums[i];
                swap(nums[i], nums[nums[i] - 1]);
            }
        }
        // 没退出，则nums[n]肯定是多出来的
        return nums[n];
    }
};


// 正解：快慢指针
// 建一个i -> nums[i]的边，
// 那么整个数组会连成一个链表，0 -> nums[0] -> nums[nums[0]] -> ...
// 由于存在重复元素，肯定存在 nums[i] == nums[j]，
// 就会存在 -> nums[i] -> nums[nums[i]] -> ... -> nums[j] 行成环
// 然后用快慢指针找到环
// 再，慢指针从头，快指针继续，都只步进1，找到交汇处
class Solution2 {
public:
    int findDuplicate(vector<int> &nums) {
        int slow = 0, fast = 0;
        do
        {
            slow = nums[slow];
            fast = nums[nums[fast]];
        } while (slow != fast);
        slow = 0;  // slow重新从入口走
        // 
        while (slow != fast)
        {
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;
    }
};


int main() {
    Solution sol;

    vector<int> nums1 = {1, 3, 4, 2, 2};
    cout << sol.findDuplicate(nums1) << endl; // 2

    vector<int> nums2 = {3, 1, 3, 4, 2};
    cout << sol.findDuplicate(nums2) << endl; // 3

    vector<int> nums3 = {1, 1};
    cout << sol.findDuplicate(nums3) << endl; // 1

    vector<int> nums4 = {1, 1, 2};
    cout << sol.findDuplicate(nums4) << endl; // 1

    return 0;
}