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

        // for (int i = 0; i < (n_s - n_p); ++i) {
        //     if (n_diff == 0) {
        //         res.push_back(i);
        //     }

        //     if (diff[s[i] - 'a'] == 0) {
        //         ++n_diff;
        //     }
        //     else if (diff[s[i] - 'a'] == -1) {
        //         --n_diff;
        //     }
        //     ++diff[s[i] - 'a'];

        //     if (diff[s[i + n_p] - 'a'] == 0) {
        //         ++n_diff;
        //     }
        //     else if (diff[s[i + n_p] - 'a'] == 1) {
        //         --n_diff;
        //     }
        //     --diff[s[i + n_p] - 'a'];
        // }

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