/*
    hard
*/
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <iostream>
#include <algorithm>

using namespace std;


// 用堆实现
// 两个优先队列，pqleft <= median, pqright > median
class MedianFinder {
    priority_queue<int, vector<int>, less<int>> pqleft;     // 大顶堆维护<= mid 的 最大的
    priority_queue<int, vector<int>, greater<int>> pqright; // 小顶堆维护 > mid 的 最小的 
public:
    MedianFinder() {}

    void addNum(int num) {

        if (pqleft.empty()) {
            pqleft.push(num);
            return;
        }

        if (num <= pqleft.top()) {  // num插入到左堆
            pqleft.push(num);
            if (pqleft.size() > pqright.size() + 1) {  // 原来是奇数，导致左比右高2，左pop，右push
                pqright.push(pqleft.top());
                pqleft.pop();
            }
            else {}  // 原来是偶数，现在左比右高1，不变
        }
        else {  // num插入右堆 (包含了右堆是空的情况)
            pqright.push(num);
            if (pqright.size() > pqleft.size()) {  // 原来是偶数，导致右比左高，右pop，左push
                pqleft.push(pqright.top());
                pqright.pop();
            }
            else {}  // 原来是奇数，现在左右高度一致，不变
        }
    }

    double findMedian() {
        if (pqleft.size() > pqright.size()) return pqleft.top();
        else return (pqleft.top() + pqright.top()) / 2.0;
    }

};


// 用multiset实现
/*
    multiset: 自动排序，底层为红黑树，插入、删除、查找均为logn
    遍历为O(n)，因为类似二叉树中序遍历，是O(n)
*/
class MedianFinder2 {
    multiset<int> nums;
    multiset<int>::iterator l, r;
public:
    MedianFinder2(): l(nums.end()), r(nums.end()) { }
    
    void addNum(int num) {
        size_t n = nums.size();  // 原size
        nums.insert(num);
        if (!n) {  // 原来是空
            l = r = nums.begin();
        }
        else if (n % 2 == 0) {  // 原来是偶数
            if (num > *l && num < *r) {
                ++l;
                --r;
            }
            else if (num >= *r) {
                ++l;
                r = l; // 考虑相等情况， 4 (5) 5，把r挤到更右边，所以l++, r = l
            }
            else {
                --r;
                l = r;  // 考虑相等情况， 4 (4) 5，把l挤到更左边，所以r--, l = r
            }
        }
        else {  // 原来是奇数
            if (num < *l) {
                --l;
            }
            else {
                ++r;
            }
        }
    }
    
    double findMedian() {
        return (*l + *r) / 2.0;
    }
};


int main() {
    MedianFinder medianFinder;
    medianFinder.addNum(1);
    medianFinder.addNum(2);
    cout << medianFinder.findMedian() << endl; // 1.5
    medianFinder.addNum(3);
    cout << medianFinder.findMedian() << endl; // 2.0
    return 0;
}