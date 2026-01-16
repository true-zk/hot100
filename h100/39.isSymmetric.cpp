/*
    easy
*/
#include <iostream>
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


// 递归实现，
// 对称 = left和right根一样，并且left->right和right->left相等，反之亦然
class Solution {
public:
    bool checklr(TreeNode *p, TreeNode *q) {
        if (p == nullptr && q == nullptr) return true;
        else if (p == nullptr || q == nullptr) return false;
        return (p->val == q->val) && checklr(p->left, q->right) && checklr(p->right, q->left);
    }

    bool isSymmetric(TreeNode* root) {
        if (root == nullptr) return true;

        return checklr(root->left, root->right);
    }
};


// 递推实现
// 这里用队列模拟调用栈，因为是一个广搜的过程（每次处理一层）
class Solution2 {
public:
    bool isSymmetric(TreeNode *root) {
        if (root == nullptr) return true;
        queue<TreeNode*> q;
        TreeNode *u, *v;
        q.push(root->left);
        q.push(root->right);
        while (!q.empty())
        {
            u = q.front();
            q.pop();
            v = q.front();
            q.pop();
            if (u == nullptr && v == nullptr) continue;
            else if (u == nullptr || v == nullptr) return false;
            if (u->val != v->val) return false;
            q.push(u->left);
            q.push(v->right);
            q.push(u->right);
            q.push(v->left);
        }
        return true;
    }
};


TreeNode* buildSymmetricTree() {
    // 构造如下对称二叉树：
    //      1
    //     / \
    //    2   2
    //   / \ / \
    //  3  4 4  3
    TreeNode* n1 = new TreeNode(1);
    TreeNode* n2a = new TreeNode(2);
    TreeNode* n2b = new TreeNode(2);
    TreeNode* n3a = new TreeNode(3);
    TreeNode* n3b = new TreeNode(3);
    TreeNode* n4a = new TreeNode(4);
    TreeNode* n4b = new TreeNode(4);
    n1->left = n2a; n1->right = n2b;
    n2a->left = n3a; n2a->right = n4a;
    n2b->left = n4b; n2b->right = n3b;
    return n1;
}

TreeNode* buildAsymmetricTree() {
    // 构造如下非对称二叉树：
    //      1
    //     / \
    //    2   2
    //     \    \
    //      3    3
    TreeNode* n1 = new TreeNode(1);
    TreeNode* n2a = new TreeNode(2);
    TreeNode* n2b = new TreeNode(2);
    TreeNode* n3a = new TreeNode(3);
    TreeNode* n3b = new TreeNode(3);
    n1->left = n2a; n1->right = n2b;
    n2a->right = n3a;
    n2b->right = n3b;
    return n1;
}

int main() {
    Solution sol;
    Solution2 sol2;

    TreeNode* root1 = buildSymmetricTree();
    TreeNode* root2 = buildAsymmetricTree();

    cout << "对称树递归判断: " << (sol.isSymmetric(root1) ? "true" : "false") << endl;
    cout << "对称树迭代判断: " << (sol2.isSymmetric(root1) ? "true" : "false") << endl;

    cout << "非对称树递归判断: " << (sol.isSymmetric(root2) ? "true" : "false") << endl;
    cout << "非对称树迭代判断: " << (sol2.isSymmetric(root2) ? "true" : "false") << endl;

    // 释放内存（面试可省略）
    // ...可选...

    return 0;
}