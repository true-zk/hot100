/*
    hard
    Limitation O(logn)
    找两个有序数组的中位数 = 找两个有序数组中第k小的数，k = n+m / 2 或者 k = n+m / 2 + 1
*/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;


// 这算法真不是人想的
/*
    对a和b，分别找k/2 - 1的位置，然后比较两个值，较小的那个数组中，k/2 - 1之前的部分不在考虑：
    - 假设a[k/2 - 1] <= b[k/2 - 1]
    - a[0, k/2 - 2] b[0, k/2 - 2] 中一共 "k - 2" 个元素，
    - 那么最多只有这些 a[0, k/2 - 2] b[0, k/2 - 2] 即 "k - 2" 个元素 < a[k/2 - 1]
    - 即，a[k/2 - 1]最大也顶多是第 "k - 1" 大，不可能是第k个元素
    - 可以忽略[0, k/2 - 2]这个区间
    - a的左边界变成 k / 2 - 1
    - k -> k - k/2 (减去消除的k/2个数)
*/
/*
    special cases:
    - 有一个数组是空的，= 该数组都被排除，直接返回另一个数组的第k小
    - k = 1，= 最小的，返回两个数组的最小值即可
    - k/2 - 1在a或b中越界，选越界数组的最后一个元素，
        - 这种情况只能手动算
        - 这时候不能直接k -> k/2了，因为排除的数字数量可能不是k/2
        - 这种情况仍然保持了正确性，因为越界说明更不可能是第k大了(比pivot小的元素更少了，还不到k-2个)
*/
class Solution {
public:
    int findKth(vector<int> &nums1, vector<int> &nums2, int k) {
        int n1 = nums1.size(), n2 = nums2.size();
        int left1 = 0, left2 = 0;  // 标定此时的还没排除的nums1 nums2的左边界
        while (true)
        {
            // 边界
            if (left1 == n1) {  // 左空，返回右中第k大
                return nums2[left2 + k - 1];
            }
            if (left2 == n2) {  // 右空
                return nums1[left1 + k - 1];
            }
            if (k == 1) {  // k == 1，最小的，即左右最小的
                return min(nums1[left1], nums2[left2]);
            }

            // 可能越界，要处理
            int cur_idx_1 = min(left1 + (k / 2 - 1), n1 - 1);  // 越界则取n-1
            int cur_idx_2 = min(left2 + (k / 2 - 1), n2 - 1); 

            int pivot1 = nums1[cur_idx_1];
            int pivot2 = nums2[cur_idx_2];

            if (pivot1 <= pivot2) {
                k = k - (cur_idx_1 - left1 + 1);  // 包括pivot本身也排除（pivot 只能是第k-1大，排除）
                left1 = cur_idx_1 + 1;            // 跳到pivot后面
            }
            else {
                k = k - (cur_idx_2 - left2 + 1);  // 对称
                left2 = cur_idx_2 + 1;
            }
        }
    }

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size(), n2 = nums2.size();
        if ((n1 + n2) % 2 == 0) {
            int k1 = findKth(nums1, nums2, (n1 + n2) / 2);
            int k2 = findKth(nums1, nums2, (n1 + n2) / 2 + 1);
            return (k1 + k2) / 2.0;
        }
        else {
            return findKth(nums1, nums2, (n1 + n2) / 2 + 1);
        }
    }
};


int main() {
    Solution sol;

    vector<int> nums1 = {1, 3};
    vector<int> nums2 = {2};
    cout << sol.findMedianSortedArrays(nums1, nums2) << endl; // 2.0

    vector<int> nums3 = {1, 2};
    vector<int> nums4 = {3, 4};
    cout << sol.findMedianSortedArrays(nums3, nums4) << endl; // 2.5

    vector<int> nums5 = {0, 0};
    vector<int> nums6 = {0, 0};
    cout << sol.findMedianSortedArrays(nums5, nums6) << endl; // 0.0

    vector<int> nums7 = {};
    vector<int> nums8 = {1};
    cout << sol.findMedianSortedArrays(nums7, nums8) << endl; // 1.0

    vector<int> nums9 = {2};
    vector<int> nums10 = {};
    cout << sol.findMedianSortedArrays(nums9, nums10) << endl; // 2.0

    return 0;
}