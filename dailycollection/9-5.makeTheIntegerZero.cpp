/*
    medium

    给你两个整数：num1 和 num2 。
    在一步操作中，你需要从范围 [0, 60] 中选出一个整数 i ，并从 num1 减去 2i + num2 。
    请你计算，要想使 num1 等于 0 需要执行的最少操作数，并以整数形式返回。
    如果无法使 num1 等于 0 ，返回 -1 。
*/
#include <iostream>

using namespace std;


// 数学
/*
    假设操作k次，即，nums1 - k * nums2 是不是 k个2^i 的组合？
    进一步，设 x = nums1 - k * nums2, 设 f(x) 是 x 二进制表示中的1的个数，则 k 的范围：
        - k <= x ： 每次最小取2^0 = 1，如果k > x，无法满足；上界
        - k >= f(x) ： 至少要有这么多k来把1覆盖掉，例如 x = 1011, f(x) = 3, 至少要3个k来覆盖掉1；下界
    这个范围是一定成立的情况，即只要 k 落在这个范围内，就有解，返回 k 
    关于 有解性：
        - k <= nums1 - k * nums2 => k * (num2 + 1) <= nums1
            if nums2 + 1 <= 0, 由 nums1 >= 1，恒成立，只要 k >= f(x) 即可，这种情况一定有解
            if nums2 + 1 > 0, k <= nums1 / (nums2 + 1)，可能在 k 枚举到 f(x) 之前，超越上界，可能无解
*/
class Solution {
public:
    int makeTheIntegerZero(int num1, int num2) {
        int k = 0;
        
        while (true)
        {
            long long  x = num1 - k * num2;
            if (k > x) return -1; // k 超过上界
            else if (k >= __builtin_popcount(x)) return k;  //  f(x) <= k <= x 
            ++k;
        }
    }
};