/*
    medium
    回溯模板题
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;


// 括号valid: 任意位置i，右括号数量 <= 左括号数量
// 回溯的选与不选：要么左 要么右括号
class Solution {
public:
    void backtrack(vector<string> &res, string &tmp, int len, int n, int numl, int numr) {
        if (numl < numr) return;  // invalid
        if (len == n) {
            if (numl == numr) {
                res.emplace_back(tmp);
            }
            return;
        }

        tmp.push_back('(');
        backtrack(res, tmp, len + 1, n, numl + 1, numr);
        tmp.pop_back();
        tmp.push_back(')');
        backtrack(res, tmp, len + 1, n, numl, numr + 1);
        tmp.pop_back();
    }

    vector<string> generateParenthesis(int n) {
        vector<string> res;
        string tmp;
        backtrack(res, tmp, 0, n * 2, 0, 0);
        return res;
    }
};


// 解法2，还有种想法，任何合法的序列应该确保每个左括号都有对应的右括号
// 递推定义合法性：(a)b 其中a和b也合法（递归生成）
class Solution2 {
public:

    vector<vector<string>> cache;  // 缓存每个长度的中间结果

    vector<string> recursiveGenerate(int n) {
        if (!cache[n].empty()) return cache[n];  // 【记忆化】如果已经构造好了n长度括号，返回（避免重复构造相同长度的括号）
        // 构造到n长度的括号
        if (n == 0) {
            cache[0] = vector<string> {""};
            return cache[0];
        }
        else
        {
            vector<string> tmpres;
            // 一共n个 = 'a'i个，'b'n - i - 1个，加上自身1个
            for (int i = 0; i < n; ++i) {
                vector<string> lefts = recursiveGenerate(i);
                vector<string> rights = recursiveGenerate(n - i - 1);
                for (const auto &left: lefts) {
                    for (const auto &right: rights) {
                        tmpres.emplace_back("(" + left + ")" + right);
                    }
                }
            }
            cache[n] = tmpres;  // 缓存结果 避免重复计算
            return tmpres;
        }
    }

    vector<string> generateParenthesis(int n) {
        cache.resize(100);
        return recursiveGenerate(n);
    }
};


void printres(vector<string> &res) {
    cout << '[';
    for (auto &el: res) {
        cout << el;
        cout << ((el == *(res.end() - 1)) ? "" : ",");
    }
    cout << ']' << endl;
}


int main() {
    Solution2 sol;
    int n = 3;
    vector<string> res = sol.generateParenthesis(n);
    printres(res);

    n = 1;
    res = sol.generateParenthesis(n);
    printres(res);
    return 0;
}