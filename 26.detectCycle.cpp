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

    /*
        此时，已知point在环里，永远出不了。
        加一个从head开始的ptr，如果都是step为1的慢指针，总会相遇在交点。因为：
        因为：
            非环部分为a
            相遇的时候：将环切分成b + c，b是慢指针走过的部分，c是没走的
            慢指针走过 x = a + b
            快指针走过 2x = a + n (b + c) + b  // n圈(b + c) size的环
            2(a + b) = a + (n + 1)b + nc  ->  a = nc + (n - 1)b = c + (n - 1)(b + c)
        所以：
            a = c + (n - 1)(b + c)  // a其实为(n - 1)圈环再加上多出来的c
            那么这时，引入新指针ptr从head开始走，当走到交点的时候，也就是走了a，同时慢指针走完了c + (n - 1)(环)，也到了交点！
    */
    ListNode *slowheadPtr(ListNode *head, ListNode *point) {
        ListNode *slow = point, *ptr = head;
        while (ptr != slow)
        {
            ptr = ptr->next;
            slow = slow->next;
        }
        return ptr;

    }

    ListNode* detectCycle(ListNode *head) {
        if (head == nullptr or head->next == nullptr) {
            return nullptr;
        }

        auto point = fastslowPtr(head);
        if (point == nullptr) {
            return nullptr;
        }
        else {
            return slowheadPtr(head, point);
        }
    }
};


int main() {
    // 测试1：无环
    ListNode* head1 = new ListNode(1);
    head1->next = new ListNode(2);
    head1->next->next = new ListNode(3);

    Solution sol;
    ListNode* res1 = sol.detectCycle(head1);
    cout << "无环测试: ";
    if (res1) {
        cout << "环起点值为 " << res1->val << endl;
    } else {
        cout << "无环" << endl;
    }

    // 释放内存
    delete head1->next->next;
    delete head1->next;
    delete head1;

    // 测试2：有环，环起点为2
    ListNode* head2 = new ListNode(1);
    head2->next = new ListNode(2);
    head2->next->next = new ListNode(3);
    head2->next->next->next = head2->next; // 构成环，起点为2

    ListNode* res2 = sol.detectCycle(head2);
    cout << "有环测试: ";
    if (res2) {
        cout << "环起点值为 " << res2->val << endl;
    } else {
        cout << "无环" << endl;
    }

    // 有环链表不能直接delete，否则死循环，面试时可省略释放

    return 0;
}
