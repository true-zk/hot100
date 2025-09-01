#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hashable;
        for ( int i = 0; i < nums.size(); i++ ) {
            if ( hashable.find(target - nums[i]) != hashable.end() ) {
                return {hashable[target - nums[i]], i};
            }
            hashable[nums[i]] = i;
        }
        return {};
    }
};