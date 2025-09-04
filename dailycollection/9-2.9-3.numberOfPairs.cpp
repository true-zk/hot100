/*
    3025, 3027 人员站位的方案数
    medium hard
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;


// 合法的节点对(xa, ya) (xb, yb)满足:
// xa <= xb && ya >= yb
// 注意, 任意两个节点不同 -> 不需要考虑a = b的情况
class Solution {
public:
    int numberOfPairs(vector<vector<int>>& points) {
        // 按照行升序,列降序排序
        auto lambda = [] (vector<int> &l, vector<int> &r) {
            if (l[0] != r[0]) return l[0] < r[0];
            return l[1] > r[1];
        };
        sort(points.begin(), points.end(), lambda);
        // 从左上角开始遍历
        /*
            遍历到i, j的时候,
            对于[i + 1, j - 1]的区间的k点, 需要保证yk > yi || yk < yj
            - yk > yi 通过排序, 不存在这样的点
            - 只需要判断 yk < yj 即可, (后面选的节点要在前面选的节点上面)
            - 维护一个maxy, 存住之前的最大yk, 只要yj > maxy, 就可以选, 并更新maxy
        */
        int n = points.size();
        int res = 0;
        for (int i = 0; i < n; ++i) {
            int y1 = points[i][1];
            int maxy = numeric_limits<int>::min();
            for (int j = i + 1; j < n; ++j) {  // 之前的节点不需要再考虑
                int y2 = points[j][1];
                if (y1 >= y2 && y2 > maxy) {
                    ++res;
                    maxy = y2;
                }
            }
        }
        return res;
    }
};


int main() {
    Solution sol;

    vector<vector<int>> points1 = {{6, 2}, {4, 4}, {2, 6}};
    cout << sol.numberOfPairs(points1) << endl; // 2

    vector<vector<int>> points2 = {{3, 1}, {1, 3}, {1, 1}};
    cout << sol.numberOfPairs(points2) << endl; // 2

    vector<vector<int>> points3 = {{1, 1}, {2, 2}, {3, 3}};
    cout << sol.numberOfPairs(points3) << endl; // 0

    return 0;
}