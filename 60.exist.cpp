/*
    medium
    注意到细节，方法2visited的设置可以减少很多不必要的时间复杂度
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <algorithm>

using namespace std;


// 应该是对的，但是超时，有太多重复遍历
class Solution {
public:

    int Direct[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    bool dfsCheck(vector<vector<char>> &board, string &word, int x, int y, int curlen, unordered_set<int> &visited) {
        if (curlen == word.size()) {
            return board[x][y] == word[curlen - 1];
        }
        else if (board[x][y] != word[curlen - 1]){
            return false;
        }
        else {
            bool valid = false;
            int m = board.size(), n = board[0].size();
            for (auto &d: Direct) {
                int i = x + d[0], j = y + d[1];
                if (i >= 0 && i < m && j >= 0 && j < n && !visited.count(i * n + j)) {
                    visited.insert(i * n + j);
                    valid = valid || dfsCheck(board, word, i, j, curlen + 1, visited);  // 只要有一次valid就是valid
                    visited.erase(i * n + j);  // 完成尝试后，重新变成没访问过，不然后面不能再访问了
                }
            }
            return valid;
        }
    }

    bool exist(vector<vector<char>>& board, string word) {
        // vector<pair<int, int>> cans;
        int m = board.size(), n = board[0].size();
        int lenw = word.size();
        bool valid = false;
        unordered_set<int> visited;  // 每个节点只能用一次，所以要标记已经走过的部分
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == word[0]) {
                    visited.clear();
                    visited.insert(i * n + j);
                    valid = valid || dfsCheck(board, word, i, j, 1, visited);
                }
            }
        }
        return valid;
    }
};


// 思路一致，稍微优化一下时间复杂度
class Solution2 {
public:

    int Direct[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    bool dfsCheck(vector<vector<char>> &board, string &word, vector<vector<int>> &visited, int x, int y, int curlen) {
        if (board[x][y] != word[curlen - 1]) return false;
        else if (curlen == word.size()) return true;

        // 当前位置相等，并且还没到word.size()
        visited[x][y] = 1;  // visit
        int m = board.size(), n = board[0].size();
        for (const auto &d: Direct) {
            int i = x + d[0], j = y + d[1];
            if (i >= 0 && i < m && j >= 0 && j < n && visited[i][j] == 0 && 
                dfsCheck(board, word, visited, i, j, curlen + 1)) {
                return true;  // valid直接提前结束就行
            }
        }
        visited[x][y] = 0;  // 结束当前尝试后还原
        return false;  // 结束尝试如果没有返回true, 显然没有合适结果，返回false
    }

    bool exist(vector<vector<char>> &board, string word) {
        int m = board.size(), n = board[0].size();
        vector<vector<int>> visited(m, vector<int>(n));  // 等大小的visited数组
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == word[0] && dfsCheck(board, word, visited, i, j, 1)) {
                    return true;
                }
            }
        }
        return false;
    }
};


int main() {
    Solution2 sol;
    vector<vector<char>> board = {
        {'A','B','C','E'},
        {'S','F','C','S'},
        {'A','D','E','E'}
    };

    cout << boolalpha << sol.exist(board, "ABCCED") << endl; // true
    cout << boolalpha << sol.exist(board, "SEE") << endl;    // true
    cout << boolalpha << sol.exist(board, "ABCB") << endl;   // false

    board = {
        {'A','B'},
        {'C','D'}
    };
    cout << boolalpha << sol.exist(board, "CDBA") << endl; // true

    return 0;
}