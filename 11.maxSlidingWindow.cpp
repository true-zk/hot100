#include <vector>
#include <algorithm>
#include <queue>

using std::vector;
using std::max;
using std::priority_queue;
using std::pair;


class Solution1 {
public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k) {
        vector<int> res;
        int n = nums.size();
        priority_queue<pair<int, int>> pq;

        for (int i = 0; i < k; ++i) {
            pq.emplace(nums[i], i);
        }

        res.push_back(pq.top().first);

        for (int i = k; i < n; ++i) {
            // emplace first, pop then will better:
            // push, pq will filter anc replace all items,
            // which makes the pop hit cache more.
            pq.emplace(nums[i], i);
            while (pq.top().second <= i - k) {
                pq.pop();
            }
            res.push_back(pq.top().first);
        }

        return res;

    }
};


// class Solution