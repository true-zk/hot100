/*
    easy
    经典双指针
    给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。
    请注意 ，必须在不复制数组的情况下原地对数组进行操作。
*/

#include <vector>

using namespace std;

// 

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int which_zero = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != 0 && which_zero) {
                nums[i - which_zero] = nums[i];
            }

            if (nums[i] == 0) {
                which_zero++;
            }
        }

        for (int i = nums.size() - which_zero; i < nums.size(); i++) {
            nums[i] = 0;
        }
        return;
    }
};


class Solution2 {
public:
    void moveZeros(vector<int>& nums) {
        int n = nums.size();
        int first_zero = 0;
        while (first_zero < n && nums[first_zero] != 0) {
            first_zero++;
        }
        int left = first_zero;
        int right = first_zero + 1;
        while (right < n) {
            if (nums[right] != 0) {
                nums[left] = nums[right];
                nums[right] = 0; // swap is ok; or finish this after the loop
                left++;
            }
            right++;
        }
        return;
    }
};