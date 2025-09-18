/*
    3408. 设计任务管理器
    medium

    一个任务管理器系统可以让用户管理他们的任务，每个任务有一个优先级。这个系统需要高效地处理添加、修改、执行和删除任务的操作。

    请你设计一个 TaskManager 类：
    TaskManager(vector<vector<int>>& tasks) 初始化任务管理器，初始化的数组格式为 [userId, taskId, priority] ，表示给 userId 添加一个优先级为 priority 的任务 taskId 。

    void add(int userId, int taskId, int priority) 表示给用户 userId 添加一个优先级为 priority 的任务 taskId ，输入 保证 taskId 不在系统中。

    void edit(int taskId, int newPriority) 更新已经存在的任务 taskId 的优先级为 newPriority 。输入 保证 taskId 存在于系统中。

    void rmv(int taskId) 从系统中删除任务 taskId 。输入 保证 taskId 存在于系统中。

    int execTop() 执行所有用户的任务中优先级 最高 的任务，如果有多个任务优先级相同且都为 最高 ，执行 taskId 最大的一个任务。执行完任务后，taskId 从系统中 删除 。
    同时请你返回这个任务所属的用户 userId 。如果不存在任何任务，返回 -1 。

    注意 ，一个用户可能被安排多个任务。
*/
#include <vector>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <queue>
using namespace std;


class TaskManager {
    struct Paircmp  // 自定义函数对象来实现比较
    {
        bool operator()(const pair<int, int> &l, const pair<int, int> &r) {
            return (l.first == r.first ? (l.second < r.second) : (l.first < r.first));
        }
    };
    unordered_map<int, vector<int>> task_map;  // taskid: {userid, p}
    priority_queue<pair<int, int>, vector<pair<int, int>>, Paircmp> pq;  // p, taskid
public:
    // [userId, taskId, priority]
    TaskManager(vector<vector<int>>& tasks) {
        for (auto &task: tasks) {
            task_map[task[1]] = vector<int> {task[0], task[2]};
            pq.push(pair<int, int> {task[2], task[1]});
        }
    }
    
    void add(int userId, int taskId, int priority) {
        task_map[taskId] = vector<int> {userId, priority};
        pq.emplace(priority, taskId);
    }
    
    void edit(int taskId, int newPriority) {
        task_map[taskId][1] = newPriority;
        // 直接加入pq，懒删除
        pq.emplace(newPriority, taskId);
    }
    
    void rmv(int taskId) {
        // 只删除map中的，pq中在exec的时候才检测
        task_map.erase(taskId);
    }
    
    int execTop() {
        // 非空 && (pq的top不在map中 || top的p改了)
        while (!pq.empty() && 
            (!task_map.count(pq.top().second) || 
            pq.top().first != task_map[pq.top().second][1]))
        {
            // 执行懒删除
            pq.pop();
        }
        
        // 要么空，要么top在map中，可以执行和返回
        if (pq.empty()) return -1;
        else {
            int tid = pq.top().second;
            int uid = task_map[tid][0];
            // rm
            task_map.erase(tid);
            pq.pop();
            return uid;
        }
    }
};

/**
 * Your TaskManager object will be instantiated and called as such:
 * TaskManager* obj = new TaskManager(tasks);
 * obj->add(userId,taskId,priority);
 * obj->edit(taskId,newPriority);
 * obj->rmv(taskId);
 * int param_4 = obj->execTop();
 */


 int main() {
    vector<vector<int>> tasks = {
        {1, 101, 5},
        {2, 102, 7},
        {1, 103, 7},
        {3, 104, 3}
    };
    TaskManager tm(tasks);

    cout << tm.execTop() << endl; // 1 (taskId 103, priority 7)
    tm.add(2, 105, 10);
    cout << tm.execTop() << endl; // 2 (taskId 105, priority 10)
    tm.edit(101, 10);
    cout << tm.execTop() << endl; // 1 (taskId 101, priority 10)
    tm.rmv(103);
    cout << tm.execTop() << endl; // 3 (taskId 104, priority 3)
    cout << tm.execTop() << endl; // -1 (no tasks left)

    return 0;
}