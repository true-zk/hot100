/*
    medium
*/
#include <string>
#include <stack>
#include <vector>
#include <limits>
#include <iostream>
#include <algorithm>

using namespace std;


class Solution {
public:
    // 引用 实际更新i
    string decodeNum(string &s, int &i) {
        string res = "";
        while (s[i] >= '0' && s[i] <= '9')
        {
            res += s[i];
            ++i;
        }
        return res;
    }

    string decodeString(string s) {
        vector<string> stk;
        int i = 0;
        while (i < s.size())
        {
            char cur = s[i];
            if (cur >= '0' && cur <= '9') {
                stk.push_back(decodeNum(s, i));
            }
            else if ((cur >= 'a' && cur <= 'z') || cur == '[') {
                stk.emplace_back(1, s[i]);  // string和vector构造是先n后char
                ++i;
            }
            // cur == ']' 出栈
            else {
                ++i;
                vector<string> tmp;
                // 直到遇到 '['
                while (stk.back() != "[")
                {
                    tmp.push_back(stk.back());
                    stk.pop_back();
                }
                stk.pop_back(); // 把 '[' 出栈，然后一定是一个num
                int repeat = stoi(stk.back());  // stoi(string) -> int
                stk.pop_back(); // 出栈这个num
                // 倒序的tmp才是正常的顺序
                reverse(tmp.begin(), tmp.end());  // in #include <algorithm>
                string tmps = "", tmpres = "";
                for (auto &s: tmp) {
                    tmps += s;
                }
                for (int j = 0; j < repeat; ++j) {
                    tmpres += tmps;
                }
                stk.push_back(tmpres);
            }
        }
        string res = "";
        for (auto &s: stk) {
            res += s;
        }
        return res;
    }
};


int main() {
    Solution sol;
    cout << sol.decodeString("4[2[jk]e1[f]]") << endl;  return 0;
    cout << sol.decodeString("3[a]2[bc]") << endl;        // aaabcbc
    cout << sol.decodeString("3[a2[c]]") << endl;         // accaccacc
    cout << sol.decodeString("2[abc]3[cd]ef") << endl;    // abcabccdcdcdef
    cout << sol.decodeString("abc3[cd]xyz") << endl;      // abccdcdcdxyz
    return 0;
}