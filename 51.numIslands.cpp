/*
    medium
*/

#include <iostream>
#include <vector>
using namespace std;


class Solution {
public:
    int m;
    int n;

    // 递归将同一块陆地消除掉
    void recursiveRemoveland(vector<vector<char>> &grid, int x, int y) {
        if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] == '0') return;
        grid[x][y] = '0';
        recursiveRemoveland(grid, x - 1, y);
        recursiveRemoveland(grid, x + 1, y);
        recursiveRemoveland(grid, x, y - 1);
        recursiveRemoveland(grid, x, y + 1);
    }

    int numIslands(vector<vector<char>>& grid) {
        int res = 0;
        m = grid.size();
        n = grid[0].size();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '1') {
                    ++res;
                    recursiveRemoveland(grid, i, j);
                }
            }
        }
        return res;
    }
};


// 并查集
// 并查集适合联通分量的问题，恰好判断岛是这样的问题
class DSU {
public:
    // 初始化，刚开始每个根是自己
    DSU(vector<vector<char>> &grid) {
        count = 0;
        int m = grid.size();
        int n = grid[0].size();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                // Init parent vec, add each land to parent
                if (grid[i][j] == '1') {
                    parent.push_back(i * n + j);  // sequence index (unique)
                    ++count;
                }
                else {
                    parent.push_back(-1);  // water, add -1
                }
                rank.push_back(0);
            }
        }
    }

    // 找根，递归实现
    // 路径压缩优化：3-2-1-0，当第一次find(3)，会变成0-0-0-0
    // 下次find(3)，虽然还是进入递归，但是会直接到0，减少了递归次数
    int find(int i) {
        if (parent[i] != i) {
            parent[i] = find(parent[i]);  // 路径压缩
        }
        return parent[i];
    }

    // 合并岛屿
    void unite(int x, int y) {
        int rootx = find(x);
        int rooty = find(y);
        if (rootx != rooty) {
            if (rank[rootx] < rank[rooty]) {
                swap(rootx, rooty);
            }
            parent[rooty] = rootx;
            if (rank[rootx] == rank[rooty]) {
                rank[rootx] += 1;
            }
            --count;
        }
    }

    // 返回岛屿数量
    int getCount() {
        return count;
    }

private:
    vector<int> parent;
    vector<int> rank;  // 把低秩挂在高秩上防止退化成链
    int count;
};


class Solution2 {
public:
    int numIslands(vector<vector<char>> &grid) {
        if (!grid.size()) return 0;
        int m = grid.size(), n = grid[0].size();
        DSU dsu(grid);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '1') {
                    // grid[i][j] = 0;  // 同样遍历过的就变成'0'  // 这里其实不需要，但是写了也没关系，减少判断而已
                    if (i > 0 && grid[i - 1][j] == '1') dsu.unite(i * n + j, (i - 1) * n + j);
                    if (i < m - 1 && grid[i + 1][j] == '1') dsu.unite(i * n + j, (i + 1) * n + j);
                    if (j > 0 && grid[i][j - 1] == '1') dsu.unite(i * n + j, i * n + j -1);
                    if (j < n - 1 && grid[i][j + 1] == '1') dsu.unite(i * n + j, i * n + j + 1);
                }
            }
        }
        return dsu.getCount();
    }
};


int main() {
    // 测试用例
    vector<vector<char>> grid = {
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}
    };

    Solution2 sol;
    int res = sol.numIslands(grid);
    cout << "岛屿数量: " << res << endl; // 期望输出：3

    return 0;
}