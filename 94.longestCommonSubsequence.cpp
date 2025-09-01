/*
    medium
*/
#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>


using namespace std;


// 经典2Ddp
// dp[i][j] = s1[0:i] 和 s2[0:j]的最长公共子序列
//  - s[i] == s[j], dp[i][j] = dp[i-1][j-1] + 1
//  - s[i] != s[j], dp[i][j] = max dp[i - 1][j] , dp[i][j - 1]
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int n1 = text1.size(), n2 = text2.size();
        // 多创建一行和一列，可以避免边界处理
        vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, 0));
        for (int i = 0; i < n1; ++i) {
            for (int j = 0; j < n2; ++j) {
                if (text1[i] == text2[j]) {
                    dp[i + 1][j + 1] = dp[i][j] + 1;
                }
                else {
                    dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);
                }
            }
        }
        return dp[n1][n2];
    }
};


int main() {
    Solution sol;
    cout << sol.longestCommonSubsequence("abcde", "ace") << endl;    // 3
    cout << sol.longestCommonSubsequence("abc", "abc") << endl;      // 3
    cout << sol.longestCommonSubsequence("abc", "def") << endl;      // 0
    cout << sol.longestCommonSubsequence("bsbininm", "jmjkbkjkv") << endl; // 1
    return 0;
}