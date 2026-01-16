/*
    medium
    回溯模板题
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;


class Solution {
public:
    // 仍然是选与不选的问题，对当前节点，要么选，要么不选，不选就跳到下个节点
    void backtrack(vector<vector<int>> &res, vector<int> &tmp, vector<int> &cans, int target, int idx) {
        if (idx == cans.size()) return;
        if (target == 0) {
            res.emplace_back(tmp);
            return;
        }
        // 1. 不选，跳到下个点
        backtrack(res, tmp, cans, target, idx + 1);
        // 2. 选
        if (target - cans[idx] >= 0) {
            tmp.emplace_back(cans[idx]);  // 加入到tmp
            backtrack(res, tmp, cans, target - cans[idx], idx);  // 仍然是idx，因为当前节点可以重复选
            tmp.pop_back();  // 同样，递归完选择的情况得pop
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        vector<int> tmp;
        backtrack(res, tmp, candidates, target, 0);
        return res;
    }
};


void print2DVec(const vector<vector<int>>& res) {
    for (const auto& v : res) {
        cout << "[";
        for (int i = 0; i < v.size(); ++i) {
            cout << v[i];
            if (i + 1 < v.size()) cout << ",";
        }
        cout << "] ";
    }
    cout << endl;
}


int main() {
    Solution sol;
    vector<vector<int>> res;

    vector<int> cans = {2, 3, 6, 7};
    int target = 7;
    res = sol.combinationSum(cans, target);
    print2DVec(res);
    return 0;
}