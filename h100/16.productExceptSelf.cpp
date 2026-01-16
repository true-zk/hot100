/*
    238. 除自身以外数组的乘积
    medium

    给你一个整数数组 nums，返回 数组 answer ，其中 answer[i] 等于 nums 中除 nums[i] 之外其余各元素的乘积 。
    题目数据 保证 数组 nums之中任意元素的全部前缀元素和后缀的乘积都在  32 位 整数范围内。
    请 不要使用除法，且在 O(n) 时间复杂度内完成此题。

    两个方向遍历：
    - 从左往右 再从右往左
    - res[i] = preleft[i] * preright[i]

    空间优化到O(1)：
    只要一个res数组就行，开始从左，然后从右，一样的
*/

#include <vector>
#include <iostream>
using std::vector;
using std::cout; using std::endl;
using std::cin;


class Solution1 {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> prefix_prod(nums.size(), 1);
        vector<int> suffix_prod(nums.size(), 1);
        for (int i = 1; i < n; ++i) {
            prefix_prod[i] = prefix_prod[i - 1] * nums[i - 1];
        }
        for (int i = n - 2; i >= 0; --i) {
            suffix_prod[i] = suffix_prod[i + 1] * nums[i + 1];
        }
        for (int i = 0; i < n; ++i) {
            prefix_prod[i] = prefix_prod[i] * suffix_prod[i];
        }
        return prefix_prod;
    }
};


class Solution2 {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n, 1);
        for (int i = 1; i < n; ++i) {
            res[i] = res[i - 1] * nums[i - 1];  // prefix
        }
        int suffix = nums[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            res[i] = res[i] * suffix;
            suffix = suffix * nums[i];
        }
        return res;
    }
};


class Solution3 {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n);
        res[0] = 1;  // rm init time consume
        for (int i = 1; i < n; ++i) {
            res[i] = res[i - 1] * nums[i - 1];  // prefix
        }
        int suffix = nums[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            res[i] = res[i] * suffix;
            suffix = suffix * nums[i];
        }
        return res;
    }
};


int main() {
    cout << "Plz input a array: ";
    vector<int> nums;
    int tmp;
    while (cin >> tmp)
    {
        nums.push_back(tmp);
    }
    Solution2 sol;
    vector<int> result = sol.productExceptSelf(nums);
    cout << "The result is: ";
    for (int i : result) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}