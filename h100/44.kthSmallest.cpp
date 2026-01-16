/*
    medium
    给的是BTS
    Limitation: 如果需要频繁修改树，如何优化？
    TODO: 这个优化比较复杂，后续再做
*/
#include <iostream>
#include <limits>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
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


// 中序遍历，用stack模拟递推
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        stack<TreeNode*> stk;
        while (!stk.empty() || root!=nullptr)
        {
            while (root != nullptr)
            {
                stk.push(root);
                root = root->left;
            }
            root = stk.top();
            stk.pop();
            --k;
            if (k == 0) return root->val;
            root = root->right;
        }
        return -1;  // should never occur, only for return type.
    }
};


int INT_MIN = numeric_limits<int>::min();
// 辅助函数：用层序vector生成二叉树
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
    // 测试用例：BST [5,3,6,2,4,INT_MIN,INT_MIN,1]
    vector<int> vals = {5,3,6,2,4,INT_MIN,INT_MIN,1};
    TreeNode* root = buildTree(vals);

    Solution sol;
    int k = 3;
    int res = sol.kthSmallest(root, k);
    cout << "第" << k << "小的元素是: " << res << endl; // 期望输出：3

    // 释放内存（面试可省略）
    // ...可选...

    return 0;
}