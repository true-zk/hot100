/*
    medium
*/
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
#include <iostream>
#include <algorithm>

using namespace std;


class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> freq; // val: frequence
        for (auto &el: nums) {
            ++freq[el];
        }

        // 小顶
        auto reversecmp = [] (pair<int, int> &l, pair<int, int> &r) {return l.second > r.second;};

        // 优先队列（堆）维护
        // 元素：pair<int, int>，容器vector，比较函数bigger
        priority_queue<pair<int, int>,vector<pair<int, int>>, decltype(reversecmp)> pq(reversecmp);
        for (auto& el: freq) {
            // 只需要维护k个最大频率即可，如果满了，并且当前堆最小值 < el.secound，删除堆顶，加入新的
            if (pq.size() == k) {
                if (el.second > pq.top().second) {
                    pq.pop();
                    pq.emplace(el);
                }
            }
            else {
                pq.emplace(el);
            }
        }

        vector<int> res;
        while (!pq.empty()) {
            res.emplace_back(pq.top().first);
            pq.pop();
        }
        return res;
    }
};


// 还有种快排的做法


int main() {
    Solution sol;

    vector<int> nums1 = {1,1,1,2,2,3};
    int k1 = 2;
    auto res1 = sol.topKFrequent(nums1, k1);
    cout << "测试1: ";
    for (int x : res1) cout << x << " ";
    cout << endl; // 1 2

    vector<int> nums2 = {4,1,-1,2,-1,2,3};
    int k2 = 2;
    auto res2 = sol.topKFrequent(nums2, k2);
    cout << "测试2: ";
    for (int x : res2) cout << x << " ";
    cout << endl; // -1 2

    vector<int> nums3 = {5};
    int k3 = 1;
    auto res3 = sol.topKFrequent(nums3, k3);
    cout << "测试3: ";
    for (int x : res3) cout << x << " ";
    cout << endl; // 5

    return 0;
}