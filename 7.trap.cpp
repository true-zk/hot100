#include<vector>
#include<algorithm>
#include<stack>

using namespace std;

// dp
class Solution1 {
public:
    int trap(vector<int>& height) {
        auto n = height.size();
        if (n == 0) {
            return 0;
        }
        vector<int> left_max(n, 0);
        vector<int> right_max(n, 0);
        int res = 0;

        left_max[0] = height[0];
        right_max[n - 1] = height[n - 1];

        for (int i = 1; i < n; i++) {
            left_max[i] = max(left_max[i - 1], height[i]);
            right_max[n - 1 - i] = max(right_max[n - i], height[n - 1 - i]);
        }

        for (int i = 1; i < n - 1; i++) {
            int tmp = min(left_max[i], right_max[i]) - height[i];
            if (tmp > 0) {
                res += tmp;
            }
        }

        return res;
    }
};


class Solution2 {
public:
    int trap(vector<int>& height) {
        int res = 0;
        auto n = height.size();
        stack<int> stk;
        for (int i = 0; i < n; ++i) {
            while (!stk.empty() && height[i] > height[stk.top()])
            {
                int top = stk.top();
                stk.pop();
                if (stk.empty()) {
                    break;
                }

                int width = (i - stk.top() - 1);
                int h = min(height[i], height[stk.top()]) - height[top]; // stk.top() is cur idx;
                res += h * width;
            }
            stk.push(i);

        }

        return res;
    }
};


class Solution3 {
public:
    int trap(vector<int>& height) {
        auto n = height.size();
        if (n < 3) {
            return 0;
        }

        int res = 0;
        int left = 0, right = n - 1;
        int max_left = height[left], max_right = height[right];

        while (left < right)
        {
            int min_max = min(max_left, max_right);
            if (min_max > max_left) {
                ++left;
                int cur_height = height[left];
                if (cur_height < max_left) {
                    res += max_left - cur_height;
                }
                else {
                    max_left = cur_height;
                }
            }
            else {
                --right;
                int cur_height = height[right];
                if (cur_height < max_right) {
                    res += max_right - cur_height;
                }
                else {
                    max_right = cur_height;
                }
            }
        }

        return res;
    }
};