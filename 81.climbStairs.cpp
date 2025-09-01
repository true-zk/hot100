/*
    easy
    最典型的dp
*/
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


class Solution {
public:
    int climbStairs(int n) {
        if (n == 1) return 1;
        vector<int> dp(n + 1);
        dp[0] = 1;
        dp[1] = 1;
        for (int i = 2; i <= n; ++i) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }
};


// 本题还有矩阵快速幂和通项公式的优化


int main() {
    Solution sol;
    cout << sol.climbStairs(2) << endl;
    cout << sol.climbStairs(3) << endl;
    cout << sol.climbStairs(4) << endl;

    return 0;
}