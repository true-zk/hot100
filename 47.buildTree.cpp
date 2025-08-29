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


class Solution {
public:
    TreeNode *recursiveBuild(vector<int> &preorder, vector<int> &inroder, int lpre, int rpre, int lin, int rin) {
        if (lpre > rpre || lin > rin) {
            return nullptr;
        }
        else if (lpre == rpre) {
            return new TreeNode(preorder[lpre]);
        }

        TreeNode *root = new TreeNode(preorder[lpre]);
        int inrootidx = lin, preleftbound;
        while (inroder[inrootidx] != root->val)  // 这里找inrootindex是O(n)的，可以用hashtable优化成O(1)
        {
            ++inrootidx;
        }
        preleftbound = lpre + (inrootidx - lin);

        // preorder: lpre [lpre + 1, preleftbound] [preleftbound + 1, rpre]
        // inorder： [lin, inrootidx - 1] inrootidx [inrootidx + 1, rin]

        root->left = recursiveBuild(preorder, inroder, lpre + 1, preleftbound, lin, inrootidx - 1);
        root->right = recursiveBuild(preorder, inroder, preleftbound + 1, rpre, inrootidx + 1, rin);
        return root;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return recursiveBuild(preorder, inorder, 0, preorder.size() - 1, 0, inorder.size() - 1);
    }
};


// 递推形式，相对复杂
class Solution2 {
public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        if (!preorder.size()) {
            return nullptr;
        }

        TreeNode *root = new TreeNode(preorder[0]);
        stack<TreeNode *> stk;
        stk.push(root);
        int inorderIndex = 0;
        for (int i = 1; i < preorder.size(); ++i) {
            int preorderVal = preorder[i];
            TreeNode *topnode = stk.top();
            // 如果此时 栈顶 和 inorderIndex位置的值 不一致，
            // pre[i]一定是栈顶的左儿子：创建，连接，入栈
            if (topnode->val != inorder[inorderIndex]) {
                topnode->left = new TreeNode(preorderVal);
                stk.push(topnode->left);
            }
            // 否则，pre[i]是栈中某个节点的右儿子
            else {
                // 如果一路都是没右儿子下来的，那么 inorderIndex和栈顶始终相等
                while (!stk.empty() && stk.top()->val == inorder[inorderIndex])
                {
                    ++inorderIndex;
                    topnode = stk.top();
                    stk.pop();
                }
                // 第一个不相等的位置，说明此时栈顶节点topnode有右儿子，也就是pre[i]
                topnode->right = new TreeNode(preorderVal);
                // 继续
                stk.push(topnode->right);
            }
        }
        return root;
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
    // 测试用例：前序和中序
    vector<int> preorder = {3,9,20,15,7};
    vector<int> inorder = {9,3,15,20,7};

    Solution2 sol;
    TreeNode* root = sol.buildTree(preorder, inorder);

    cout << "重建后的二叉树前序遍历: ";
    preorderPrint(root);
    cout << endl;

    // 释放内存（面试可省略）
    // ...可选...

    return 0;
}