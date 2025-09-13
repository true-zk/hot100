/*
    3227. 字符串元音游戏
    medium

    小红和小明在玩一个字符串元音游戏。

    给你一个字符串 s，小红和小明将轮流参与游戏，小红 先 开始：

    在小红的回合，她必须移除 s 中包含 奇数 个元音的任意 非空 子字符串。
    在小明的回合，他必须移除 s 中包含 偶数 个元音的任意 非空 子字符串。
    第一个无法在其回合内进行移除操作的玩家输掉游戏。假设小红和小明都采取 最优策略 。

    如果小红赢得游戏，返回 true，否则返回 false。

    英文元音字母包括：a, e, i, o, 和 u。
*/
#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;


// 智力题，只要有元音，必然小红赢
class Solution {
public:
    bool doesAliceWin(string s) {
        unordered_set<char> vowel_set = {'a', 'e', 'i', 'o', 'u'};
        for (auto c: s) {
            if (vowel_set.count(c)) {
                return true;
            }
        }
        return false;
    }
};


int main() {
    Solution sol;
    cout << boolalpha << sol.doesAliceWin("leetcoder") << endl;      // true
    cout << boolalpha << sol.doesAliceWin("bbcd") << endl;      // false
    return 0;
}