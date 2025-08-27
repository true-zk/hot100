#include <vector>
#include <iostream>

using std::vector;


class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<int> res;
        int dirct = 0;
        /*
        dirct: 0右, 1下，2左，3上
        */
        int top = 1, bottom = m - 1, left = 0, right = n - 1;
        int i = 0, j = 0;
        for (int cnt = m * n; cnt > 0; --cnt) {
            res.push_back(matrix[i][j]);
            //确定下一个i,j
            if (dirct == 0) {  // 右
                if (j == right) {
                    dirct = 1;
                    --right;
                    ++i;
                }
                else {
                    ++j;
                }
            }
            else if (dirct == 1)  // 下
            {
                if (i == bottom) {
                    dirct = 2;
                    --bottom;
                    --j;
                }
                else {
                    ++i;
                }
            }
            else if (dirct == 2)  // 上
            {
                if (j == left) {
                    dirct = 3;
                    ++left;
                    --i;
                }
                else {
                    --j;
                }
            }
            else if (dirct == 3) // 左
            {
                if (i == top) {
                    dirct = 0;
                    ++top;
                    ++j;
                }
                else {
                    --i;
                }
            }
        }
        return res;
    }
};


// 按层遍历，也就是把矩阵按层看待，直到到达最中心一层
class Solution2 {
public:
    vector<int> spiralOrder(vector<vector<int>> &matrix) {
        int m = matrix.size(), n = matrix[0].size();
        int top = 0, left = 0, right = n - 1, bottom = m - 1;
        vector<int> res;
        while (left <= right && top <= bottom)
        {
            for (int j = left; j <= right; ++j) {
                res.push_back(matrix[top][j]);
            }
            for (int i = top + 1; i <= bottom; ++i)
            {
                res.push_back(matrix[i][right]);
            }
            // "top < bottom" in case: top == bottom, output twice will make err.
            for(int j = right - 1; top < bottom && j >= left; --j) {
                res.push_back(matrix[bottom][j]);
            }
            // same
            for(int i = bottom - 1; left < right && i > top; --i) {
                res.push_back(matrix[i][left]);
            }
            
            ++left;
            ++top;
            --right;
            --bottom;
        }
        return res;
    }
};


int main() {
    // vector<vector<int>> matrix {{3}, {2}};
    // vector<vector<int>> matrix {{1,2,3},{4,5,6}, {7,8,9}};
    vector<vector<int>> matrix {{1,2,3,4},{5,6,7,8}, {9,10,11,12}};
    for (const auto& row : matrix) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    Solution2 sol;
    auto res = sol.spiralOrder(matrix);
    for(auto a: res) {
        std::cout << a << ' ';
    }
    std::cout << std::endl;
    return 0;
}