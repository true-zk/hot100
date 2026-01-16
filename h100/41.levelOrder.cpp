/*
    medium
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


// 递推，层次的递推一般用queue
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (root == nullptr) {
            return vector<vector<int>> {};
        }
        vector<vector<int>> res;
        vector<int> curlayer;  // 内存分配次数少
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty())
        {
            int qsize = q.size();
            while (qsize > 0)
            {
                TreeNode *tmp = q.front();
                q.pop();
                curlayer.push_back(tmp->val);
                if (tmp->left != nullptr) q.push(tmp->left);
                if (tmp->right != nullptr) q.push(tmp->right);
                --qsize;
            }
            res.push_back(curlayer);
            curlayer.clear();
        }
        return res;
    }
};


TreeNode* buildTestTree() {
    // 构造如下二叉树：
    //      1
    //     / \
    //    2   3
    //   /   / \
    //  4   5   6
    TreeNode* n4 = new TreeNode(4);
    TreeNode* n5 = new TreeNode(5);
    TreeNode* n6 = new TreeNode(6);
    TreeNode* n2 = new TreeNode(2, n4, nullptr);
    TreeNode* n3 = new TreeNode(3, n5, n6);
    TreeNode* n1 = new TreeNode(1, n2, n3);
    return n1;
}

// 打印二维vector
void print2DVec(const vector<vector<int>>& res) {
    for (const auto& layer : res) {
        for (int x : layer) cout << x << " ";
        cout << endl;
    }
}

int main() {
    TreeNode* root = buildTestTree();

    Solution sol;
    vector<vector<int>> res = sol.levelOrder(root);

    cout << "层序遍历结果:" << endl;
    print2DVec(res);

    // 释放内存（面试可省略）
    delete root->left->left;   // n4
    delete root->left;         // n2
    delete root->right->left;  // n5
    delete root->right->right; // n6
    delete root->right;        // n3
    delete root;               // n1

    return 0;
}