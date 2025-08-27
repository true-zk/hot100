#include <iostream>
#include <unordered_set>
using std::unordered_set;


struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};


/*
A独有a，B独有b，相交c；A长度为m, B长度为n
    a + c = m
    b + c = n
    ->
    a + c + b == b + c + a
所以分别在各自链上后移，当到尾巴的时候换到另一条的头；
直到两个链都遍历完了没找到（必然有pA == pB == nullptr） 为nullptr
否则会找到交点
*/
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (headA == nullptr || headB == nullptr) {
            return nullptr;
        }

        ListNode *pA = headA, *pB = headB;
        while (pA != nullptr || pB != nullptr)
        {
            if (pA != nullptr && pB != nullptr && pA == pB) {
                return pA;
            }

            if (pA != nullptr) {
                pA = pA->next;
            }
            else {
                pA = headB;
            }

            if (pB != nullptr) {
                pB = pB->next;
            }
            else {
                pB = headA;
            }
        }
        return nullptr;
    }
};


// 一个更简洁的写法
class Solution1 {
    public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (headA == nullptr || headB == nullptr) {  // special case
            return nullptr;
        }

        ListNode *pA = headA, *pB = headB;
        while (pA != nullptr || pB != nullptr)
        {
            pA = pA == nullptr ? headB : pA->next;
            pB = pB == nullptr ? headA : pB->next;
        }
        return pA;
    }
};


// 更直接的想法：hashset
class Solution2 {
    public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        unordered_set<ListNode *>  visited;
        ListNode *p = headA;
        while (p != nullptr)
        {
            visited.insert(p);
            p = p->next;
        }

        p = headB;
        while (p != nullptr)
        {
            if (visited.count(p) != 0) {
                return p;
            }   
            p = p->next;
        }
        return nullptr;
    }
};
