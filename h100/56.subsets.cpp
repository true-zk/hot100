/*
    medium
    回溯模板题
*/
#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;


// 子集的核心是选与不选的问题
// 解法1，朴素，对当前值给原来每个子集加上
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        res.push_back({});
        for (int i = 0; i < nums.size(); ++i) {
            int sz = res.size();  
            for (int j = 0; j < sz; ++j) {  // 对原来所有的子集
                vector<int> cursub = res[j];  // copyi
                cursub.push_back(nums[i]);    // add cur val
                res.push_back(cursub);         // add to res
            }
        }
        return res;
    }
};


// 解法2，回溯版，那么也就是选与不选的问题了，
// 边界就用是不是到了数组长度，这时候有的选有的不选，生成不同结果
class Solution2 {
public:
    // res记录总结果
    // tmp记录当前的结果，其中有的选，有的不选
    // 当cur到达nums.size的时候边界
    void backtrack(vector<vector<int>> &res, vector<int> &tmp, vector<int> &nums, int cur) {
        // 边界，加入当前解
        if (cur == nums.size()) {
            res.push_back(tmp);
            return;
        }
        // 寻找当前层可能解
        // 要么选择当前值，要么不选当前值
        tmp.push_back(nums[cur]);  // select
        backtrack(res, tmp, nums, cur + 1);  // 移动到下一个值，下一个值同样会选或者不选
        tmp.pop_back();  // no select
        backtrack(res, tmp, nums, cur + 1);  // 移动到下一个值
    }

    vector<vector<int>> subsets(vector<int> &nums) {
        vector<vector<int>> res;
        vector<int> tmp;
        backtrack(res, tmp, nums, 0);
        return res;
    }
};


// 解法3，二进制，
// 子集可以看作一个二进制选则问题，那么可以用二进制遍历
class Solution3 {
public:
    vector<vector<int>> subsets(vector<int> &nums) {
        int n = nums.size();
        vector<vector<int>> res;
        vector<int> cur;
        // 总可能数：2^n = 1 << n
        for (int mask = 0; mask < (1 << n); ++mask) {
            int cur_mask = mask;
            cur.clear();
            for (int j = 0; j < n; ++j) {
                if (cur_mask & 1) {
                    cur.push_back(nums[j]);
                }
                cur_mask = cur_mask >> 1;
            }
            res.push_back(cur);
        }
        return res;
    }
};


void print2DVec(const vector<vector<int>>& res) {
    for (const auto& v : res) {
        cout << "[";
        for (int i = 0; i < v.size(); ++i) {
            cout << v[i];
            if (i + 1 < v.size()) cout << ",";
        }
        cout << "] ";
    }
    cout << endl;
}

int main() {
    vector<int> nums = {1, 2, 3};

    Solution sol1;
    auto res1 = sol1.subsets(nums);
    cout << "解法1所有子集: ";
    print2DVec(res1);

    Solution2 sol2;
    auto res2 = sol2.subsets(nums);
    cout << "解法2所有子集: ";
    print2DVec(res2);

    Solution3 sol3;
    auto res3 = sol3.subsets(nums);
    cout << "解法3所有子集: ";
    print2DVec(res3);

    return 0;
}