/*
    medium
    经典双指针问题
    以短的柱子作为蓄水的h，r - l作为w
    所以，短的柱子的指针往中间收缩
*/

#include <vector>

using namespace std;

/*
Obvious bi-direction problem, uses 2 pointers.
*/

class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0;
        int right = height.size() - 1;
        int res = (right - left) * min(height[right], height[left]);
        while (left < right) {
            int cur_height = min(height[left], height[right]);
            if (height[left] == cur_height) {
                do
                {
                    left++;
                } while (height[left] <= cur_height && left < right);
                
                if (left != right) {
                    int cur = min(height[left], height[right]) * (right - left);
                    if (cur > res) {
                        res = cur;
                    }
                }
            }
            else {
                do
                {
                    right--;
                } while (height[right] <= cur_height && left < right);

                if (left != right) {
                    int cur = min(height[left], height[right]) * (right - left);
                    if (cur > res) {
                        res = cur;
                    }
                }
            }
        }
        return res;
    }
};