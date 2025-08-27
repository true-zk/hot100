#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <numeric>  // For accumulate

using namespace std;

// use sorted string as hash key
// O(Nklog(k))
class Solution1 {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> map;
        vector<vector<string>> res;
        for (const string& str: strs) {
            string sorted_str = str;
            sort(sorted_str.begin(), sorted_str.end());
            map[sorted_str].push_back(str);
        }
        for (const auto& pair : map) {
            res.push_back(pair.second);
        }
        return res;
    }
};

// use num of letters as hash key
// O(Nk)
class Solution2 {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        // self-deined hash function
        auto array_hash = [fn = hash<int>{}] (
            const array<int, 26>& arr
        ) -> size_t {
            return accumulate(
                arr.begin(),
                arr.end(),
                0,
                [&](size_t acc, int num) {
                    return (acc << 1) ^ fn(num);
                }   
            );
        };

        unordered_map<array<int, 26>, vector<string>, decltype(array_hash)> map(0, array_hash);
        vector<vector<string>> res;
        for (const string& str: strs) {
            array<int, 26> tmp_arr = {};
            for (const char c: str) {
                tmp_arr[c - 'a']++;
            }
            map[tmp_arr].push_back(str);
        }
        for (const auto& pair : map) {
            res.push_back(pair.second);
        }
        return res;
    }
};
