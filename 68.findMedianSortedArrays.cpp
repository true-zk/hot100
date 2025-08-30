/*
    hard
*/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;


// 只有 左右有重叠的情况需要特殊处理
class Solution {
public:

    int lowerBound(vector<int> &nums, int tgt) {
        int l = 0, r = nums.size(), mid;
        while (l < r)
        {
            mid = l + (r - l) / 2;
            if (nums[mid] >= tgt) {
                r = mid;
            }
            else {
                l = mid + 1;
            }
        }
        return l;
    }

    int upperBound(vector<int> &nums, int tgt) {
        int l = 0, r = nums.size() - 1, mid;
        while (l < r)
        {
            mid = l + (r - l) / 2;
            if (nums[mid] > tgt) {
                r = mid;
            }
            else {
                l = mid + 1;
            }
        }
        return l;
    }

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size(), n2 = nums2.size();
        if (n1 == 0) {
            return (nums2[(n2 - 1) / 2] + nums2[ n2 / 2]) / 2;
        }
        else if (n2 == 0) {
            return (nums1[(n2 - 1) / 2] + nums1[ n2 / 2]) / 2;
        }
        // 将两种情况转换成一种 nums1[0] <= nums2[0]的情况，即只有可能nums1在左边，nums2在右边
        vector<int> *pnums1, *pnums2;
        if (nums1[0] <= nums2[0]) {
            pnums1 = &nums1;
            pnums2 = &nums2;
        }
        else {
            pnums1 = &nums2;
            pnums2 = &nums1;
            swap(n1, n2);
        }
        // 处理不重叠情况
        if ((*pnums1)[n1 - 1] <= (*pnums2)[0]) {  // pnums1 <= pnums2
            int mid1 = (n1 + n2 - 1) / 2;
            int mid2 = (n1 + n2) / 2;
            int median1 = (mid1 < n1) ? (*pnums1)[mid1] : (*pnums2)[mid1 - n1];
            int median2 = (mid2 < n1) ? (*pnums1)[mid2] : (*pnums2)[mid2 - n1]; 
            return (median1 + median2) / 2;
        }

        // 只剩下了交叠的情况
    }
};