/*
    medium
*/
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


class Solution {
public:
    int jump(vector<int>& nums) {
        if (nums.size() == 1) return 0;
        int res = 1;
        int n = nums.size();
        int canrange = nums[0];
        int idx = 0;
        // 寻找现在可达范围内，下一个最大可达范围
        while (canrange > 0 && idx + canrange < n - 1)
        {
            int i = idx + 1;
            int curbound = idx + canrange;
            for (; i <= curbound; ++i) {
                if (i + nums[i] > idx + canrange) {
                    canrange = nums[i];
                    idx = i;
                }
            }
            ++res;
        }
        return res;
    }
};


int main() {
    vector<int> nums ;
    Solution sol;

    nums  = {2,3,1,1,4};
    cout << sol.jump(nums ) << endl;

    nums  = {2,3,0,1,4};
    cout << sol.jump(nums ) << endl;

    return 0;
}