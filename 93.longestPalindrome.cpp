/*
    medium
    2D dp经典
*/
#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>


using namespace std;


// Palindrome的本质：回文去掉头尾还是回文
// 二维dp
// dp[i][j] = 区间[i:j]是回文
// dp[i][j] = true,  when dp[i+1][j-1] && s[i] == s[j]
// dp[i][j] = false, when otherwise
class Solution {
public:
    string longestPalindrome(string s) {
        if (s.size() == 1) return s;
        int n = s.size();
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        // 边界，自己都是回文
        for (int i = 0; i < n; ++i) dp[i][i] = true;
        // 枚举区间，从0 - n-1的所有区间
        // 区间开始 i = n-1 -> 0  // 因为dp[i + 1][j - 1] 依赖后面的i，所以从后遍历开始边界
        // 区间结束 j = i -> n - 1  // j < i 肯定是false，同样dp[i + 1][j - 1] 依赖前面的j
        int resi = 0, resj = 0;
        for (int i = n - 1; i >= 0; --i) {
            for (int j = i + 1; j < n; ++j) {
                if (i + 1 == j) {
                    dp[i][j] = s[i] == s[j];
                }
                else {
                    dp[i][j] = s[i] == s[j] && dp[i + 1][j - 1];
                }
                if(dp[i][j] && j - i > resj - resi) {
                    resj = j;
                    resi = i;
                }
            }
        }
        return s.substr(resi, resj - resi + 1);
    }
};


// 枚举中心
class Solution2 {
public:
    pair<int, int> expandPalindrome(string &s, int l, int r) {
        while (l >= 0 && r < s.size() && s[l] == s[r])
        {
            --l;
            ++r;
        }
        return pair<int, int>(l + 1, r - 1);
    }

    string longestPalindrome(string s) {
        if (s.size() == 1) return s;

        int n = s.size();
        int start = 0, end = 0;
        for (int i = 0; i < s.size(); ++i) {
            pair<int, int> tmp1 = expandPalindrome(s, i, i);
            pair<int, int> tmp2 = expandPalindrome(s, i, i + 1);  // 允许越界

            if (tmp1.second - tmp1.first > end - start) {
                end = tmp1.second;
                start = tmp1.first;
            }
            if (tmp2.second - tmp2.first > end - start) {  // 越界，则second < first，差是负数，不影响
                end = tmp2.second;
                start = tmp2.first;
            }
        }

        return s.substr(start, end - start + 1);
    }
};


int main() {
    Solution2 sol;
    cout << sol.longestPalindrome("babad") << endl; // "bab" 或 "aba"
    cout << sol.longestPalindrome("cbbd") << endl;  // "bb"
    cout << sol.longestPalindrome("a") << endl;     // "a"
    cout << sol.longestPalindrome("ac") << endl;    // "a" 或 "c"
    cout << sol.longestPalindrome("racecar") << endl; // "racecar"
    return 0;
}