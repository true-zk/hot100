/*
    easy
    二分模板
*/

#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int i = 0, j = nums.size() - 1;
        int mid;
        while (i <= j)  // 只有 i > j出循环
        {
            mid = i + (j - i) / 2;
            if (nums[mid] == target) {
                return mid;
            }
            else if (nums[mid] > target)
            {
                j = mid - 1;
            }
            else {
                i = mid + 1;  // 前进一步
            }
        }
        // 出循环，i>j，说明
        return i;
    }
};


class Solution2 {
public:
    int searchInsert(vector<int>& nums, int target) {
        int i = 0, j = nums.size() - 1;
        int mid;
        while (i < j)  // 另一种判断条件
        {
            mid = i + (j - i) / 2;
            if (nums[mid] == target) {
                return mid;
            }
            else if (nums[mid] > target)
            {
                j = mid - 1;
            }
            else {
                i = mid + 1;
            }
        }
        // 出循环，i>=j，此时，还需要多判断一步
        return nums[i] < target ? i + 1: i;
    }
};


int main() {
    int n, target;
    vector<int> nums;
    cout << "input n: " << endl;
    cin >> n;
    cout << "input nums: " << endl;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        nums.push_back(x);
    }
    cout << "input target: ";
    cin >> target;

    Solution2 sol;
    int idx = sol.searchInsert(nums, target);
    cout << "插入位置: " << idx << endl;

    return 0;
    
}