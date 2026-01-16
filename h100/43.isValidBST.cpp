/*
    medium
    BST定义：left中节点严格小于root，right中节点严格大于root
        并且left和right本身也符合这个条件
*/
#include <iostream>
#include <limits>
#include <algorithm>
#include <vector>
#include <queue>
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


// 本身是递归定义的，递归实现
class Solution {
public:

    struct Status {
        int minv;
        int maxv;
        bool valid;
    };

    Status recursiveCheck(TreeNode *root) {
        // if (root == nullptr) {
        //     // 这里有个问题，即题中val的值是有可能取int极限值的
        //     return Status {numeric_limits<int>::max(), numeric_limits<int>::min(), true};
        // }

        // 所以改成如下分开判断边界情况
        if (root->left == nullptr && root->right == nullptr) {
            return Status {root->val, root->val, true};
        }
        else if (root->left == nullptr) {
            Status rs = recursiveCheck(root->right);
            return Status {min(rs.minv, root->val), max(rs.maxv, root->val), rs.valid && (root->val < rs.minv)};
        }
        else if (root->right == nullptr) {
            Status ls = recursiveCheck(root->left);
            return Status {min(ls.minv, root->val), max(ls.maxv, root->val), ls.valid && (root->val > ls.maxv)};
        }
        
        Status ls = recursiveCheck(root->left);
        Status rs = recursiveCheck(root->right);
        int curmin = min({ls.minv, rs.minv, root->val});
        int curmax = max({ls.maxv, rs.maxv, root->val});
        bool curvalid = (root->val > ls.maxv) && (root->val < rs.minv) && ls.valid && rs.valid;
        return Status {curmin, curmax, curvalid};
    }

    bool isValidBST(TreeNode* root) {
        if (root == nullptr) return true;  // 测试中实际没有空的树，只是配合recursiveCheck不处理null
        return recursiveCheck(root).valid;
    }
};


// 更简洁的写法，但是注意到边界判断，因为会有-2^23, 2^23 -1 出现，要用longlong
class Solution2 {
public:
    long long inf = static_cast<long long>(numeric_limits<int>::max()) + 1;
    long long ninf = static_cast<long long>(numeric_limits<int>::min()) - 1;

    // 递归的时候携带最大和最小值
    bool recursiveCheck(TreeNode *root, long long minv, long long maxv) {
        if (root == nullptr) return true;
        return (root->val < maxv) && (root->val > minv) 
        && recursiveCheck(root->left, minv, root->val)
        && recursiveCheck(root->right, root->val, maxv);
    }

    bool isValidBST(TreeNode* root) {
        return recursiveCheck(root, ninf, inf);  
    }
};


// 中序遍历
// 递推形式用栈模拟调用栈
class Solution3 {
public:
   bool isValidBST(TreeNode* root) {
        stack<TreeNode*> stk;
        long long curv = static_cast<long long>(numeric_limits<int>::min()) - 1;
        while (!stk.empty() || root != nullptr)
        {
            // 处理Left
            while (root != nullptr)
            {
                stk.push(root);
                root = root->left;
            }
            // 处理mid
            root = stk.top();
            stk.pop();
            if (root->val <= curv) return false;
            curv = root->val;
            // 处理right
            root = root->right; 
        }
        return true;
    } 
};


//////////////////////////////////////////////////////////
int INT_MIN = numeric_limits<int>::min();


// 辅助函数：用层序vector生成二叉树（null用INT_MIN表示）
TreeNode* buildTree(const vector<int>& vals) {
    if (vals.empty() || vals[0] == INT_MIN) return nullptr;
    TreeNode* root = new TreeNode(vals[0]);
    queue<TreeNode*> q;
    q.push(root);
    int i = 1;
    while (!q.empty() && i < vals.size()) {
        TreeNode* node = q.front(); q.pop();
        // 左子节点
        if (i < vals.size() && vals[i] != INT_MIN) {
            node->left = new TreeNode(vals[i]);
            q.push(node->left);
        }
        i++;
        // 右子节点
        if (i < vals.size() && vals[i] != INT_MIN) {
            node->right = new TreeNode(vals[i]);
            q.push(node->right);
        }
        i++;
    }
    return root;
}


int main() {
    vector<int> vals1 = {32,26,47,19,INT_MIN,INT_MIN,56,INT_MIN,27};
    TreeNode* root1 = buildTree(vals1);


    Solution sol;
    cout << "测试用例1是否为BST: " << (sol.isValidBST(root1) ? "true" : "false") << endl;

    // 释放内存（面试可省略）
    // ...可选...

    return 0;
}