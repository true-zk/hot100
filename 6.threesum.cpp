#include<vector>
#include<set>
#include<algorithm>

using namespace std;

class Solution1 {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        set<vector<int>> res;  // this is no need;
        sort(nums.begin(), nums.end());

        for (int i = 0; i < n - 2; i++) {
            int cur_base = nums[i];
            int left = i + 1;
            int right = n-1;
            while(left < right) {
                int lv = nums[left];
                int rv = nums[right];
                int tmp = lv + rv + cur_base;
                if (tmp == 0) {
                    res.insert({cur_base, lv, rv});
                    left++;
                    while (lv == nums[left + 1] && left < right)
                    {
                        left++;
                    }
                    right++;
                    while (rv == nums[right-1]  && left < right)
                    {
                        right--;
                    }   
                }
                else if (tmp < 0) {
                    left++;
                }
                else {
                    right--;
                }
            }
        }
        vector<vector<int>> res_(res.begin(), res.end());
        return res_;
    }
};

// -4 -1 -1 0 1 2
// -2 -1 1 2
class Solution {
public:
    vector<vector<int>> two_sum(vector<int>& nums, int l, int r, int base_v) {
        vector<vector<int>> res;
        while (l < r)
        {
            int tmp = nums[l] + nums[r] + base_v;
            if (tmp == 0) {
                res.push_back({base_v, nums[l], nums[r]});
                while (l < r && nums[l] == nums[l + 1])
                {
                    l++;
                }
                l++;
                while (l < r && nums[r] == nums[r - 1])
                {
                    r--;
                }
                r--;
            }
            else if (tmp < 0)
            {
                l++;
            }
            else {
                r--;
            }
        }
        return res; 
    }

    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        int n = nums.size();
        sort(nums.begin(), nums.end());
        for (int i = 0; i < n - 2; i++) {
            auto tmp = two_sum(nums, i + 1, n - 1, nums[i]);
            res.insert(res.end(), tmp.begin(), tmp.end());

            // for each base v, only need to check once, and this can rm repeat v.
            while (i < n - 2 && nums[i] == nums[i + 1])
            {
                i++;
            }
        }
        return res;
    }

};