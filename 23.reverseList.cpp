#include <iostream>
#include <unordered_set>
using std::unordered_set;


struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};


// 最常见的3个指针方法
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr) {
            return nullptr;
        }

        ListNode *prv = head, *cur = head->next;
        ListNode *tmp;
        prv->next = nullptr;
        while (cur != nullptr)
        {
            tmp = cur->next;
            cur->next = prv;
            prv = cur;
            cur = tmp;
        }
        return prv;
    }
};


// 递归写法，
/*
    reverseList(head) 返回翻转后的newhead节点；
    退出条件：当head为nullptr或者head->next == nullptr

    在一次递归中，前面（包括现在的head）是没反转的，后面是反转好的，
    所以只需要把连接的地方反过来，然后返回newhead即可
*/
// 空间复杂度受限于递归栈 O(n)
class Solution2 {
    ListNode *reverseList(ListNode *head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        ListNode *newhead = reverseList(head->next);  // 后面的已经反转
        // head为k
        // 反转k和k+1的连接
        // ... -> k-1 -> k(head) -> k+1 <- k+2 <- k+3 <- ... <- newhead
        head->next->next = head;  // k->next == k+1，反转，即 k+1->next = k
        // 现在的head变成了“队尾”，其next应该是null
        head->next = nullptr;
        // return新的队首给前面的调用
        return newhead;
    }
};