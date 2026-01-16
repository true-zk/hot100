/*
    medium
    dp
*/
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <limits>

using namespace std;


class Solution {
public:
    bool subword(string &s, int end, string &word) {
        int n = word.size();
        if (n > end + 1) return false;

        for (int i = 0; i < n; ++i) {
            if (word[n - i - 1] != s[end - i]) return false;
        }
        return true;
    }

    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.size();
        vector<int> dp(n + 1, 0);
        dp[0] = 1;  // 恰好到0是valid的
        for (int i = 0; i < n; ++i) {
            int valid = 0;
            for (auto &word: wordDict) {
                int wordn = word.size();
                if ( i + 1 - wordn >= 0 && dp[i + 1 - wordn]) {
                    valid = valid || subword(s, i, word);
                }
                // valid = valid || (dp[i + 1 - wordn] && subword(s, i, word));
            }
            dp[i + 1] = valid;
        }
        return dp[n];
    }
};


int main() {
    string s;
    vector<string> worddict;
    Solution sol;

    s = "abpenab";
    worddict = {"ab", "pen"};
    cout << sol.wordBreak(s, worddict) << endl;

    s = "applepenapple";
    worddict = {"apple", "pen"};
    cout << sol.wordBreak(s, worddict) << endl;

    return 0;
}