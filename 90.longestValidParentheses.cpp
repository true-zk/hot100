/*
    hard
*/
#include <vector>
#include <stack>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <limits>

using namespace std;


// 递归解
/*
    dp[i] = 以i结尾 的最长有效括号长度
    - '(' 一定是0
    - ')' 
        - i-1 是 '('，遇到 ...() 情况 ，直接 dp[i] = dp[i-2] + 2
        - i-1 是 ')', 遇到 ...)) 情况 ，依赖dp[i-1]的情况：
            有可能前面恰好有多余'('可以和自己构成，
            如何找到可能多余的'('？ -> 如果存在，一定是...((...))，一定在前一个左括号的最大合法长度-1
            if j = i - dp[i-1] - 1 是'(':
                dp[i] = dp[i-1] + dp[i - dp[i-1] - 2] + 2
                                  这里是加上在 j的'('之前的合法最大长度
            else j = i - dp[i-1] - 1 是')':
                说明是...)(...))，dp[i] = 0
*/
class Solution {
public:
    int longestValidParentheses(string s) {
        if (s.size() == 0) return 0;
        int n = s.size();
        vector<int> dp(n, 0);
        int res = 0;  // 额外维护最长值，因为结果不一定在最后一个位置
        for (int i = 1; i < n; ++i) {
            if (s[i] == ')')  {  // == ')'
                if (s[i - 1] == '(') {  // ...()
                    dp[i] = (i >= 2) ? dp[i - 2] + 2 : 2;  // 防止越界
                }
                else {      // ...))
                    int j = i - dp[i - 1] - 1;  // 前一个最长有效串的 前一个位置
                    if (j >= 0 && s[j] == '(') {  // ...'('(...))
                        dp[i] = (j - 1 >= 0 ? dp[j - 1] : 0) + 2 + dp[i - 1];
                    }
                }
                res = max(res, dp[i]);
            }
        }
        return res;
    }
};


// 注意到直接遇到')'就匹配不行，
// 因为有()()的情况，如果把第一个(匹配走了，会以为最大长度重新开始，maxlen还是2
// 为了处理这种连续的情况，在栈底加入最前面(的左侧的idx，也就是前面最后一个 多余)
class Solution2 {
public:
    int longestValidParentheses(string s) {
        if (s.size() == 0) return 0;
        int n = s.size();
        stack<int> stk;
        stk.push(-1);  // 刚开始没有最后一个 多余')'，加入-1作为哨兵
        int res = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '(') {
                stk.push(i);
            }
            else {  // == ')'
                stk.pop();  // 先出栈一个元素
                if (stk.empty()) {  // 说明之前只有最后一个多余')'，说明没有匹配的'('，新的')'作为最后一个多余')'
                    stk.push(i);
                }
                else {  // 正常匹配，长度 = i - 最后一个多余')' or i - 前一个( ;; 注意，这里栈顶无论如何都是应该匹配的'('的前一个，恰好不用+1
                    res = max(res, i - stk.top());  // -1处理了边界
                }
            }
        }
        return res;
    }
};


// 神秘双向贪心
// 从左到右维护numl和numr，当numl == numr记录结果
// 如果numr > numl，说明遇到 ())，前面都不再合法，numl=numr=0归零
// 但是上述过程漏掉了numl 永远> numr的情况： (()
// 再从右往左遍历，反转条件就可以
class Solution3 {
public:
    int longestValidParentheses(string s) {
        if (s.size() == 0) return 0;
        int n = s.size();
        int res = 0;
        int numl = 0, numr = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '(') ++numl;
            if (s[i] == ')') ++numr;

            if (numl == numr) res = max(res, numl * 2);
            else if (numl < numr) {  // ())...
                numl = numr = 0;
            }
        }
        numl = numr = 0;
        for (int i = n - 1; i >= 0; --i) {
            if (s[i] == ')') ++numr;
            if (s[i] == '(') ++numl;

            if (numl == numr) res = max(res, numl * 2);
            else if (numl > numr) {  // ...(()
                numl = numr = 0;
            }
        }
        return res;
    }
};


int main () {
    Solution3 sol;
    cout << sol.longestValidParentheses("(()") << endl;         // 2
    cout << sol.longestValidParentheses(")()())") << endl;      // 4
    cout << sol.longestValidParentheses("") << endl;            // 0
    cout << sol.longestValidParentheses("()(()") << endl;       // 2
    cout << sol.longestValidParentheses("()(())") << endl;      // 6
    cout << sol.longestValidParentheses(")()())()()(") << endl; // 4
    return 0;
}