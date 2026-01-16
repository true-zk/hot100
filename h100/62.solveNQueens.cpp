/*
    hard
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <algorithm>

using namespace std;


// 总体上是回溯
// 另外如果每次遍历判断能不能放皇后会很慢，所以要优化，这里用集合优化
/*
    n个皇后，n*n的格子：显然每行只能放一个，所以可以按行进行递归
*/
class Solution {
public:

    vector<string> generatedBoard(vector<int> &queensidx, int n) {
        vector<string> board{};
        for (int i = 0; i < n; ++i) {
            string row = string(n, '.');
            row[queensidx[i]] = 'Q';
            board.emplace_back(row);
        }
        return board;
    }

    void backtrack(
        vector<vector<string>> &res,
        vector<int> &queenidx,       // 存每一行中的皇后的colidx
        unordered_set<int> &cols,    // 列
        unordered_set<int> &diags1,  // 主对角线
        unordered_set<int> &diags2,  // 副对角线
        int rowidx,  // 按行递归
        int n
    ) {
        // 边界，皇后全部放好了
        if (rowidx == n) {
            res.emplace_back(generatedBoard(queenidx, n));
        }
        // 对当前行，遍历每一列，check哪些位置可以放皇后，对能放的进行递归，然后回溯
        for (int colidx = 0; colidx < n; ++colidx) {
            if (cols.count(colidx) != 0) continue;
            if (diags1.count(rowidx - colidx) != 0) continue;
            if (diags2.count(rowidx + colidx) != 0) continue;
            // 递归
            queenidx.push_back(colidx);
            cols.insert(colidx);
            diags1.insert(rowidx - colidx);
            diags2.insert(rowidx + colidx);
            backtrack(res, queenidx, cols, diags1, diags2, rowidx + 1, n);
            // 回溯
            queenidx.pop_back();
            cols.erase(colidx);
            diags1.erase(rowidx - colidx);
            diags2.erase(rowidx + colidx);
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        vector<int> queensidx;
        // 用来优化判断可不可以放皇后
        /*
            每次放一个皇后，更新三个集合，把不能放皇后的位置放到三个集合中；
            cols中就是加入行列，
            diags1放主对角线的值，特征：i - j 一致
            diags2放副对角线的值，特征：i + j 一致
        */
        unordered_set<int> cols;
        unordered_set<int> diags1;
        unordered_set<int> diags2;
        backtrack(res, queensidx, cols, diags1, diags2, 0, n);
        return res;
    }
};


void printres(vector<vector<string>> &res) {
    cout << '[';
    for (auto &resl: res) {
        cout << '[';
        for (auto &el: resl) {
            cout << "\"" << el << "\"";
            cout << (el == *(resl.end() - 1) ? ", ": "");
        }
        cout << "]";
        cout << (resl == *(res.end() - 1) ? ", ": "");
    }
    cout << "]" << endl;
}


int main() {
    int n = 4;
    Solution sol;

    auto res = sol.solveNQueens(n);
    printres(res);

    return 0;
}