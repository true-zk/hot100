/*
    1935. 可以输入的最大单词数
    easy

    给你一个由若干单词组成的字符串 text ，
    单词间由单个空格组成（不含前导和尾随空格）；另有一个字符串 brokenLetters ，由所有已损坏的不同字母键组成，
    返回你可以使用此键盘完全输入的 text 中单词的数目。
*/
#include <string>
#include <unordered_set>
#include <iostream>

using namespace std;


class Solution {
public:
    int canBeTypedWords(string text, string brokenLetters) {
        int res = 0;
        int n = text.size();
        unordered_set<char> broken_set;
        for (auto &c: brokenLetters) {
            broken_set.insert(c);
        }

        for (int i = 0; i < n; ++i) {
            if (broken_set.count(text[i])) {
                while (i < n && text[i] != ' ') {
                    ++i;
                }
                // text[i] = ' '
                continue;
            }
            else if (text[i] == ' ' || i == n - 1) {
                ++res;
                continue;
            }
        }
        return res;
    }
};


int main() {
    Solution sol;
    cout << sol.canBeTypedWords("hello world", "ad") << endl;         // 1
    cout << sol.canBeTypedWords("leet code", "e") << endl;            // 0
    cout << sol.canBeTypedWords("leet code", "lt") << endl;           // 1
    cout << sol.canBeTypedWords("a b c", "z") << endl;                // 3
    cout << sol.canBeTypedWords("abc def ghi", "a") << endl;          // 2
    cout << sol.canBeTypedWords("abc def ghi", "adg") << endl;        // 0
    return 0;
}