/*
    medium
*/
#include <iostream>
#include <limits>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;


struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(): val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *_left, TreeNode *_right): val(x), left(_left), right(_right) {}
};


// 层次遍历，每层的最后一个
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        if (root == nullptr) return vector<int> {};
        vector<int> res;
        queue<TreeNode*> q;
        // TreeNode *tmp;
        q.push(root);
        while (!q.empty())
        {
            int qsize = q.size();
            for (int i = 0; i < qsize; ++i) {
                root = q.front();
                q.pop();
                if (root->left != nullptr) q.push(root->left);
                if (root->right != nullptr) q.push(root->right);
            }
            // 处理好一层，恰好root为该层最右侧
            res.push_back(root->val);
        }
        return res;
    }
};


// 携带深度的DFS
class Solution2 {
public:
    void dfs(TreeNode *root, int depth, vector<int> &res) {
        if (root == nullptr) return;

        // 第一次进入当前层
        if (depth > res.size()) {
            res.push_back(root->val);
        }
        dfs(root->right, ++depth, res);
        dfs(root->left, depth, res);
    }

    vector<int> rightSideView(TreeNode *root) {
        if (root == nullptr) return vector<int> {};
        vector<int> res;
        dfs(root, 1, res);
        return res;
    }
};


int INT_MIN = numeric_limits<int>::min();
TreeNode* buildTree(const vector<int>& vals) {
    if (vals.empty() || vals[0] == INT_MIN) return nullptr;
    TreeNode* root = new TreeNode(vals[0]);
    queue<TreeNode*> q;
    q.push(root);
    int i = 1;
    while (!q.empty() && i < vals.size()) {
        TreeNode* node = q.front(); q.pop();
        // 左子节点
        if (i < vals.size() && vals[i] != INT_MIN) {
            node->left = new TreeNode(vals[i]);
            q.push(node->left);
        }
        i++;
        // 右子节点
        if (i < vals.size() && vals[i] != INT_MIN) {
            node->right = new TreeNode(vals[i]);
            q.push(node->right);
        }
        i++;
    }
    return root;
}

int main() {
    // 测试用例：[1,2,3,INT_MIN,5,INT_MIN,4]
    vector<int> vals = {1,2,3,INT_MIN,5,INT_MIN,4};
    TreeNode* root = buildTree(vals);

    Solution2 sol;
    vector<int> res = sol.rightSideView(root);

    cout << "右视图结果: ";
    for (int x : res) cout << x << " ";
    cout << endl;

    // 释放内存（面试可省略）
    // ...可选...

    return 0;
}