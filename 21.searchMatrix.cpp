#include <vector>
#include <iostream>

using std::vector;


/*
Limitation:  矩阵行列分别升序
*/

// 按行二分
// O(m * logn)
class Solution {
public:
    // lower_bound 二分模板
    int lower_bound(vector<int> &vec, const int &target) {
        int l = 0, r = vec.size();  // [l, r)
        while (l < r)  // 必须l < r，l <= r会导致mid == r，越界
        {
            int mid = l + (r - l) / 2;
            if (vec[mid] < target) {
                l = mid + 1;  // vec[mid] < target 表明包括mid本身都不合法，故mid + 1
            }
            else {
                r = mid;  // 与上面相反
            }
        }
        return l;
    }

    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        for (int i = 0; i < m; ++i) {
            int l_b = lower_bound(matrix[i], target);
            if (l_b != n && matrix[i][l_b] == target) {
                return true;
            }
        }
        return false;
    }
};


// Z形搜索
// 从(0, n-1)开始搜
/*
    维护(x, y)
    1. matrix[x, y] == target, return
    2. matrix[x, y] > target, --y
    3. matrix[x, y] < target, ++x
*/
// O(n + m)
class Solution1 {
public:

    bool searchMatrix(vector<vector<int>> &matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        int x = 0, y = n - 1;  // 
        while (x < m && y >= 0)
        {   
            int cur = matrix[x][y];
            if (cur == target) {
                return true;
            }
            else if (cur > target)
            {
                --y;
            }
            else {
                ++x;
            }
        }
        return false;
    }
};


int main(){
    vector<vector<int>> matrix {
        {1,4,7,11,15},
        {2,5,8,12,19},
        {3,6,9,16,22},
        {10,13,14,17,24},
        {18,21,23,26,30}};

    for (const auto& row : matrix) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    Solution1 sol;
    bool res = sol.searchMatrix(matrix, 5);
    std::cout << res << std::endl;
    return 0;
}