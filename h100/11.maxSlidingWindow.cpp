/*
    239. 滑动窗口最大值
    hard

    给你一个整数数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。
    你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。
    返回 滑动窗口中的最大值 。

    动态的最大值-> priority_queue nlogn


    单调性 -> 单调栈/队列 n
    单调队列中保存下标，保证每个nums[p.back()] > nums[i]
    即队列从头往尾，单调递减，p.front()就是最大值的下标，
    但是要判断p.front() < i-k，否则要pop_front()直到找到第一个在范围内的

    如果nums[p.back()] <= nums[i]，说明nums[i]之前的这些都比nums[i]小，
    不可能是滑窗最大值了，直接p.pop_back()直到符合nums[p.back()] > nums[i]或者空了
    把nums[i] push_back入队列
*/

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