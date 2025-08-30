/*
    medium
    二分模板
    lowerbound && upperbound
*/

#include <iostream>
#include <vector>
#include <utility>

using namespace std;


class Solution {
public:

    int lower_bound(vector<int> &nums, int target) {
        int l = 0, r = nums.size();  // lower_bound可能是n本身
        int mid;
        while (l < r)
        {
            mid = l + (r - l) / 2;  // 奇数，恰好mid，偶数，偏左（所以不会到r，不会越界）
            if (nums[mid] >= target) {  // 区别，下界可能是mid本身
                r = mid;        // tgt < mid, 答案在左边 or mid，所以r不能是mid + 1，只能是mid
            }
            else {
                l = mid + 1;    // tgt >= mid，下界一定在右边
            }
        }
        return l;
    }

    int upper_bound(vector<int> &nums, int target) {
        int l = 0, r = nums.size();
        int mid;
        while (l < r)
        {
            mid = l + (r - l) / 2;
            if (nums[mid] > target) {  // 唯一区别，上界是比target大的
                r = mid;      // tgt <= mid, 答案在左边 or mid，所以r不能是mid + 1，只能是mid
            }
            else {
                l = mid + 1;  // tgt > mid，答案一定在右边
            }
        }
        return l;
    }

    vector<int> searchRange(vector<int>& nums, int target) {
        if (!nums.size()) return vector<int> {-1, -1};

        int lb = lower_bound(nums, target);
        int ub = upper_bound(nums, target);
        
        if (lb == ub) return vector<int> {-1, -1};
        
        return vector<int> {lb, ub - 1};
    }
};


int main() {
    vector<int> res;
    Solution sol;

    vector<int> nums {5, 7, 7, 8, 8, 10};
    int tgt = 5;

    res = sol.searchRange(nums, tgt);
    cout << "[" << res[0] << ", " << res[1] << "]" << endl;
    return 0;
}