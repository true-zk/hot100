/*
    medium
    dp
*/
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n + 1, n + 1);  // 每个i的最少数量，初始化成最大值
        dp[0] = 0;  // dp[0] = 0
        dp[1] = 1;  // dp[1] = 1
        for (int i = 2; i <= n; ++i) {
            int tmp = i;
            for (int j = 1; j *j <= i; ++j) {
                tmp = min(dp[i - j * j] + 1, tmp);
            }   
            dp[i] = tmp;
        }
        return dp[n];
    }
};


// 本题还有个数学解法，「四平方和定理」：任意一个正整数都可以被表示为至多四个正整数的平方和


int main() {
    Solution sol;

    cout << sol.numSquares(13) << endl;

    cout << sol.numSquares(12) << endl;

    return 0;
}