/*
    2. 两数相加
    medium

    给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。
    请你将两个数相加，并以相同形式返回一个表示和的链表。
    你可以假设除了数字 0 之外，这两个数都不会以 0 开头。

    从头直接加就行，注意进位，注意结束之后，把不是null的那串放到结果后面
*/
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