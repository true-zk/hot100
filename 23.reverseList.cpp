/*
    206. 反转链表
    easy

    给你单链表的头节点 head ，请你反转链表，并返回反转后的链表。

    史上最经典
    1. 用3个指针，pre, cur, tmp
        pre指向cur的前面     初始pre=head, pre->next = nullptr
        cur为当前，          初始cur = head->next
        tmp暂存cur->next

    2. 递归
        假设 1 -> 2 -> ... -> n -> n + 1 <- n + 2 <- ... end
        即，从n+1已经翻转了，现在在n，要翻转n和n+1之间
             - 先调用reverse(head->next)，把之后的部分翻转，完成假设
             - 然后翻转head：
                head->next->next = head;  // 把n+1的next指向自己，完成翻转head
                head->next = nullptr;     // 把自己的next指向null，否则出现环
                return head
        边界：head == nullptr || head->next == nullptr，直接返回head
*/
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