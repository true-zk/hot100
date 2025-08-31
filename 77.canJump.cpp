/*
    medium
*/
#include <vector>
#include <iostream>

using namespace std;


class Solution {
public:
    bool canJump(vector<int>& nums) {
        if (nums.size() == 1) return true;

        int n = nums.size();
        int canrange = nums[0];
        int idx = 0;
        while (canrange > 0)
        {
            ++idx;  // 跳到下个数
            --canrange;  // 可用范围-1
            if (nums[idx] > canrange) canrange = nums[idx];  // 如果当前值更大，更新可跳范围
            if (idx + canrange >= n - 1) return true;
        }
        return false;
    }
};


int main() {
    vector<int> nums ;
    Solution sol;

    nums  = {2,3,1,1,4};
    cout << sol.canJump(nums ) << endl;

    nums  = {3,2,1,0,4};
    cout << sol.canJump(nums ) << endl;

    return 0;
}