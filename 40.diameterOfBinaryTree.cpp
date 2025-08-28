/*
    easy
*/
#include <iostream>
#include <algorithm>
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


// 递归实现
// 注意到，直径必然过 某个 根，只是有可能不是最顶层的根而已，
// 所以加一个全局res记录max即可
class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        if (root == nullptr) return 0;
        res = 0;
        depth(root);
        return res-1;  // length比node数少一
    }

private:
    int res;
    int depth(TreeNode *root) {
        if (root == nullptr) return 0;
        int dl = depth(root->left);
        int dr = depth(root->right);
        // 这里是node的数量，真正的res在最后的时候还要-1
        res = (dl + dr + 1 > res) ? (dl + dr + 1) : res;
        return max(dl, dr) + 1;
    }
};


/*  有点想麻烦了 */
// 递归实现，
// maxlen = max(ldiameter, rdiameter, 跨过中间max)
// 跨过中间max = 左最深 + 右最深
class Solution2 {
public:
    struct Status
    {
        int diameter;
        int depth;
    };
    
    Status recursiveDiameter(TreeNode *root) {
        if (root == nullptr) return Status {0, 0};
        Status ls = recursiveDiameter(root->left);
        Status rs = recursiveDiameter(root->right);
        int cur_diameter = max(ls.diameter, rs.diameter);
        int cur_depth = max(ls.depth, rs.depth) + 1;
        cur_diameter = max(cur_diameter, ls.depth + rs.depth + 1);
        return Status {cur_diameter, cur_depth};
    }

    int diameterOfBinaryTree(TreeNode* root) {
        if (root == nullptr) return 0;
        Status res = recursiveDiameter(root);
        return res.diameter - 1;
    }
};


TreeNode* buildTestTree() {
    // 构造如下二叉树：
    //      1
    //     / \
    //    2   3
    //   / \     
    //  4   5   
    TreeNode* n4 = new TreeNode(4);
    TreeNode* n5 = new TreeNode(5);
    TreeNode* n2 = new TreeNode(2, n4, n5);
    TreeNode* n3 = new TreeNode(3);
    TreeNode* n1 = new TreeNode(1, n2, n3);
    return n1;
}


int main() {
    TreeNode* root = buildTestTree();

    Solution2 sol;
    int diameter = sol.diameterOfBinaryTree(root);

    cout << "二叉树的直径: " << diameter << endl; // 期望输出: 3

    // 释放内存（面试可省略）
    delete root->left->left;   // n4
    delete root->left->right;  // n5
    delete root->left;         // n2
    delete root->right;        // n3
    delete root;               // n1

    return 0;
}