/*
    medium
*/
#include <iostream>
#include <limits>
#include <algorithm>
#include <vector>
#include <stack>
#include <unordered_map>
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


// 递归判断恰好在root左右？还是只在root一边？
class Solution {
public:

    TreeNode *recursiveCheck(TreeNode *root, TreeNode *p, TreeNode *q) {
        // 有p或者q就返回root本身（非null），或者遇到边界返回null
        if (root == nullptr || root == p || root == q) return root;
        // 分别check左子树和右子树中有没有p和q
        TreeNode *inl = recursiveCheck(root->left, p, q);
        TreeNode *inr = recursiveCheck(root->right, p, q);
        // 左右都有p和q，说明root在pq中间，那就是root本身了，递归返回就行
        if (inl != nullptr && inr != nullptr) return root;
        // 只在一边，说明不是root，而是 同时出现那边 的结果
        else return (inl == nullptr) ? inr : inl;
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        return recursiveCheck(root, p, q);
    }
};


// hash存储父节点
// 从p上跳，标记；然后从q上跳，遇到的第一个被标记就是结果
class Solution2 {
public:
    TreeNode* lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
        if (root == nullptr) return root;
        unordered_map<int, TreeNode*> parent_map;  // val -> parent
        unordered_map<int, bool> vistied_by_p;  // val -> ifvisited
        // log parent for each node
        stack<TreeNode *> stk;
        stk.push(root);
        while (!stk.empty())
        {
            root = stk.top();
            stk.pop();
            if (root->left != nullptr) {
                parent_map[root->left->val] = root;
                stk.push(root->left);
            }
            if (root->right != nullptr) {
                parent_map[root->right->val] = root;
                stk.push(root->right);
            }
        }
        // logs p's Ancestor.
        vistied_by_p[p->val] = true;  // inlcudes p self.
        while (parent_map.count(p->val))
        {
            vistied_by_p[parent_map[p->val]->val] = true;
            p = parent_map[p->val];
        }
        // traverses q's Ancestor, the first visited is the answer.
        while (!vistied_by_p[q->val])
        {
            q = parent_map[q->val];
        }
        return q;
    }
};


TreeNode* buildTestTree(TreeNode*& p, TreeNode*& q) {
    // 构造如下二叉树：
    //        3
    //       / \
    //      5   1
    //     / \ / \
    //    6  2 0  8
    //      / \
    //     7   4
    TreeNode* n7 = new TreeNode(7);
    TreeNode* n4 = new TreeNode(4);
    TreeNode* n2 = new TreeNode(2, n7, n4);
    TreeNode* n6 = new TreeNode(6);
    TreeNode* n5 = new TreeNode(5, n6, n2);
    TreeNode* n0 = new TreeNode(0);
    TreeNode* n8 = new TreeNode(8);
    TreeNode* n1 = new TreeNode(1, n0, n8);
    TreeNode* root = new TreeNode(3, n5, n1);
    p = n5; // 5
    q = n1; // 1
    return root;
}

int main() {
    TreeNode* p = nullptr;
    TreeNode* q = nullptr;
    TreeNode* root = buildTestTree(p, q);

    Solution sol;
    TreeNode* ans = sol.lowestCommonAncestor(root, p, q);
    cout << "最近公共祖先（递归法）: " << (ans ? ans->val : -1) << " 应为: 3" << endl;

    // 换一组测试，p=5, q=4，最近公共祖先应为5
    p = root->left;         // 5
    q = root->left->right->right; // 4
    ans = sol.lowestCommonAncestor(root, p, q);
    cout << "最近公共祖先（递归法）: " << (ans ? ans->val : -1) << " 应为: 5" << endl;

    // Solution2测试
    p = root->left;         // 5
    q = root->right;        // 1
    Solution2 sol2;
    ans = sol2.lowestCommonAncestor(root, p, q);
    cout << "最近公共祖先（哈希法）: " << (ans ? ans->val : -1) << " 应为: 5" << endl;

    return 0;
}