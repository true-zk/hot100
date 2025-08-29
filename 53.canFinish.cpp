/*
    medium
    [拓扑排序] 对于一个有向图G，任何一条有向边(u, v)，u在排列中都出现在v前面的排序。
        - 有环则没有拓扑排序
        - 拓扑排序不唯一（最极端的，没有边的情况，则任意排）
*/
#include <vector>
#include <queue>
#include <iostream>
using namespace std;


// dfs: 假如当前节点的相邻节点都已经完成搜索，当前节点才能完成搜索
// 用栈维护，从顶到底恰好是拓扑排序
class Solution {
public:
    vector<vector<int>> edges;  // 用邻接链表存边 edges[i] = 所有后继节点列表
    vector<int> visited;
    bool valid;

    // 对某个节点拓扑序递归，其子节点必须在自己之后遍历
    void dfs(int x) {
        visited[x] = 1;
        for (int next: edges[x]) {
            // 遍历子节点
            if (visited[next] == 0) {
                dfs(next);
                if (!valid) return;
            }
            // == 1 说明子节点正在遍历栈上，遇到了在递归栈上的子节点，有环,invalid
            else if (visited[next] == 1) {
                valid = false;
                return;
            }
        }
        visited[x] = 2;  // 2 表示所有子节点都遍历完，自己也遍历完，出栈
        // 如果在这里加一个栈，
        // stk.push(x)
        // 就能得到拓扑排序结果
    }
    
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        valid = true;
        edges.resize(numCourses);  // 初始化成空列表，方便后续直接加边
        visited.resize(numCourses);
        for (const auto pre: prerequisites) {
            edges[pre[1]].push_back(pre[0]);
        }
        // 对每个未访问的节点dfs，判断valid
        for (int i = 0; i < numCourses && valid; ++i) {
            if (!visited[i]) {
                dfs(i);
            }
        }
        return valid;
    }
};


// bfs 更直观，
// 移除没有入边的节点的出边，就能得到拓扑序
class Solution2 {
    public:
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites) {
        vector<vector<int>> edges;
        vector<int> indegree;
        edges.resize(numCourses);
        indegree.resize(numCourses);
        for (auto &pre: prerequisites) {
            edges[pre[1]].push_back(pre[0]);  // 注意顺序
            ++indegree[pre[0]];
        }

        queue<int> q;
        // 初始把所有indegree == 0 的节点入队
        for (int i = 0; i < indegree.size(); ++i) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        int visited = 0;  // 记录访问了多少节点
        while (!q.empty())
        {
            ++visited;
            int u = q.front();
            q.pop();
            // 这里如果加上把q放到res中就能输出一个拓扑排序结果
            // res.push_back(q)
            for (int v: edges[u]) {  // 这里和之前必须把当前层遍历完再push的不同，只要度为0就可以加入，不会有影响
                --indegree[v];
                if (indegree[v] == 0) {
                    q.push(v);
                }
            }
        }
        // 如果还有节点没被遍历，那肯定有环导致入度不是0
        return visited == numCourses;
    }
};


int main() {
    Solution sol;

    // 测试1：有环
    int n1 = 2;
    vector<vector<int>> pres1 = {{1, 0}, {0, 1}};
    cout << "测试1（有环），输出: " << sol.canFinish(n1, pres1) << endl; // 0

    // 测试2：无环
    int n2 = 2;
    vector<vector<int>> pres2 = {{1, 0}};
    cout << "测试2（无环），输出: " << sol.canFinish(n2, pres2) << endl; // 1

    // 测试3：无依赖
    int n3 = 3;
    vector<vector<int>> pres3 = {};
    cout << "测试3（无依赖），输出: " << sol.canFinish(n3, pres3) << endl; // 1

    // 测试4：复杂无环
    int n4 = 4;
    vector<vector<int>> pres4 = {{1,0},{2,1},{3,2}};
    cout << "测试4（链式无环），输出: " << sol.canFinish(n4, pres4) << endl; // 1

    // 测试5：复杂有环
    int n5 = 4;
    vector<vector<int>> pres5 = {{1,0},{2,1},{3,2},{0,3}};
    cout << "测试5（复杂有环），输出: " << sol.canFinish(n5, pres5) << endl; // 0

    return 0;
}