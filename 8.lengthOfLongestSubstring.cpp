/*
    3. 无重复字符的最长子串
    medium
    给定一个字符串 s ，请你找出其中不含有重复字符的 最长 子串 的长度。

    滑窗的基本题
    left指向不重复子串开始的位置，right指向结束，
    
    每次left++, 开始枚举下一个开始位置，while不断移动right，用unordered_set记录不重复，
    出现重复就结束这次循环，继续下次循环（left++）

*/

#include <string>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if (s.size() == 0) {
            return 0;
        }

        unordered_set<char> word_set;
        int res = 0;
        auto right = s.cbegin();
        // word_set.insert(*right);

        for (auto left = s.cbegin(); left != s.end(); ++left) {
            while (right != s.end() && !word_set.count(*right)) {
                word_set.insert(*right);
                ++right;  // here, will cause the right iter points to the next word.
            }

            int tmp = right - left;
            if (tmp > res) {
                res = tmp;
            }
            word_set.erase(*left);

        }

        return res;
    }
};