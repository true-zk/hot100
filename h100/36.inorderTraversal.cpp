/*
    easy
    Limitation: 递归和迭代分别实现
    附加一组morris实现，非常巧妙
*/
#include <iostream>
#include <vector>
#include <stack>
using namespace std;


struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) :val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


// 递归实现
class Solution {
public:

    void reverseInorder(TreeNode *root, vector<int> &res) {
        if (root == nullptr) return;
        reverseInorder(root->left, res);
        res.push_back(root->val);
        reverseInorder(root->right, res);
    }

    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        reverseInorder(root, res);
        return res;
    }
};


// 递推实现
// 递归的时候隐式有调用栈，递推需要模拟调用栈，当遇到空值的时候出栈
class Solution2 {
public:

    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> res;
        stack<TreeNode*> stk;

        while (root != nullptr || !stk.empty())
        {
            while (root != nullptr)
            {
                stk.push(root);  // 左边没空之前先保存root
                root = root->left;  // 跳到左边
            }
            // 最左边的可以处理了
            root = stk.top();
            stk.pop();
            res.push_back(root->val);
            root = root->right;  // root处理完了，可以处理右边了
        }
        return res;
    }
};


// 天才的Morris中序遍历算法
// O(1)空间复杂度！
// 简单而言就是每次将“左子树的最右节点(predecessor)”连到root，
// 这样遍历到predecessor就说明已经完成了左子树的遍历
/*
    1. if x->left is null, add x, goto right
    2. else, find predecessor,
        - if predecessor->right == null (第一次遍历到), right = x
        - else (第二次遍历到，已经完成了x->left遍历)，right=null, add x, goto x->right.
*/
class Solution3 {
public:
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> res;
        TreeNode *predecessor = nullptr;

        while (root != nullptr)
        {
            // root 有左子树
            if (root->left != nullptr) {
                // 1. find predecessor
                predecessor = root->left;
                while (predecessor->right != nullptr && predecessor->right != root)
                {   // predecessor->right != root是因为第一次访问完会加上predecessor->right = root
                    predecessor = predecessor->right;
                }
                
                // 2.1 if predecessor->right == null, 第一次访问
                if (predecessor->right == nullptr) {
                    predecessor->right = root;
                    root = root->left;  // 继续遍历root的左子树
                }
                // 2.2 else predecessor->right == root, 第二次访问，root左子树已经遍历完了
                else
                {
                    predecessor->right = nullptr;  // 还原
                    res.push_back(root->val);
                    root = root->right;  // 可以遍历root右子树了
                }
            }
            // root没有左子树，加入root，goto right
            else
            {
                res.push_back(root->val);
                root = root->right;
            }
        }
        return res;
    }
};


// //////////////////////////////////////////
TreeNode* buildTestTree() {
    // 构造如下二叉树：
    //      1
    //       \
    //        2
    //       /
    //      3
    TreeNode* n3 = new TreeNode(3);
    TreeNode* n2 = new TreeNode(2, n3, nullptr);
    TreeNode* n1 = new TreeNode(1, nullptr, n2);
    return n1;
}

// 辅助函数：打印vector
void printVec(const vector<int>& vec) {
    for (int x : vec) cout << x << " ";
    cout << endl;
}

int main() {
    TreeNode* root = buildTestTree();

    Solution sol1;
    Solution2 sol2;
    Solution3 sol3;

    vector<int> res1 = sol1.inorderTraversal(root);
    vector<int> res2 = sol2.inorderTraversal(root);
    vector<int> res3 = sol3.inorderTraversal(root);

    cout << "递归中序遍历: ";
    printVec(res1);

    cout << "迭代中序遍历: ";
    printVec(res2);

    cout << "Morris中序遍历: ";
    printVec(res3);

    // 释放内存（面试可省略）
    delete root->right->left;
    delete root->right;
    delete root;

    return 0;
}