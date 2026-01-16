/*
    189. 轮转数组
    medium

    给定一个整数数组 nums，将数组中的元素向右轮转 k 个位置，其中 k 是非负数。
    必须O(1)空间，原地

    比较好理解的方法是数组翻转；还有个很逆天的数学做法，用gcd
    
    数组翻转：
    数组翻转操作是用双指针，把[l, r]之间的部分翻转；
    这个题，右移k，见下面例子
    1 2 3 4 5 6 7    k = 3
    7 6 5 4 3 2 1    reverse(nums, 0, 6)
    5 6 7            reverse(nums, 0, k - 1) 
          1 2 3 4    reverse(nums, k, 6)
*/

#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>
using std::vector;
using std::swap;
using std::gcd;
using std::cout; using std::endl;
using std::cin;


class Solution1 {
public:
    void rotate(vector<int>& nums, int k) {
        vector<int> res(nums.size());
        for (int i = 0; i < nums.size(); ++i) {
            res[(i + k) % nums.size()] = nums[i];
        }
        nums = res;
    }
};


class Solution2 {
public:
    void reserve_array(vector<int> &nums, int start, int end) {
        while (start < end)
        {
            swap(nums[start], nums[end]);
            --end;
            ++start;
        }
    }

    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k = k % n;  // k <= n
        reserve_array(nums, 0, n - 1);
        reserve_array(nums, 0, k - 1);
        reserve_array(nums, k, n - 1);
    }
};


class Solution3 {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k = k % n;  
        int cnt = gcd(k, n);
        for (int start = 0; start < cnt; ++start) {
            int cur = start;
            int prev = nums[start];
            do
            {
                int j = (cur + k) % n;
                int tmp = nums[j];
                nums[j] = prev;
                prev = tmp;
                cur = j;
            } while (cur != start);
        }
    }
};


int main() {
    int n, k;
    // 输入数组长度和k
    cout << "请输入数组长度和k: ";
    cin >> n >> k;
    vector<int> nums(n);
    cout << "请输入数组元素: ";
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }

    Solution1 sol;
    sol.rotate(nums, k);

    cout << "旋转后的数组: ";
    for (int x : nums) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}