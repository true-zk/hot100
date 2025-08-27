#include <iostream>
using namespace std;


struct ListNode
{
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x): val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
    int val;
    ListNode *next;
};


class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {

        int carry = 0;
        ListNode *reshead = new ListNode(0);
        ListNode *p = reshead;

        while (l1 != nullptr && l2 != nullptr)
        {
            int cur = carry + l1->val + l2->val;
            carry = cur / 10;
            cur = cur % 10;
            p->next = new ListNode(cur);
            // p->next = tmp;
            p = p->next;
            l1 = l1->next;
            l2 = l2->next;
        }

        while (l1 != nullptr)
        {
            int cur = carry + l1->val;
            carry = cur / 10;
            cur = cur % 10;
            p->next = new ListNode(cur);
            // p->next = tmp;
            p = p->next;
            l1 = l1->next;
        }
        while (l2 != nullptr)
        {
            int cur = carry + l2->val;
            carry = cur / 10;
            cur = cur % 10;
            p->next = new ListNode(cur);
            // p->next = tmp;
            p = p->next;
            l2 = l2->next;
        }
        if (carry > 0) {
            p->next = new ListNode(carry);
        }
        return reshead->next;
    }
};