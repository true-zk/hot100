/*
    165. 比较版本号
    medium

    给你两个 版本号字符串 version1 和 version2 ，请你比较它们。版本号由被点 '.' 分开的修订号组成。修订号的值 是它 转换为整数 并忽略前导零。

    比较版本号时，请按 从左到右的顺序 依次比较它们的修订号。如果其中一个版本字符串的修订号较少，则将缺失的修订号视为 0。

    返回规则如下：

    如果 version1 < version2 返回 -1，
    如果 version1 > version2 返回 1，
    除此之外返回 0。
*/
#include <string>
#include <iostream>

using namespace std;


class Solution {
public:
    int compareVersion(string version1, string version2) {
        int n = version1.size();
        int m = version2.size();

        int p1 = 0, p2 = 0;
        while (p1 < n || p2 < m)
        {
            // 指针移动到下个.号
            long long x = 0;
            for (; p1 < n && version1[p1] != '.'; ++p1) {
                x = x * 10 + static_cast<int>(version1[p1] - '0');
            }
            ++p1; // move after dot

            long long y = 0;
            for (; p2 < m && version2[p2] != '.'; ++p2) {
                y = y * 10 + static_cast<int>(version2[p2] - '0');
            }
            ++p2;

            if (x != y)
                return x < y ? -1 : 1;
        }
        return 0;
    }
};


int main() {
    string v1, v2;
    Solution sol;

    v1 = "1.2";
    v2 = "1.10";
    cout << v1 << ", " << v2 << "res: " << sol.compareVersion(v1, v2) << endl;

    v1 = "1.01";
    v2 = "1.001";
    cout << v1 << ", " << v2 << "res: " << sol.compareVersion(v1, v2) << endl;

    v1 = "1.0";
    v2 = "1.0.0.0";
    cout << v1 << ", " << v2 << "res: " << sol.compareVersion(v1, v2) << endl;

    return 0;
}