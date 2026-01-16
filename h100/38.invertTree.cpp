/*
    easy
*/
#include <iostream>
using namespace std;


struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(): val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
};


// 递归实现，对每个节点把其左右互换即可
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) return root;
        TreeNode *tmp = root->left;
        root->left = invertTree(root->right);
        root->right = invertTree(tmp);
        return root;
    }
};


////////////////////////////////////////////////
void preorderPrint(TreeNode* root) {
    if (!root) return;
    cout << root->val << " ";
    preorderPrint(root->left);
    preorderPrint(root->right);
}

// 构造测试二叉树
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

    cout << "原二叉树前序遍历: ";
    preorderPrint(root);
    cout << endl;

    Solution sol;
    TreeNode* inverted = sol.invertTree(root);

    cout << "翻转后前序遍历: ";
    preorderPrint(inverted);
    cout << endl;

    // 释放内存（面试可省略）
    delete inverted->right->right; // 原n4
    delete inverted->right;        // 原n2
    delete inverted->left;         // 原n3
    delete inverted;               // 原n1

    return 0;
}