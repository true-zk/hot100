/*
    76. 最小覆盖子串
    hard
    给你一个字符串 s 、一个字符串 t 。
    返回 s 中涵盖 t 所有字符的最小子串。如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 。

    子串->滑窗 （和9.findAnagrams有点像，也是从s中找符合的子串）
    初始l=r=0
    - 不符合：r++扩展窗口，直到符合
    - 符合：l++收缩窗口，直到不符合
    - 到r到尾，并且l不能再收缩就结束了
*/

#include <string>
#include <iostream>
#include <unordered_map>

using namespace std;


// 先找到滑窗右边界，
// 然后收缩左边，直到不能覆盖，记录一次minres
// 然后再往右划
class Solution {
    unordered_map<char, int> tmap, windowmap;
    // O(n)的检测
    bool ifCovered() {
        for (auto &el: tmap) {
            if (windowmap[el.first] < el.second) {
                return false;
            }
        }
        return true;
    }
public:
    string minWindow(string s, string t) {
        // 统计t中每个字母的频次，用于检测覆盖
        for (char &c: t) {
            ++tmap[c];
        }
        
        int n = s.size();
        int left = 0;  // 滑窗左点
        int resl = -1, resr = n;  // 初始应该是不可能的值，resr - resl = n + 1

        for (int right = 0; right < n; ++right) {
            windowmap[s[right]]++;  // 将右端点移入window
            while (ifCovered())     // if window中覆盖t，判断res，收缩左侧
            {
                if(right - left < resr - resl) {
                    resr = right;
                    resl = left;
                }
                windowmap[s[left]]--;  // 收缩
                left++;
            }
            // 直到不能覆盖
        }
        
        // 处理特殊情况
        if (resl == -1) {  // 从没覆盖，返回空
            return "";
        }

        return s.substr(resl, resr - resl + 1);
    }
};


// 搜索是否覆盖的复杂度是O(n)，可以优化成O(1)，即只考虑变化量
// 记录windows和tmap的差，==0相等，如果变1，考虑怎么变的


int main() {
    Solution sol;
    cout << sol.minWindow("ADOBECODEBANC", "ABC") << endl; // "BANC"
    cout << sol.minWindow("a", "a") << endl;               // "a"
    cout << sol.minWindow("a", "aa") << endl;              // ""
    cout << sol.minWindow("ab", "b") << endl;              // "b"
    cout << sol.minWindow("bba", "ab") << endl;            // "ba"
    return 0;
}