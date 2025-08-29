/*
    medium
    回溯模板题
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


// O(n*n!) n!次调用栈，每次n的复制操作
class Solution {
public:
    void backtrack(vector<vector<int>> &res, vector<int> &nums, int first, int len) {
        // 1. 终止条件
        if (first == len) {
            res.emplace_back(nums);
            return;
        }
        // 2. 选择本层集合中的元素进行递归处理
        for (int i = first; i < len; ++i) {
            // 动态维护数组
            swap(nums[i], nums[first]);  // 这里实际上在选择本层填的值是什么
            /*  [1, x, x]  固定第一个是1
                [2, 1, x]   第一个是2， 这样后面还会通过一样的方式，让第二个位置遍历1,3的可能
                [3, x, 1]
            */
            // 递归填下一个数字
            backtrack(res, nums, first + 1, len);
            // 还原数组
            swap(nums[i], nums[first]);  // 还原是必要的，不然会换乱
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        backtrack(res, nums, 0, nums.size());
        return res;
    }
};


int main() {
    vector<int> nums {1, 2, 3};
    Solution sol;
    vector<vector<int>> res = sol.permute(nums);
    for (auto &e: res) {
        for (auto &i: e) {
            cout << i << " ";
        }
        cout << endl;
    }
    return 0;
}