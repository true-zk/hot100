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