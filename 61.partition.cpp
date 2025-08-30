/*
    medium
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <algorithm>

using namespace std;


// 每次选择第一个部分，然后开始对后面的部分迭代，
// 注意到，后面的部分的分割可能涉及重复计算，可以缓存
// aaabbb， a,a,(abbb) 和 aa,(abbb)的(abbb)的处理是一样的
class Solution {
public:
    bool isPalindrome(string &s) {
        int i = 0, j = s.size() - 1;
        while (i < j)
        {
            if (s[i] != s[j]) return false;
            ++i;
            --j;
        }
        return true;
    }

    void backtrack(vector<vector<string>> &res, vector<string> &tmp, string &s, int i) {
        // 到尾后，完成了遍历
        if (i == s.size()) {
            res.emplace_back(tmp);
            return;
        }

        for (int k = i; k < s.size(); ++k) {
            string newcase = s.substr(i, k - i + 1); // pos, len
            if (isPalindrome(newcase)) {  // 保证是回文串才加入tmp，不然跳过
                tmp.emplace_back(newcase);
                backtrack(res, tmp, s, k + 1);  // 从i到k都被选了，跳到k+1
                tmp.pop_back();  // 回溯，去掉这种选择继续
            }
        }
    }

    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        vector<string> tmp;
        backtrack(res, tmp, s, 0);
        return res;
    }
};


// 优化：记忆化
// 注意到1里面，对回文子串的判断有冗余，相同的字串部分如果判断过就不必再次判断
// 可以用ij标记字串位置，如果已经判断过就返回之前判断的结果 
class Solution2 {
public:

    bool isPalindrome(string &s, vector<vector<int>> &visited, int i, int j) {
        if (visited[i][j] != 0) {
            return visited[i][j] == 1;  // 1是回文 2不是
        }
        else {
            // 利用记忆化，这里也递归判断
            // 当前i j 位置相等，而且[i-1, j-1]是回文，则是回文
            if (i >= j ) {  // 奇数偶数边界
                visited[i][j] = 1;
                return true;
            }
            else {
                bool curvalid = isPalindrome(s, visited, i + 1, j - 1) && s[i] == s[j];
                visited[i][j] = curvalid ? 1 : 2;
                return curvalid;
            }
        }
    }

    void backtrack(vector<vector<string>> &res, vector<string> &tmp, string &s, int i, vector<vector<int>> &visited) {
        // 到尾后，完成了遍历
        if (i == s.size()) {
            res.emplace_back(tmp);
            return;
        }

        for (int k = i; k < s.size(); ++k) {
            // string newcase = s.substr(i, k - i + 1); // pos, len
            if (isPalindrome(s, visited, i, k)) {  // 保证是回文串才加入tmp，不然跳过
                tmp.emplace_back(s.substr(i, k - i + 1));
                backtrack(res, tmp, s, k + 1, visited);  // 从i到k都被选了，跳到k+1
                tmp.pop_back();  // 回溯，去掉这种选择继续
            }
        }
    }

    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        vector<string> tmp;
        vector<vector<int>> visited(s.size(), vector<int> (s.size(), 0));  // 0 表示没访问，1 表示回文，2 表示非回文
        backtrack(res, tmp, s, 0, visited);
        return res;
    }
};


// 还有种优化，先把所有回文串求出来，如果isPlindrome[i][j] true是回文，false不是回文
// 这样可以O(1)判断是不是回文
class Solution3 {
public:
    // 换种写法，写成成员变量
    vector<vector<string>> res;
    vector<string> tmp;
    vector<vector<int>> isPalindrome;

    void dfs(string &s, int i, int n) {
        if (i == n) {
            res.emplace_back(tmp);
            return;
        }
        else {
            for (int j = i; j < n; ++j) {
                if (isPalindrome[i][j]) {
                    tmp.emplace_back(s.substr(i, j - i + 1));
                    dfs(s, j + 1, n);
                    tmp.pop_back();
                }
            }
        }
        
    }

    vector<vector<string>> partition (string s) {
        int n = s.size();
        isPalindrome.resize(n, vector<int>(n, 1));  // 边界是true
        res.clear();

        // 预处理所有回文子串
        // DP: f[i][j] == f[i + 1]f[j - 1] && s[i] == s[j]
        // 所以要递推的话，要倒序处理，从i最大和j最小开始
        for (int i = n - 1; i >= 0; --i) {
            for (int j = i + 1; j < n; ++j) {
                isPalindrome[i][j] = isPalindrome[i + 1][j - 1] && s[i] == s[j];
            }
        }

        dfs(s, 0, n);
        return res;
    }
};


void printres(vector<vector<string>> &res) {
    cout << "[";
    for (auto &resl: res) {
        cout << "[";
        for (auto &s: resl) {
            cout << s;
            cout << ((s == *(resl.end() - 1)) ? "" : ",");
        }
        cout << "]";
        cout << ((resl == *(res.end() - 1)) ? "" : ",");
    }
    cout << ']';
    cout << endl;
}


int main() {
    Solution3 sol;
    string s = "aab";
    vector<vector<string>> res;

    res = sol.partition(s);
    printres(res);

    return 0;
}