/*
    438. 找到字符串中所有字母异位词
    medium
    给定两个字符串 s 和 p，找到 s 中所有 p 的 异位词 的子串，
    返回这些子串的起始索引。不考虑答案输出的顺序。

    s = "cbaebabacd", p = "abc"
    res: [0,6]

    滑窗：
    用vector维护每个词在p中的次数，
    构造一个长度和p一致的滑窗，如果滑窗内的词的次数和p一致，就是答案
    不断移动滑窗来判断结果（同时左--右++）

    其实只要左就行，right = left + p的长度

    优化：
    这种判断两个字符串一不一样的问题，可以用差来O（1）判断：
    维护差值的vector，count[i]：
        初始，p中的使得count[p[i] - 'a']--
        s中的使得count[s[i] - 'a']++，
    维护相差的数量 diff = count[i]中不是0的数量

    如果diff == 0，则完全一致

    如果从不同变得相同：即count[p[left]]--之前是1，或者count[p[right]]++之前是-1，那么diff--
    如果从相同变得不同：即count[p[left]]--和count[p[right]]++之前是0，那么diff++
*/

#include <vector>
#include <string>
// #include <unordered_map>
#include <array>

using std::vector;
using std::string;
// using std::unordered_map;
using std::array;


class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> res;
        int n_p = p.size(), n_s = s.size();

        if (n_p > n_s) {
            return res;
        }

        array<int, 26> p_cnt {}, s_cnt {};

        for (int i = 0; i < n_p; i++) {
            ++p_cnt[p[i] - 'a'];
            ++s_cnt[s[i] - 'a'];
        }

        for (auto ri = s.begin() + n_p; ri != s.end(); ++ri) {
            if (p_cnt == s_cnt) {
                res.push_back((ri - s.begin() - n_p));
            }

            ++s_cnt[*ri - 'a'];
            --s_cnt[*(ri - n_p) - 'a'];
        }

        if (p_cnt == s_cnt) {
            res.push_back(n_s - n_p);
        }

        return res;

    }
};


class Solution2 {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> res;
        int n_p = p.size(), n_s = s.size();

        if (n_p > n_s) {
            return res;
        }

        array<int, 26> diff {};
        int n_diff = 0;

        for (int i = 0; i < n_p; ++i) {
            ++diff[p[i] - 'a'];
            --diff[s[i] - 'a'];
        }

        for (int i = 0; i < 26; ++i) {
            if (diff[i]) {
                ++n_diff;
            }
        }

        for (int i = 0; i < (n_s - n_p); ++i) {
            if (n_diff == 0) {
                res.push_back(i);
            }

            int &tmpl = diff[s[i] - 'a'];
            int &tmpr = diff[s[i + n_p] - 'a'];
            if (tmpl == 0) {
                ++n_diff;
            }
            else if (tmpl == -1) {
                --n_diff;
            }
            ++tmpl;

            if (tmpr == 0) {
                ++n_diff;
            }
            else if (tmpr == 1) {
                --n_diff;
            }
            --tmpr;
        }

        // post process
        if (n_diff == 0){
            res.push_back(n_s - n_p);
        }

        return res;
    }
};