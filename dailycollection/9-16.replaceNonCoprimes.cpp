/*
    2197. 替换数组中的非互质数

    给你一个整数数组 nums 。请你对数组执行下述操作：

    从 nums 中找出 任意 两个 相邻 的 非互质 数。
    如果不存在这样的数，终止 这一过程。
    否则，删除这两个数，并 替换 为它们的 最小公倍数（Least Common Multiple，LCM）。
    只要还能找出两个相邻的非互质数就继续 重复 这一过程。
    返回修改后得到的 最终 数组。可以证明的是，以 任意 顺序替换相邻的非互质数都可以得到相同的结果。

    两个数字 x 和 y 满足 非互质数 的条件是：GCD(x, y) > 1 ，其中 GCD(x, y) 是 x 和 y 的 最大公约数 。
*/

#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>

using namespace std;


// gcd和lcm手写
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}


int lcm(int a, int b) {
    return a / gcd(a, b) * b;
}


class Solution {
public:
    vector<int> replaceNonCoprimes(vector<int>& nums) {
        int n = nums.size();
        vector<int> res;
        for (int i = 0; i < n; ++i) {
            int tmp = nums[i];
            while (!res.empty())
            {
                if (gcd(tmp, res.back()) != 1) {  // 和栈顶不互质，替换
                    tmp = lcm(tmp, res.back());
                    res.pop_back();
                }
                else {  // 和栈顶互质，不需要继续
                    break;
                }
            }
            res.push_back(tmp);
        }
        return res;
    }
};


void printVec(const vector<int>& nums) {
    for (int x : nums) cout << x << " ";
    cout << endl;
}

int main() {
    Solution sol;

    vector<int> nums1 = {6,4,3,2,7,6,2};
    auto res1 = sol.replaceNonCoprimes(nums1);
    printVec(res1); // 12 7 6

    vector<int> nums2 = {2,6,8,3};
    auto res2 = sol.replaceNonCoprimes(nums2);
    printVec(res2); // 24

    vector<int> nums3 = {2,3,5,7,11};
    auto res3 = sol.replaceNonCoprimes(nums3);
    printVec(res3); // 2 3 5 7 11

    vector<int> nums4 = {2,4,8,16};
    auto res4 = sol.replaceNonCoprimes(nums4);
    printVec(res4); // 16

    return 0;
}