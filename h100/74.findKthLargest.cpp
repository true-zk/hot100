/*
    medium
    这道题看起来很重要，题面不复杂，但是要求O（n）
    解法1 取自快排思想
    解法2 考察自构建大堆（优先队列）
*/
#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <limits>
#include <iostream>
#include <algorithm>

using namespace std;


// 最大堆
class Solution {
public:

    void siftdown(vector<int> &nums, int i) {
        int n = nums.size();
        while (true)
        {
            int l = i * 2 + 1;
            int r = i * 2 + 2;
            int largest = i;

            if (l < n && nums[l] > nums[largest]) largest = l;
            if (r < n && nums[r] > nums[largest]) largest = r;

            if (largest == i) break;

            swap(nums[largest], nums[i]);
            i = largest;
        }
    }

    void buildMaxHeap(vector<int> &nums) {
        // 从第一个非叶子开始，下沉
        for (int i = nums.size() / 2 - 1; i >= 0; --i) {
            siftdown(nums, i);
        }
    }

    int findKthLargest(vector<int>& nums, int k) {
        buildMaxHeap(nums);
        int res;
        while (k > 0)
        {
            res = nums[0];
            swap(nums[0], nums[nums.size() - 1]);  // put last at head
            nums.pop_back(); // rm cur last(original head)
            siftdown(nums, 0);  // maintain head
            --k;
        }
        return res;
    }
};


// 快排
class Solution2 {
public:
    // 快排思想找到第k大的元素
    // Hoare select pivot:p [l, p] [p + 1, r]
    // 确定arr[p] 是第p大的
    // Hoare算法，双指针平均性能好，不会被特殊全相等的例子卡掉
    int quickSelect(vector<int> &arr, int l, int r, int k) {
        if (l == r) return arr[k];  // 边界
        
        // Hoare partition
        int pivot = arr[l];
        int i = l - 1;
        int j = r + 1;
        while (i < j)
        {
            do ++i; while (arr[i] < pivot);  // 定位到左边第一个>= pivot的
            do --j; while (arr[j] > pivot);

            if (i < j) swap(arr[i], arr[j]);
        }
        // i >= j; q =j, [l, q] [q + 1, r]
        // k <= q 则在左边继续找，否则在右边继续找
        if (k <= j) return quickSelect(arr, l, j, k);
        else return quickSelect(arr, j + 1, r, k);
    }

    // Lomuto算法，正确性一致，但是会被全相等的例子卡掉
    int quickSelectLomuto(vector<int> &arr, int l, int r, int k) {
        if (l == r) return arr[k];

        int pivot = arr[r];
        int i = l - 1;  // 标定已处理的比pivot小等的边界
        for (int j = l; j < r; ++j) {
            if (arr[j] <= pivot) {
                ++i;
                swap(arr[j], arr[i]);
            }
        }
        // [l, i] [i + 1, r - 1] [r]
        int p = i + 1;
        // -> [l, p - 1] [p] [p + 1, r]
        swap(arr[p], arr[r]);

        if (k == p) return arr[p];
        else if (k < p) return quickSelectLomuto(arr, l, p - 1, k);
        else return quickSelectLomuto(arr, p + 1, r, k);
    }

    int findKthLargest(vector<int>& nums, int k) {
        // return quickSelect(nums, 0, nums.size() - 1, nums.size() - k);
        return quickSelectLomuto(nums, 0, nums.size() - 1, nums.size() - k);
    }
};


int main() {
    Solution2 sol;

    vector<int> nums1 = {3,2,1,5,6,4};
    int k1 = 2;
    cout << sol.findKthLargest(nums1, k1) << endl; // 5

    vector<int> nums2 = {3,2,3,1,2,4,5,5,6};
    int k2 = 4;
    cout << sol.findKthLargest(nums2, k2) << endl; // 4

    vector<int> nums3 = {1};
    int k3 = 1;
    cout << sol.findKthLargest(nums3, k3) << endl; // 1

    return 0;
}