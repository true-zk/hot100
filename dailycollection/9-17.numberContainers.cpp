/*
    2349. 设计数字容器系统
    medium

    设计一个数字容器系统，可以实现以下功能：
    在系统中给定下标处 插入 或者 替换 一个数字。
    返回 系统中给定数字的最小下标。
    请你实现一个 NumberContainers 类：

    NumberContainers() 初始化数字容器系统。
    void change(int index, int number) 在下标 index 处填入 number 。如果该下标 index 处已经有数字了，那么用 number 替换该数字。
    int find(int number) 返回给定数字 number 在系统中的最小下标。如果系统中没有 number ，那么返回 -1 。
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <set>

using namespace std;


// <O(n)的find，所以一定是hash的
// 优先队列存number对应的下标
class NumberContainers {
    unordered_map<int, int> index_map;  // idx: num
    unordered_map<int, priority_queue<int, vector<int>, greater<>>> num_pq_map;  // num: [idx1, idx2, ...]
public:
    NumberContainers() {
    }

    // O(logn) 不删除pq里面的Idx，在find的时候审查
    void change(int index, int number) {
        num_pq_map[number].push(index);
        index_map[index] = number;
    }

    // 平均O(logn)
    int find(int number) {
        if (num_pq_map.count(number)) {
            auto &pq = num_pq_map[number];
            while (!pq.empty() && index_map[pq.top()] != number)
            {
                pq.pop();
            }
            return pq.empty() ? -1 : pq.top();
        }
        else {
            return -1;
        }
    }
};


class NumberContainers2 {
    unordered_map<int, int> index_map;          // idx: num
    unordered_map<int, set<int>> num_set_map;   // num: set {idx1, idx2, ...}
    // set is ordered!
public:
    NumberContainers2() {
    }

    // O(logn)
    void change(int index, int number) {
        if (index_map.count(index)) {
            num_set_map[index_map[index]].erase(index);
        }
        index_map[index] = number;
        num_set_map[number].insert(index);
    }

    // O(logn)
    int find(int number) {
        if (!num_set_map[number].empty()) {  // 有可能被删空了
            return *num_set_map[number].begin();
        }
        else {
            return -1;
        }
    }
};


/**
 * Your NumberContainers object will be instantiated and called as such:
 * NumberContainers* obj = new NumberContainers();
 * obj->change(index,number);
 * int param_2 = obj->find(number);
 */