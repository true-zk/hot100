/*
    medium
    Limitation: 扫描一次 空间O(1)
    著名荷兰国旗问题，三数快速排序
*/
#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>
#include <random>


using namespace std;


// 两次遍历的想法，一个指针维护边界：第一次把0都换到边界
// 第二次把1放到0的尾巴后面

// 双指针1，p0指向0的下界（最后一个0的后面），p1指向1的下界（最后一个1后面）
// - nums[i] == 2, 不管
// - nums[i] == 1, swap(nums[i], p1), ++p1
// - nums[i] == 0, swap(nums[i], p0), 
//      如果此时p1 > p0，说明在[p0,p1)之间是连续的1，一定把一个1换到了nums[i]
//      所以需要再swap(nums[i], p1)
//      最后，无论如何要同时++p1 ++p0
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int p0 = 0, p1 = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] == 1) {
                swap(nums[i], nums[p1]);
                ++p1;
            }
            else if (nums[i] == 0) {
                swap(nums[i], nums[p0]);
                if (p1 > p0) {
                    swap(nums[i], nums[p1]);
                }
                ++p0;
                ++p1;
            }
        }
    }
};


// 还可以p0指向0的边界 000] p0，p2指向2的边界 p2 [222
// - 0: swap(nums[i], p0); ++p0
// - 2: swap(nums[i], p2); --p2, 如果nums[i]还是2，继续交换和--p2直到不是
//         如果不继续交换，可能把2换出来，并且跳到下个i，导致这个换出来的2留在这里
// - 1: 不管
// i > p2 就停止，这时候[i, n-1]全是2了
class Solution2 {
public:
    void sortColors(vector<int> &nums) {
        int p0 = 0, p2 = nums.size() - 1;
        int i = 0;
        for (int i = 0; i <= p2; ++i) {
            while (i <= p2 && nums[i] == 2)
            {
                swap(nums[i], nums[p2]);
                --p2;
            }
            if (nums[i] == 0) {
                swap(nums[i], nums[p0]);
                ++p0;
            }
        }
    }
};


void printVec(const vector<int>& nums) {
    for (int x : nums) cout << x << " ";
    cout << endl;
}

int main() {
    Solution sol;

    vector<int> nums1 = {2, 0, 2, 1, 1, 0};
    sol.sortColors(nums1);
    printVec(nums1); // 0 0 1 1 2 2

    vector<int> nums2 = {2, 0, 1};
    sol.sortColors(nums2);
    printVec(nums2); // 0 1 2

    vector<int> nums3 = {0};
    sol.sortColors(nums3);
    printVec(nums3); // 0

    vector<int> nums4 = {1, 2, 0};
    sol.sortColors(nums4);
    printVec(nums4); // 0 1 2

    return 0;
}