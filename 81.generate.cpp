/*
    easy
    最典型的dp
*/
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        if (numRows == 1) return vector<vector<int>> {{1}};
        vector<vector<int>> res;
        res.push_back({1});
        res.push_back({1, 1});
        for (int i = 3; i <= numRows; ++i) {
            vector<int> cur(i, 1);
            for (int j = 1; j < i - 1; ++j) {
                cur[j] = res.back()[j-1] + res.back()[j];
            }
            res.push_back(cur);
        }
        return res;
    }
};


void printRes(vector<vector<int>> res) {
    for (auto &l: res) {
        cout << "[";
        for (int &x: l) {
            cout << x << ",";
        }
        cout << "], ";
    }
    cout << endl;
}


int main() {
    Solution sol;
    printRes(sol.generate(1));
    printRes(sol.generate(2));
    printRes(sol.generate(5));
    return 0;
}