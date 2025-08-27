#include <vector>
#include <algorithm>
using std::vector;
using std::sort;
using std::max;
using std::min;


class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.size() == 1) {
            return intervals;
        }

        auto delta_first_sort = [] (const vector<int> &a, const vector<int> &b) {
            return a[0] < b[0];
        };
        sort(intervals.begin(), intervals.end(), delta_first_sort);
        
        auto cur = intervals.begin();
        while (cur != intervals.end() - 1) {
            if ((*cur)[1] >= (*(cur + 1))[0]) {
                (*cur)[1] = max((*cur)[1], (*(cur + 1))[1]);
                (*cur)[0] = min((*cur)[0], (*(cur + 1))[0]);
                intervals.erase(cur + 1);
            }
            else {
                ++cur;
            }
        }
        return intervals;
    }
};



class Solution1 {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.size() == 1) {
            return intervals;
        }

        auto delta_first_sort = [] (const vector<int> &a, const vector<int> &b) {
            return a[0] < b[0];
        };
        sort(intervals.begin(), intervals.end(), delta_first_sort);
        
        vector<vector<int>> res;
        for (int i = 0; i < intervals.size(); ++i) {
            if (res.empty() || res.back()[1] < intervals[i][0]) {
                res.push_back(intervals[i]);
            } else {
                // ignores condition: res.back()[0] < intervals[i][0]
                res.back()[1] = max(res.back()[1], intervals[i][1]);
            }
        }
        return res;
    }
};