#include<vector>
#include<unordered_set>

using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        // use set to remove duplicates
        unordered_set<int> set;
        for (int num: nums) {
            set.insert(num);
        }
        
        int res = 0;
        // traverse 'head'
        for (int num: set) {
            if (set.find(num - 1) == set.end()) {
                // num is head
                int cur_len = 1;
                while (set.find(num + cur_len) != set.end()) {
                    cur_len++;
                }
                res = max(res, cur_len);
            }
        }
        return res;
    }
};