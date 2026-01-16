/*
    medium
    2D dp经典
*/
#include <vector>
#include <iostream>
#include <algorithm>


using namespace std;


// dp[i][j] = 到(i, j)的最小总和
// dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j]
// 边界：最上层和最左层，只有一条路可以走
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));
        dp[0][0] = grid[0][0];
        for (int i = 1; i < m; ++i) {
            dp[i][0] = dp[i - 1][0] + grid[i][0];
        }
        for (int j = 1; j < n; ++j) {
            dp[0][j] = dp[0][j - 1] + grid[0][j];
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
            }
        }

        return dp[m - 1][n - 1];
    }
};


int main() {
    Solution sol;
    vector<vector<int>> grid1 = {
        {1,3,1},
        {1,5,1},
        {4,2,1}
    };
    cout << sol.minPathSum(grid1) << endl; // 7

    vector<vector<int>> grid2 = {
        {1,2,3},
        {4,5,6}
    };
    cout << sol.minPathSum(grid2) << endl; // 12

    return 0;
}
