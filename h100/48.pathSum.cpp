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


// 暴力，迭代节点，对每个节点进行深搜，相当于两次深搜，N^2
class Solution {
public:

    int global_targetSum;
    int res;

    void dfs(TreeNode *root, long long presum) {
        if (root == nullptr) return;
        presum += root->val;
        if (presum == global_targetSum) ++res;
        dfs(root->left, presum);
        dfs(root->right, presum);
    }

    int pathSum(TreeNode* root, int targetSum) {
        if (root == nullptr) return 0;
        global_targetSum = targetSum;
        res = 0;

        // traverse all node
        stack<TreeNode*> stk;
        stk.push(root);
        while (!stk.empty())
        {
            root = stk.top();
            stk.pop();
            dfs(root, 0);
            if (root->left != nullptr) stk.push(root->left);
            if (root->right != nullptr) stk.push(root->right);
        }

        return res;
    }
};


// 另一种暴力，
class Solution2 {
public:
    // 递归处理每个目标节点
    // 这里仍然需要Long long，因为不断求减法也是一样的累计-0-
    int dfsres(TreeNode *root, long long targetVal) {
        if (root == nullptr) return 0;
        int cur_res = 0;
        if (root->val == targetVal) ++cur_res;
        cur_res += dfsres(root->left, targetVal - root->val);
        cur_res += dfsres(root->right, targetVal - root->val);
        return cur_res;
    }
    // 递归遍历每个节点
    int pathSum(TreeNode *root, int targetSum) {
        if (root == nullptr) return 0;
        int res = 0;
        res += dfsres(root, targetSum);
        res += pathSum(root->left, targetSum);
        res += pathSum(root->right, targetSum);
        return res;
    }
    // 当然也可以递推遍历每个节点
    int pathSum2(TreeNode *root, int targetSum) {
        if (root == nullptr) return 0;
        int res = 0;
        stack<TreeNode*> stk;
        stk.push(root);
        while (!stk.empty())
        {
            root = stk.top();
            stk.pop();
            res += dfsres(root, targetSum);
            if (root->left != nullptr) stk.push(root->left);
            if (root->right != nullptr) stk.push(root->right);
        }
        return res;
    }  
};


// 前缀和优化！
// O(N) 省去了重复前缀计算
class Solution3 {
public:
    // 保存(prefixsum, count)，前缀和，和前缀和出现的次数(也就是这个前缀和的路径数)
    unordered_map<long long, int> prefixsum;

    int dfs(TreeNode *root, long long cur, const int &targetSum) {
        if (root == nullptr) return 0;

        int res = 0;
        cur += root->val;
        if (prefixsum.count(cur - targetSum)) {
            res += prefixsum[cur - targetSum];
        }

        // 更新前缀和
        ++prefixsum[cur];
        // 继续深搜
        res += dfs(root->left, cur, targetSum);
        res += dfs(root->right, cur, targetSum);
        // ！这里一定要及时--，因为对当前node往下的部分已经遍历完了，
        // 剩下的部分不含当前node的前缀和
        --prefixsum[cur];
        return res;
    }

    int pathSum(TreeNode *root, int targetSum) {
        prefixsum[0] = 1;  // 空路径
        return dfs(root, 0, targetSum);
    }
};


TreeNode* buildTestTree() {
    // 构造如下二叉树：
    //      10
    //     /  \
    //    5   -3
    //   / \    \
    //  3   2    11
    // / \   \
    //3  -2   1
    TreeNode* n3a = new TreeNode(3);
    TreeNode* n_2 = new TreeNode(-2);
    TreeNode* n1 = new TreeNode(1);
    TreeNode* n11 = new TreeNode(11);
    TreeNode* n3b = new TreeNode(3, n3a, n_2);
    TreeNode* n2 = new TreeNode(2, nullptr, n1);
    TreeNode* n5 = new TreeNode(5, n3b, n2);
    TreeNode* n_3 = new TreeNode(-3, nullptr, n11);
    TreeNode* root = new TreeNode(10, n5, n_3);
    return root;
}

int main() {
    TreeNode* root = buildTestTree();
    int targetSum = 8;

    Solution sol;
    int res = sol.pathSum(root, targetSum);
    cout << "路径和为" << targetSum << "的路径数量: " << res << endl; // 期望输出：3

    // 释放内存（面试可省略）
    // ...可选...

    return 0;
}