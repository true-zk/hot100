/*
    24. 两两交换链表中的节点
    medium

    给你一个链表，两两交换其中相邻的节点，并返回交换后链表的头节点。
    你必须在不修改节点内部的值的情况下完成本题（即，只能进行节点交换）。

    和翻转有点像
    三个指针+伪头部
    pre = pseudohead,
    node1 = head,
    node2 = head->next,

    pre->next = node2
    node1->next = node2->next
    node2->next = node1

    只要pre迭代即可，到pre->next->next == nullptr就停，因为没有两个node供翻转了

    还有个递归：
        - node2 = head->next
        - head->next = swap(head->next->next)
        - node2->next = head
*/
#include <iostream>
#include <vector>
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
    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        ListNode *pseudohead = new ListNode();
        pseudohead->next = head;
        ListNode *prev = pseudohead, *tmp = nullptr, *after = nullptr;
        while (prev->next != nullptr && prev->next->next != nullptr)  // 还有两个节点可换
        {
            tmp = prev->next;  // node 1
            after = prev->next->next->next;  // node 3
            prev->next = prev->next->next;  // prev -> node 2
            tmp->next = after;              // node 1 -> node 3
            prev->next->next = tmp;         // node 2 -> node 1

            // iter
            prev = prev->next->next;
        }

        prev = pseudohead->next;  // keep res head
        delete pseudohead;
        return prev;
    }
};


// 递归
class Solution2 {
public:
    ListNode *swapPairs(ListNode *head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        // swap head and head->next, and + swapPairs(head->next->next)
        ListNode *node2 = head->next;
        // ListNode *node3 = head->next->next;
        head->next = swapPairs(head->next->next);;
        node2->next = head;
        // head = node2;

        return node2;
    }
};


/////////// test auxiliary code /////////////
ListNode* createList(const vector<int> &vals) {
    ListNode pseudonode(0);
    ListNode *cur = &pseudonode;
    for (auto v: vals) {
        cur->next = new ListNode(v);
        cur = cur->next;
    }
    return pseudonode.next;
}


void printList(ListNode *head) {
    while (head != nullptr)
    {
        cout << head->val;
        if (head->next != nullptr)
        {
            cout << "->";
        }
        head = head->next;
    }
    cout <<endl;
}


void freeList(ListNode *head) {
    while (head != nullptr)
    {
        ListNode *tmp = head;
        head  = head->next;
        delete tmp;
    }
}


int main() {
    vector<int> vals {1, 2, 3, 4};
    ListNode *head = createList(vals);

    cout << "Input: ";
    printList(head);

    Solution2 sol;
    ListNode *reshead = sol.swapPairs(head);
    cout << "Output: ";
    printList(reshead);

    freeList(reshead);
    return 0;
}