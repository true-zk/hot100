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
    TreeNode(int x, TreeNode *_left, TreeNode *_right): val(x), left(_left), right(_right) {}
};


// mid作为root，左边是左子树，右边是右子树
class Solution {
public:
    TreeNode *recursiveToBST(vector<int> &nums, int l, int r) {
        if (l == r) {
            return new TreeNode(nums[l]);
        }
        else if (l > r)
        {
            return nullptr;
        }
        
        int mid = l + (r - l) / 2;
        // int mid = l + (r - l + 1) / 2;  // 另一种形式的遍历树，偏右点
        // 还可以 +rand() % 2，实现随机
        TreeNode *root = new TreeNode(nums[mid]);
        root->left = recursiveToBST(nums, l, mid - 1);
        root->right = recursiveToBST(nums, mid + 1, r);
        return root;
    }

    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return recursiveToBST(nums, 0, nums.size() - 1);
    }
};


// 前序遍历打印二叉树
void preorderPrint(TreeNode* root) {
    if (!root) return;
    cout << root->val << " ";
    preorderPrint(root->left);
    preorderPrint(root->right);
}


int main() {
    vector<int> nums = {-10, -3, 0, 5, 9};

    Solution sol;
    TreeNode* root = sol.sortedArrayToBST(nums);

    cout << "前序遍历BST: ";
    preorderPrint(root);
    cout << endl;

    // 释放内存（面试可省略）
    // ...可选...

    return 0;
}