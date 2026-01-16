/*
    medium
*/
#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>
#include <random>


using namespace std;


// 下一个排列，即找到改动最小的
// 从右往左找第一个顺序对a[i] < a[j]
// 然后交换a[i] a[j]，
// 此时a[i]换成了尽可能小的更大的数
// 然后把[i+1, n-1]的重排为顺序
class Solution {
public:
    void nextPermutation(vector<int>& nums) {

        int n = nums.size();
        int l = 0, r = 0;  // 如果完全逆序， l = r = 0
        // 确定 l
        // 从右往左遍历，
        // 找到第一个a[i] < a[i + 1]，
        // 此时，i为最靠右的顺序对，因为[i+1, n-1]都是a[j] > a[j + 1]是逆序的
        for (int i = n - 2; i >= 0; --i) {
            if (nums[i] < nums[i + 1]) {
                l = i;
                break;
            }
        }
        // 确定 r
        // 从右往l遍历，
        // 因为[l + 1, n - 1]都是逆序
        // 找到第一个a[j] > a[l]，就是尽可能小的但是比a[l]大的元素
        for (int j = n - 1; j >= 0; --j) {
            if (nums[j] > nums[l]) {
                r = j;
                break;
            }
        }

        if (l == r && l == 0) {  // 完全逆序 || 只有一个元素，直接reverse
            reverse(nums.begin(), nums.end());
            return;
        }

        // 交换a[l] a[r]
        swap(nums[l], nums[r]);

        // 排序[l+1, n-1]， 使得变动最小化
        sort(nums.begin() + l + 1, nums.end());
    }
    // 最后这里可以不排序，因为已知[l+1, n-1]是逆序的，并且交换a[l] a[r]仍保持逆序（a[r]是大于a[l]的最小值）
    // 直接reverse(nums.begin() + l + 1, nums.end());
};


void printVec(const vector<int>& nums) {
    for (int x : nums) cout << x << " ";
    cout << endl;
}

int main() {
    Solution sol;

    vector<int> nums1 = {1, 2, 3};
    sol.nextPermutation(nums1);
    printVec(nums1); // 1 3 2

    vector<int> nums2 = {3, 2, 1};
    sol.nextPermutation(nums2);
    printVec(nums2); // 1 2 3

    vector<int> nums3 = {1, 1, 5};
    sol.nextPermutation(nums3);
    printVec(nums3); // 1 5 1

    vector<int> nums4 = {1};
    sol.nextPermutation(nums4);
    printVec(nums4); // 1

    return 0;
}