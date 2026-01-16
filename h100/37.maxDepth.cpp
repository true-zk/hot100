/*
    easy
    dfs 和 bfs实现
*/
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;


struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(): val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
};


// 递归实现: dfs
// for root: d = max(left, right) + 1
class Solution {
public:
    int maxDepth(TreeNode *root) {
        if (root == nullptr) {
            return 0;
        }

        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};


// 递推实现：bfs
// 层次遍历
class Solution1 {
public:
    int maxDepth(TreeNode *root) {
        if (root == nullptr) return 0;

        queue<TreeNode*> q;
        int res = 0;
        q.push(root);
        while (!q.empty())
        {
            int sz = q.size();
            while (sz > 0)  // 当前层
            {
                TreeNode *node = q.front();
                q.pop();
                if (node->left != nullptr) q.push(node->left);
                if (node->right != nullptr) q.push(node->right);
                --sz;
            }
            ++res;
        }
        return res;
    }
};


TreeNode* buildTestTree() {
    // 构造如下二叉树：
    //      1
    //     / \
    //    2   3
    //   /
    //  4
    TreeNode* n4 = new TreeNode(4);
    TreeNode* n2 = new TreeNode(2);
    n2->left = n4;
    TreeNode* n3 = new TreeNode(3);
    TreeNode* n1 = new TreeNode(1);
    n1->left = n2;
    n1->right = n3;
    return n1;
}


int main() {
    TreeNode* root = buildTestTree();

    Solution sol;
    Solution1 sol1;

    int depth_dfs = sol.maxDepth(root);
    int depth_bfs = sol1.maxDepth(root);

    cout << "DFS递归最大深度: " << depth_dfs << endl;
    cout << "BFS层序最大深度: " << depth_bfs << endl;

    // 释放内存（面试可省略）
    delete root->left->left;
    delete root->left;
    delete root->right;
    delete root;

    return 0;
}