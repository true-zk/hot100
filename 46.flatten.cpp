/*
    medium
*/
#include <iostream>
#include <limits>
#include <algorithm>
#include <vector>
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


// 先序遍历，前一个node恰好就是下一个node的prev，
class Solution {
public:

    TreeNode *prev;  // 全局的，这样才能正常连接

    void recursivePreorder(TreeNode *root) {
        if (root == nullptr) return;
        
        prev->right = root;
        prev->left = nullptr;
        prev = prev->right;
        TreeNode *tmpr = root->right;  // 这里一定要用局部变量保持，不然会丢失
        recursivePreorder(root->left);
        recursivePreorder(tmpr);
    }

    void flatten(TreeNode* root) {
        if (root == nullptr) return;
        TreeNode *head = new TreeNode();
        prev = head;
        recursivePreorder(root);
        delete head;
    }
};


// 更直观的做法，直接前序遍历然后记录在vector，然后再更新
class Solution2 {
public:
    void flatten(TreeNode *root) {
        vector<TreeNode*> vec;
        stack<TreeNode*> stk;
        TreeNode *p = root;
        while (p != nullptr || !stk.empty())
        {
            while (p != nullptr)
            {
                vec.push_back(p);  // 处理中
                stk.push(p);
                p = p->left;  // 先往左走
            }
            // p == null说明中、左都结束了，处理右
            p = stk.top();
            stk.pop();
            p = p->right;
        }
        TreeNode *prev, *cur;
        for (int i = 1; i < vec.size(); ++i) {
            prev = vec[i - 1];
            cur = vec[i];
            prev->right = cur;
            prev->left = nullptr;
        }
    }
};


TreeNode* buildTestTree() {
    // 构造如下二叉树：
    //      1
    //     / \
    //    2   5
    //   / \   \
    //  3   4   6
    TreeNode* n3 = new TreeNode(3);
    TreeNode* n4 = new TreeNode(4);
    TreeNode* n6 = new TreeNode(6);
    TreeNode* n2 = new TreeNode(2, n3, n4);
    TreeNode* n5 = new TreeNode(5, nullptr, n6);
    TreeNode* n1 = new TreeNode(1, n2, n5);
    return n1;
}

// 打印链表
void printFlattened(TreeNode* root) {
    while (root) {
        cout << root->val << " ";
        if (root->left) {
            cout << "(错误: left不为nullptr!) ";
            break;
        }
        root = root->right;
    }
    cout << endl;
}

int main() {
    TreeNode* root = buildTestTree();

    // Solution1 测试
    Solution sol1;
    sol1.flatten(root);
    cout << "flatten后链表（递归法）: ";
    printFlattened(root);

    // 重新构造树
    root = buildTestTree();

    // Solution2 测试
    Solution2 sol2;
    sol2.flatten(root);
    cout << "flatten后链表（迭代法）: ";
    printFlattened(root);

    // 释放内存（面试可省略）
    // ...可选...

    return 0;
}