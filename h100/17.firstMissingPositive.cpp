/*
    41. 缺失的第一个正数
    hard

    给你一个未排序的整数数组 nums ，请你找出其中没有出现的最小的正整数。
    请你实现时间复杂度为 O(n) 并且只使用常数级别额外空间的解决方案。

    没有真正的空间O(1)，只能借助原数组

    解法，用原地的idx来hash，
    - 第一次遍历 把原来是负数的数变成n + 1，这样就只考虑正数了
    - 第二次遍历 把[1, n]的数，对应下标位置设置为 负数，这样就进行了hash
    - 第三次遍历 检查每个位置，
            - 如果全是负数，说明恰好排满了，很好，输出n+1即可
            - 否则就是第一个正数的位置是答案

*/

#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
using std::vector;
using std::abs;
using std::swap;
using std::cout; using std::endl;
using std::cin;

/*
Limitation: O(n) time complexity and O(1) space complexity
*/
// 1. 没有事实上的O(1)空间复杂度解法, 利用nums中一些空间
// 2. 抽屉原理，n size的数组，没出现的最小正整数必然在[1, n+1]之间

// 如果没有限制，使用hash表可以解决，
// 所以模拟hash mapping
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int res = 1;
        int n = nums.size();
        // if nums[i] < 0, nums[i] = n + 1
        int full_flag = n + 1;
        for (int i = 0; i < n; ++i) {
            if (nums[i] <= 0) {
                nums[i] = full_flag;
            }
        }
        // 注意这里用负数，因为这样不会改变数组中的绝对值，
        // 如果改了绝对值，例如用-1作为标记，会导致遍历到该值的时候可能变成了-1，丢失了原值
        for (int i = 0; i < n; ++i) {
            int tmp_num = abs(nums[i]);
            if (tmp_num <= n && tmp_num > 0)
            {
                nums[tmp_num - 1] = -abs(nums[tmp_num - 1]);
            }
        }

        // check not neg
        for (int i = 0; i < n; ++i)
        {
            if (nums[i] > 0) {
                return i + 1;
            }
        }
        return full_flag;
    }
};


// 交换，最多交换N次可以排序好
// 如果交换后nums[i]位置还不对，继续交换即可，直到nums[i] == nums[nums[i] - 1]
// 说明两个位置都是对的
class Solution2 {
public:
    int firstMissingPositive(vector<int> &nums) {
        int n = nums.size();
        // 最多执行N次交换
        for (int i = 0; i < n; ++i) {
            while (nums[i] > 0 && nums[i] <= n && nums[i] != nums[nums[i] - 1])
            {
                swap(nums[i], nums[nums[i] - 1]);
            }
        }
        for (int i = 0; i < n; ++i) {
            if (nums[i] != i + 1) {
                return i + 1;
            }
        }
        return n + 1;
    }
};


int main() {
    vector<int> nums = {3,4,-1,1};
    Solution sol;
    cout << sol.firstMissingPositive(nums) << endl;
    return 0;
}