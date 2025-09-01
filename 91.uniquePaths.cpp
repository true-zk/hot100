/*
    medium
    2D dp经典
*/
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


// 2Ddp
// dp[i][j] = 到(i, j)的总共路径
// 要么从上面来，要么从左边来
// dp[i][j] = dp[i-1][j] + dp[i][j-1]
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, 0));
        // 边界：最左和最上面，只有一种走法
        for (int i = 0; i < m; ++i) {
            dp[i][0] = 1;
        }
        for (int j = 0; j < n; ++j) {
            dp[0][j] = 1;
        }
        // 从11开始遍历
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }

        return dp[m - 1][n - 1];
    }
};


// dp[i][j] = dp[i-1][j] + dp[i][j-1]
// 即仅和i-1有关，可以只用1D的dp来记录
// d[j]记录走到 上一层/当前层，j列的总数
class Solution2 {
public:
    int uniquePaths(int m, int n) {
        vector<int> dp(n, 1);  // 只保留第一行，初始化为1
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                // dp[0] 永远是1
                dp[j] = dp[j] + dp[j - 1];  // dp[j]是从上边（还没更新），dp[j-1]是从左边（已经更新到当前层）
            }
        }
        return dp[n - 1];
    }
};


int main() {
    Solution2 sol;

    cout << sol.uniquePaths(7, 3) << endl;
    cout << sol.uniquePaths(3, 2) << endl;
    cout << sol.uniquePaths(1, 1) << endl;

    return 0;
}