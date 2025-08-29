/*
    medium
    多源广度优先搜索
*/
#include <iostream>
#include <vector>
#include <utility>
using namespace std;


// 灵神解，有许多值得学的地方：
// 1. Direct方向矩阵
// 2. 用vector<pair<int, int>>模拟队列，更方便
// 3. emplace_back直接构造
// 4. move而不是拷贝
class Solution {
public:
    int Direct[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    int orangesRotting(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int res = 0;
        int fresh = 0;
        vector<pair<int, int>> q;  // 用vec模拟队列
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    ++fresh;
                }
                else if (grid[i][j] == 2) {
                    q.emplace_back(i, j);  // 直接调用构造函数
                }
            }
        }

        while (fresh && !q.empty())
        {
            ++res;  // 时间++
            vector<pair<int, int>> nextq;
            for (auto& [x, y] : q) {
                for (auto d: Direct) {
                    int i = x + d[0], j = y + d[1];
                    if (i >= 0 && i < m && j >= 0 && j < n && grid[i][j] == 1) {
                        grid[i][j] = 2;
                        nextq.emplace_back(i, j);
                        --fresh;
                    }
                }
            }
            q = move(nextq);  // 移动而非拷贝
        }
        
        return (fresh > 0) ? -1 : res;
    }
};


int main() {
    vector<vector<int>> grid = {
        {2,1,1},
        {1,1,0},
        {0,1,1}
    };

    Solution sol;
    int res = sol.orangesRotting(grid);
    cout << "腐烂所有橘子的最少分钟数: " << res << endl; // 期望输出：4

    // 你可以再加一个无解的测试
    vector<vector<int>> grid2 = {
        {2,1,1},
        {0,1,1},
        {1,0,1}
    };
    cout << "无解测试: " << sol.orangesRotting(grid2) << endl; // 期望输出：-1

    return 0;
}