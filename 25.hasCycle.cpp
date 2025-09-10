/*
    141. 环形链表
    easy

    给你一个链表的头节点 head ，判断链表中是否有环。

    快慢指针
*/
#include <iostream>
using namespace std;


struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};


/*
Limitation: O(1)内存
*/
class Solution {
public:

    /*
        快慢指针实现O(1)内存操作：当快慢指针相遇的时候，存在环，
        如果快指针能走到结尾（nullptr），那肯定没有环
    */
    ListNode *fastslowPtr(ListNode *head) {
        ListNode *fast = head, *slow = head;
        do
        {
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow) {
                return fast;
            }
        } while (fast != nullptr && fast->next != nullptr);
        return nullptr;
    }

    bool hasCycle(ListNode *head) {
        if (head == nullptr or head->next == nullptr) {
            return false;
        }
        
        auto point = fastslowPtr(head);
        if (point == nullptr) {
            return false;
        }
        else {
            return true;
        }
    }
};



int main() {
    // 测试1：无环
    ListNode* head1 = new ListNode(1);
    head1->next = new ListNode(2);
    head1->next->next = new ListNode(3);

    Solution sol;
    cout << "无环测试: " << (sol.hasCycle(head1) ? "true" : "false") << endl;

    // 释放内存
    delete head1->next->next;
    delete head1->next;
    delete head1;

    // 测试2：有环
    ListNode* head2 = new ListNode(1);
    head2->next = new ListNode(2);
    head2->next->next = new ListNode(3);
    head2->next->next->next = head2->next; // 构成环

    cout << "有环测试: " << (sol.hasCycle(head2) ? "true" : "false") << endl;

    // 注意：有环链表不能直接delete，否则死循环，面试时可省略释放

    return 0;
}