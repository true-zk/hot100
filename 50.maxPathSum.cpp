/*
    hard
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


// 最大的要么跨过root，要么不跨过
// 需要记录下到root的左右分别最大的部分，用来计算当前最大
class Solution {
public:

    int minv = -1001;

    struct Status
    {
        int maxpathsum;
        int max2root;
    };

    Status recursiveMaxPathSum(TreeNode *root) {
        if (root == nullptr) return Status {minv, minv};
        Status ls = recursiveMaxPathSum(root->left);
        Status rs = recursiveMaxPathSum(root->right);
        int curmax2root = max({
            root->val,
            root->val + ls.max2root,
            root->val + rs.max2root,
            // root->val + ls.max2root + rs.max2root  // 要么选左 要么选右 不能都选，不然终点就不是root了
        });
        int curmaxpathsum = max({
            ls.maxpathsum,
            rs.maxpathsum,
            curmax2root,
            root->val + ls.max2root + rs.max2root,  // 这里还有跨过root的可能
        });
        return Status {curmaxpathsum, curmax2root};
    }
    
    int maxPathSum(TreeNode* root) {
        return recursiveMaxPathSum(root).maxpathsum;
    }
};


// 基本思想差不多，但是换个想法：每次递归返回当前root的最大“贡献”
// 即以当前root为结束的最长路径
// 最长路径作为全局变量来维护，要么跨过，要么是左右最大“贡献”的一个
// 注意到，贡献最小设置为0（负贡献没意义）
class Solution2 {
public:
    int res = numeric_limits<int>::min();
    int recursiveScore(TreeNode *root) {
        if (root == nullptr) return 0;

        int leftScore = recursiveScore(root->left);
        leftScore = max(leftScore, 0);   // 最小贡献设置为0
        int rightScore = recursiveScore(root->right);
        rightScore = max(rightScore, 0);  // 最小贡献设置为0
        // 更新结果
        res = max(res, root->val + leftScore + rightScore);
        // 返回Score贡献
        return max({root->val + leftScore, root->val + rightScore, root->val});
    }

    int maxPathSum(TreeNode *root) {
        res = numeric_limits<int>::min();
        recursiveScore(root);
        return res;
    }
};


TreeNode* buildTestTree() {
    // 构造如下二叉树：
    //      -10
    //      /  \
    //     9   20
    //        /  \
    //       15   7
    TreeNode* n15 = new TreeNode(15);
    TreeNode* n7 = new TreeNode(7);
    TreeNode* n20 = new TreeNode(20, n15, n7);
    TreeNode* n9 = new TreeNode(9);
    TreeNode* root = new TreeNode(-10, n9, n20);
    return root;
}

int main() {
    TreeNode* root = buildTestTree();

    Solution sol;
    int res = sol.maxPathSum(root);
    cout << "最大路径和: " << res << endl; // 期望输出：42

    // 释放内存（面试可省略）
    // ...可选...

    return 0;
}