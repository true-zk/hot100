/*
    hard
    一维数组，对每个数，找到第一个比他小的
    -> 一维数组，对每个元素，找第一个满足某种条件的数，
    -> 单调栈
*/
#include <string>
#include <stack>
#include <vector>
#include <limits>
#include <iostream>
#include <algorithm>

using namespace std;


// 思路：按照高度遍历，对每个高度，只要得知了其左右边界（第一个比当前高度低的位置），就可求得
// 同样高度的柱子结果是一致的
// 解法：带有位置信息的单调栈，求每个柱子的左右边界
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        stack<pair<int, int>> stk;  // (val, idx)
        vector<int> leftbound(n, -1), rightbound(n, -1);
        stk.push(pair<int, int> {-1, -1});  // 永远不会出栈，作为左边界
        for (int i = 0; i < n; ++i) {
            while (stk.top().first >= heights[i])  // 左边界要严格小于heights[i]
            {
                stk.pop();
            }
            leftbound[i] = stk.top().second + 1;
            stk.push(pair<int, int> {heights[i], i});
        }
        while (!stk.empty())
        {
            stk.pop();
        }
        stk.push(pair<int, int> {-1, n});  // 右边界
        for (int i = n - 1; i >= 0; --i) {
            while (stk.top().first >= heights[i])  // 同样，右边界严格小于heights[i]
            {
                stk.pop();
            }
            rightbound[i] = stk.top().second - 1;
            stk.push(pair<int, int> {heights[i], i});
        }
        // 求解，遍历每个高度
        int res = 0;
        for (int i = 0; i < n; ++i) {
            res = max(res, (heights[i] * (rightbound[i] - leftbound[i] + 1)));
        }
        return res;
    }
};


// 优化：把三次遍历变成一次：
// 求左边界的时候，当 栈顶 要出栈的时候，就是遇到了右边界的时候（第一个小于自己的）
// 而栈顶的左边界一定已经在之前求得了（不然不会入栈）
// 这时候就能求解 栈顶 的 高度 的最大面积了
class Solution2 {
    public:
    int largestRectangleArea(vector<int> &heights) {
        int res = 0;
        int n = heights.size();
        stack<pair<int, int>> stk;  // (val, idx)
        vector<int> leftbound;
        stk.push(pair<int, int> {-1, -1});  // 哨兵
        for (int i = 0; i < n; ++i) {
            while (heights[i] <= stk.top().first)
            {
                // 当前stk.top遇到了右边界(heights[i] > top)，处理
                auto curtop = stk.top();
                res = max(res, (curtop.first * (i - leftbound[curtop.second])));
                stk.pop();
            }
            // 此时 top > heights[i], 计算左边界，入栈
            leftbound.push_back(stk.top().second + 1);
            stk.push(pair<int, int> {heights[i], i});
        }
        // 额外考虑最后一段升序，把栈里剩余元素出栈和计算
        // 注意到不能碰到哨兵，因为哨兵会curtop.second == -1会越界
        while (stk.top().first >= 0)
        {
            auto curtop = stk.top();
            res = max(res, (curtop.first * (n - leftbound[curtop.second])));
            stk.pop();
        }
        return res;
    }
};


int main() {
    Solution2 sol;
    vector<int> heights {2,1,5,6,2,3};

    cout << sol.largestRectangleArea(heights) << endl; // 10

    return 0;
}