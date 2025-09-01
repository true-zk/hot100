/*
    hard!
    编辑距离
*/
#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>


using namespace std;


/*
    只从尾开始考虑 （顺序不敏感）
    s: horse
    t: ros
    - 如果尾一样，都去掉
    - 否则，从下面选项中选择编辑距离最短的 + 1：dp[i][j] = min (s插入，s删除，s替换) + 1
        - s插入字符，肯定插入一样的(ros -> rose)，所以和插入后，把两个尾都去掉一样，= 直接删除t尾
        - s删除字符，删s尾
        - s替换字符，替换s尾，肯定替换一样的，= 同时删去s和t的尾
*/
// dp[i][j] = word1[0:i]和word[0:j]的编辑距离
class Solution {
public:
    int minDistance(string word1, string word2) {
        int n1 = word1.size(), n2 = word2.size();
        // 多1 处理边界
        vector<vector<int>> dp (n1 + 1, vector<int> (n2 + 1, 0));
        // 边界：当word2为空，编辑距离就是word1长度，反之亦然
        // dp[0][0] = 0;
        for (int i = 0; i < n1 + 1; ++i) {  // word2空，为word1长度
            dp[i][0] = i;
        }
        for (int j = 0; j < n2 + 1; ++j) {  // word1空，为word2长度
            dp[0][j] = j;
        }

        for (int i = 0; i < n1; ++i) {
            for (int j = 0; j < n2; ++j) {
                if (word1[i] == word2[j]) {
                    dp[i + 1][j + 1] = dp[i][j];
                }
                else {
                    dp[i + 1][j + 1] = min({
                        dp[i][j + 1],  // word1删
                        dp[i + 1][j],  // word1加  = word2删
                        dp[i][j]       // word1改  = 同时删
                    }) + 1;
                }
            }
        }

        return dp[n1][n2];
    }
};


int main() {
    Solution sol;
    cout << sol.minDistance("horse", "ros") << endl;      // 3
    cout << sol.minDistance("intention", "execution") << endl; // 5
    cout << sol.minDistance("abc", "yabd") << endl;       // 2
    cout << sol.minDistance("", "abc") << endl;           // 3
    cout << sol.minDistance("abc", "") << endl;           // 3
    cout << sol.minDistance("", "") << endl;              // 0
    return 0;
}