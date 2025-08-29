// Union-Find (Disjoint Set Union, DSU)

#include <vector>
#include <iostream>
using namespace std;

class DSU {
public:
    DSU(int n) : parent(n), rank(n, 0), count(n) {
        // 初始时每个节点是自己的父亲
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    // 查找根节点 + 路径压缩
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // 压缩路径
        }
        return parent[x];
    }

    // 合并两个集合（按秩合并）
    void unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return; // 已在同一集合

        if (rank[rx] < rank[ry]) {
            parent[rx] = ry;
        } else if (rank[rx] > rank[ry]) {
            parent[ry] = rx;
        } else {
            parent[ry] = rx;
            rank[rx]++;
        }
        count--;
    }

    // 判断两个点是否在同一集合
    bool same(int x, int y) {
        return find(x) == find(y);
    }

    // 当前集合数量
    int getCount() const {
        return count;
    }

private:
    vector<int> parent; // parent[i] 表示 i 的父亲
    vector<int> rank;   // rank[i] 表示树的近似高度
    int count;          // 当前集合的数量
};


int main() {
    DSU dsu(5); // 初始化 0~4 五个点

    dsu.unite(0, 1);
    dsu.unite(1, 2);

    cout << (dsu.same(0, 2) ? "Yes" : "No") << endl; // Yes
    cout << (dsu.same(0, 3) ? "Yes" : "No") << endl; // No

    dsu.unite(2, 3);
    cout << dsu.getCount() << endl; // 2 ( {0,1,2,3}, {4} )

    return 0;
}
