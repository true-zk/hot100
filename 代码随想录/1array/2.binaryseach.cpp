/*
    二分有两种写法：[l, r] 和 [l, r)
*/
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

class BinarySearch {
public:
    /*
        [l, r] 写法
    */
    int binarySearch1(vector<int> &arr, int l, int r, int tgt) {
        while (l <= r) {    // 闭区间，l == r有意义
            int mid = l + (r - l) / 2;
            if (arr[mid] > tgt) {
                r = mid - 1;    // 闭区间，mid一定不是下一个闭区间
            }
            else if (arr[mid] < tgt) {
                l = mid + 1;
            }
            else {
                return mid;
            }
        }
        return -1;
    }

    /*
        [l, r) 写法
    */
   int binarySearch2(vector<int> &arr, int l, int r, int tgt) {
        while (l < r)   // 开区间，l == r的时候没有元素
        {
            int mid = l + (r - l) / 2;
            if (arr[mid] > tgt) {
                r = mid;    // 右开区间
            }
            else if (arr[mid] < tgt) {
                l = mid + 1;
            }
            else {
                return mid;
            }
        }
        return -1;
   }
};

///////////////////////////////////////////////
class Solution {
public:
    /*
        [l, r]
        下界就是 第一个 >=tgt 的idx
        ... tgt [lower_bound ...

        闭区间，所以大于和小于的情况都好写，
        关键是==的时候，r = mid - 1;
    */
    int lowerbound(vector<int> &arr, int l, int r, int tgt) {
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (arr[mid] >= tgt) {
                r = mid - 1;    // 相等，r会到mid = 1，后续l = mid + 1会自然移到lower_bound
            }
            else {
                l = mid + 1;
            }
        }
        return l;
    }

    /*
        [l, r]
        上界就是 第一个 >tgt 的idx
        ... tgt (upper_bound ...

        闭区间，所以大于和小于的情况都好写，
        关键是==的时候，l = mid + 1;
    */
    int upperbound(vector<int> &arr, int l, int r, int tgt) {
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (arr[mid] > tgt) {
                r = mid - 1;
            }
            else {
                l = mid + 1;    // 相等，l = mid + 1，就是上界
            }
        }
        return l;
    }
};


int main() {
    Solution sol;
    vector<int> arr = {1, 2, 4, 4, 5, 7};
    cout << sol.lowerbound(arr, 0, arr.size() - 1, 4) << endl; // 2
    cout << sol.lowerbound(arr, 0, arr.size() - 1, 3) << endl; // 2
    cout << sol.lowerbound(arr, 0, arr.size() - 1, 8) << endl; // 6
    cout << sol.lowerbound(arr, 0, arr.size() - 1, 0) << endl; // 0
    return 0;
}
