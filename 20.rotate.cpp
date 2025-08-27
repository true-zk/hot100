#include <iostream>
#include <vector>
#include <utility>
using std::vector;

/*
按行看，第i行变成了第j列
matrix[row][col] -> matrix[col][m - row - 1]
*/

// 水平翻转+轴对称（转置）
// 翻转： matrix[row][col] -> matrix[m - row - 1][col]
// 转置： matrix[m - row - 1][col] -> matrix[col][m - row - 1]
class Solution1 {
public:
    void rotate(vector<vector<int>> &matrix) {
        int m = matrix.size(), n = matrix[0].size();
        // flip horizontal
        for (int i = 0; i < m / 2; ++i) {
            for (int j = 0; j < n; ++j)
            {
                std::swap(matrix[i][j], matrix[m - i - 1][j]);
            }
        }

        // transpose
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < i; ++j)
            {
                std::swap(matrix[i][j], matrix[j][i]);
            }
        }
    }
};


// 用一个变量记录到旋转后位置，然后四象限进行swap
/*
    matrix[row][col]
    matrix[col][n - row - 1]
    matrix[n - row - 1][n - col - 1]
    matrix[n - col - 1][row]
*/
class Solution2 {
public:
    void rotate(vector<vector<int>> &matrix) {
        int n = matrix.size();
        for (int i = 0; i < n / 2; ++i) {
            for (int j = 0; j < (n + 1) / 2; ++j) {  // take care odd matrix
                int temp = matrix[i][j];
                matrix[i][j] = matrix[n - j - 1][i];
                matrix[n - j - 1][i] = matrix[n - i - 1][n - j - 1];
                matrix[n - i - 1][n - j - 1] = matrix[j][n - i - 1];
                matrix[j][n - i - 1] = temp;
            }
        }
    }
};


int main() {
    // vector<vector<int>> matrix {{3}, {2}};
    vector<vector<int>> matrix {{1,2,3},{4,5,6}, {7,8,9}};
    // vector<vector<int>> matrix {{1,2,3,4},{5,6,7,8}, {9,10,11,12}};
    for (const auto& row : matrix) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    Solution1 sol;
    sol.rotate(matrix);
    for (const auto& row : matrix) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}