/*
    3541. 找到频率最高的元音和辅音
    easy
    给你一个由小写英文字母（'a' 到 'z'）组成的字符串 s。
    你的任务是找出出现频率 最高 的元音（'a'、'e'、'i'、'o'、'u' 中的一个）和出现频率最高的辅音（除元音以外的所有字母），并返回这两个频率之和
*/
#include <string>
#include <iostream>
#include <unordered_set>

using namespace std;


class Solution {
public:
    unordered_set<int> vowels = {'a' - 'a', 'e' - 'a', 'i' - 'a', 'o' - 'a', 'u' - 'a'};

    int maxFreqSum(string s) {
        int max_n_v = 0, max_n_c = 0;
        int arr_n[26] = {0};
        for (char c: s) {
            ++arr_n[c - 'a'];
        }
        for (int i = 0; i < 26; ++i) {
            if (vowels.count(i) && arr_n[i] > max_n_v) {
                max_n_v = arr_n[i];
            }
            else if (!vowels.count(i) && arr_n[i] > max_n_c) {
                max_n_c = arr_n[i];
            }
        }

        return max_n_v + max_n_c;
    }
};


int main() {
    Solution sol;
    string s;

    s = "successes";
    cout << sol.maxFreqSum(s) << endl;

    s = "aeiaeia";
    cout << sol.maxFreqSum(s) << endl;

    return 0;
}