/*
    2785. 将字符串中的元音字母排序
    给你一个下标从 0 开始的字符串 s ，将 s 中的元素重新 排列 得到新的字符串 t ，它满足：
    所有辅音字母都在原来的位置上。更正式的，如果满足 0 <= i < s.length 的下标 i 处的 s[i] 是个辅音字母，那么 t[i] = s[i] 。
    元音字母都必须以他们的 ASCII 值按 非递减 顺序排列。更正式的，对于满足 0 <= i < j < s.length 的下标 i 和 j  ，如果 s[i] 和 s[j] 都是元音字母，那么 t[i] 的 ASCII 值不能大于 t[j] 的 ASCII 值。
    请你返回结果字母串。
    元音字母为 'a' ，'e' ，'i' ，'o' 和 'u' ，它们可能是小写字母也可能是大写字母，辅音字母是除了这 5 个字母以外的所有字母。
*/
#include <string>
#include <vector>
#include <unordered_set>
#include <iostream>
#include <algorithm>

using namespace std;


// 朴素想法：把元音挑出来，然后排序，插回去
class Solution {
public:
    unordered_set<char> vowels_set = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
    string sortVowels(string s) {
        int n = s.size();
        vector<char> vowels;
        vector<int> vowel_index;
        for (int i = 0; i < n; ++i) {
            if (vowels_set.count(s[i])) {
                vowels.push_back(s[i]);
                vowel_index.push_back(i);
            }
        }

        sort(vowels.begin(), vowels.end());

        for (int i = 0; i < vowels.size(); ++i) {
            s[vowel_index[i]] = vowels[i];
        }

        return s;
    }
};


// 优化到O(n)
// 桶排序，元素的可能性是已知的，直接计数每个元素有几个元素就行
class Solution2 {
public:
    unordered_set<char> vowels_set = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
    vector<char> vowels_l = {'A', 'E', 'I', 'O', 'U', 'a', 'e', 'i', 'o', 'u'};
    int vowel2Index(char c) {
        for (int i = 0; i < 10; ++i) {
            if (vowels_l[i] == c) {
                return i;
            }
        }
        return -1;
    }

    string sortVowels(string s) {
        vector<int> vowels_cnt(10, 0);

        for (const char &c: s) {
            if (vowels_set.count(c)) {  // is vowel
                ++vowels_cnt[vowel2Index(c)];
            }
        }

        int vowel_idx = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (vowels_set.count(s[i])) {
                while (vowels_cnt[vowel_idx] <= 0)
                {
                    ++vowel_idx;
                }
                s[i] = vowels_l[vowel_idx];
                --vowels_cnt[vowel_idx];
            }
        }
        return s;
    }
};


int main() {
    Solution2 sol;
    cout << sol.sortVowels("lEetcOde") << endl;      // "lEOtcede"
    cout << sol.sortVowels("hello") << endl;         // "holle"
    cout << sol.sortVowels("aeiou") << endl;         // "aeiou"
    cout << sol.sortVowels("AEIOU") << endl;         // "AEIOU"
    cout << sol.sortVowels("programming") << endl;   // "prigrammong"
    cout << sol.sortVowels("xyz") << endl;           // "xyz"
    return 0;
}
