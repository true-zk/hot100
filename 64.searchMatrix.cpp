/*
    medium
    二分模板
*/

#include <iostream>
#include <vector>
#include <utility>

using namespace std;


// 注意这个矩阵和21的不一样，那个只是保证了行和列各自的顺序
// 本题是严格的下一行每个元素也＞上一行所有元素
// 故，本题可以二维展开成一维二分
// 而21题只能Z搜索或者按行2分
class Solution {
public:

    int point2idx(int x, int y, int n) {
        return x * n + y;
    }

    pair<int, int> idx2point(int idx, int n) {
        return pair<int, int> {idx / n, idx % n};
    }

    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        pair<int, int> p;
        int left = 0, right = m * n - 1;
        int mid, midval;
        while (left <= right)
        {
            mid = left + (right - left) / 2;
            p = idx2point(mid, n);
            midval = matrix[p.first][p.second];
            if (midval == target) return true;
            else if (midval > target) {
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }
        return false;
    }
};


int main() {
    vector<vector<int>> matrix = {
        {1, 3, 5, 7},
        {10, 11, 16, 20},
        {23, 30, 34, 60}
    };
    int target1 = 3;
    int target2 = 13;

    Solution sol;
    cout << boolalpha << sol.searchMatrix(matrix, target1) << endl; // true
    cout << boolalpha << sol.searchMatrix(matrix, target2) << endl; // false

    return 0;
}