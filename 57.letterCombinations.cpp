/*
    medium
    回溯模板题
*/
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;


class Solution {
public:

    unordered_map<char, vector<char>> codebook {
        {'2', {'a', 'b', 'c'}},
        {'3', {'d', 'e', 'f'}},
        {'4', {'g', 'h', 'i'}},
        {'5', {'j', 'k', 'l'}},
        {'6', {'m', 'n', 'o'}},
        {'7', {'p', 'q', 'r', 's'}},
        {'8', {'t', 'u', 'v'}},
        {'9', {'w', 'x', 'y', 'z'}},
    };

    void backtrack(vector<string> &res, string &curres, string &digits, int &targetl, int curl) {
        if (curl == targetl) {
            res.push_back(curres);
            return;
        }

        for (auto el: codebook[digits[curl]]) {
            curres += el;
            backtrack(res, curres, digits, targetl, curl + 1);
            curres.pop_back();
        }
    }

    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};
        vector<string> res;
        string curres;
        int n = digits.size();
        backtrack(res, curres, digits, n, 0);
        return res;
    }
};


int main() {
    string digits = "23";
    Solution sol;
    auto res = sol.letterCombinations(digits);
    for (auto el: res) {
        cout << el << ' ';
    }
    cout << endl;
    return 0;
}