/*
    3508.设计路由器
    medium

    请你设计一个数据结构来高效管理网络路由器中的数据包。每个数据包包含以下属性：

    source：生成该数据包的机器的唯一标识符。
    destination：目标机器的唯一标识符。
    timestamp：该数据包到达路由器的时间戳。
    实现 Router 类：

    Router(int memoryLimit)：初始化路由器对象，并设置固定的内存限制。

    memoryLimit 是路由器在任意时间点可以存储的 最大 数据包数量。
    如果添加一个新数据包会超过这个限制，则必须移除 最旧的 数据包以腾出空间。
    bool addPacket(int source, int destination, int timestamp)：将具有给定属性的数据包添加到路由器。

    如果路由器中已经存在一个具有相同 source、destination 和 timestamp 的数据包，则视为重复数据包。
    如果数据包成功添加（即不是重复数据包），返回 true；否则返回 false。
    int[] forwardPacket()：以 FIFO（先进先出）顺序转发下一个数据包。

    从存储中移除该数据包。
    以数组 [source, destination, timestamp] 的形式返回该数据包。
    如果没有数据包可以转发，则返回空数组。
    int getCount(int destination, int startTime, int endTime)：

    返回当前存储在路由器中（即尚未转发）的，且目标地址为指定 destination 且时间戳在范围 [startTime, endTime]（包括两端）内的数据包数量。
    注意：对于 addPacket 的查询会按照 timestamp 的递增顺序进行。
*/
#include <vector>
#include <iostream>
#include <set>
#include <unordered_map>
#include <queue>
#include <tuple>  // 元组
#include <algorithm>  // binary search

using namespace std;


// umap: {destid: set { timestamp }}   // for get count
// queue: FIFO
class Router {
    deque<tuple<int, int, int>> packets_dq;  // FIFO tuple<src, dst, time>
    unordered_map<int, deque<int>> dst_map;  // dst: {time1, time2, ...}
    set<tuple<int, int, int>> isExist_set;
    int totalsize;
    int cursize;
public:
    Router(int memoryLimit): totalsize(memoryLimit), cursize(0) {
    }

    bool addPacket(int source, int destination, int timestamp) {
        auto packet = tuple<int, int, int> {source, destination, timestamp};
        if (isExist_set.count(packet)) {
            return false;
        }
        if (cursize == totalsize) {
            forwardPacket();  // rm FIFO
        }
        ++cursize;
        packets_dq.push_back(packet);
        isExist_set.insert(packet);
        dst_map[destination].push_back(timestamp);
        return true;
    }

    vector<int> forwardPacket() {
        if (cursize == 0) {
            return vector<int> {};
        }

        auto front = packets_dq.front();
        dst_map[get<1>(front)].pop_front();  // 对每个dst也是FIFO
        isExist_set.erase(front);
        packets_dq.pop_front();
        --cursize;
        return vector<int> {get<0>(front), get<1>(front), get<2>(front)};
    }

    int getCount(int destination, int startTime, int endTime) {
        auto pos1 = lower_bound(dst_map[destination].begin(), dst_map[destination].end(), startTime);
        auto pos2 = upper_bound(dst_map[destination].begin(), dst_map[destination].end(), endTime);
        return pos2 - pos1;
    }
};

/**
 * Your Router object will be instantiated and called as such:
 * Router* obj = new Router(memoryLimit);
 * bool param_1 = obj->addPacket(source,destination,timestamp);
 * vector<int> param_2 = obj->forwardPacket();
 * int param_3 = obj->getCount(destination,startTime,endTime);
 */