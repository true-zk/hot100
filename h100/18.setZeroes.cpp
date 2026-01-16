/*
    73. 矩阵置零
    medium

    给定一个 m x n 的矩阵，如果一个元素为 0 ，则将其所在行和列的所有元素都设为 0 。
    请使用 原地 算法。

    借用第一行和第一列来标记是不是0
*/


#include <vector>
#include <algorithm>
#include <iostream>

using std::vector;

/*
Limitation: O(1) space complexity
1 <= m, n <= 200
*/

// 最直接的方案，记录行，列中的0
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<int> row0(m, 0);
        vector<int> col0(n, 0);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == 0) {
                    row0[i] = 1;
                    col0[j] = 1;
                }
            }
        }
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j) {
                if (row0[i] == 1 || col0[j] == 1) {
                    matrix[i][j] = 0;
                }
            }
        }
    }
};


// 为了节省空间，和上一题一样的思路，把原来的数组的第一行和第一列作为标记
// 为了记录原来第一行和第一列中有没有0，用额外的flag记录一下
class Solution2 {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        int flag_r0 = 0, flag_c0 = 0;
        for (int j = 0; j < n; ++j) {
            if (matrix[0][j] == 0) {
                flag_r0 = 1;
                break;
            }
        }
        for (int i = 0; i < m; ++i) {
            if (matrix[i][0] == 0) {
                flag_c0 = 1;
                break;
            }
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }
        if (flag_r0 == 1) {
            for (int j = 0; j < n; ++j) {
                matrix[0][j] = 0;
            }
        }
        if (flag_c0 == 1) {
            for (int i = 0; i < m; ++i) {
                matrix[i][0] = 0;
            }
        }
    }
};


// 最终优化，使用第一列第一个元素，表示第一行有没有0，
// 从而只用一个flag_c0表示第一列中有没有0即可，不再需要flag_r0
// *注意，此时，为了防止
class Solution3 {
public:
    void setZeroes(vector<vector<int>> &matrix) {
        int m = matrix.size(), n = matrix[0].size();
        bool flag_c0 = false;
        for (int i = 0; i < m; ++i) {
            if (matrix[i][0] == 0) {
                flag_c0 = true;
            }
            // 同时可以处理这一行中是否有0
            for (int j = 1; j < n; ++j) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }
        // 防止第一行被提前更新掉，从最后一行开始
        for (int i = m - 1; i >= 0; --i) {
            for (int j = 1; j < n; ++j) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
            if (flag_c0) {
                matrix[i][0] = 0;  // 更新第一列
            }
        }
    }
};


int main() {
    vector<vector<int>> matrix = {
        {0,1,1},
        {1,0,1},
        {1,1,1}
    };

    Solution3 sol;
    sol.setZeroes(matrix);
    for (const auto& row : matrix) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}