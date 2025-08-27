#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};


class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode *reshead = new ListNode(0);  // pseudo head
        ListNode *p1 = list1, *p2 = list2, *p = reshead;
        while (p1 != nullptr && p2 != nullptr)
        {
            int cur = min(p1->val, p2->val);
            ListNode *curp = new ListNode(cur);
            p->next = curp;
            p = p->next;
            if (cur == p1->val) {
                p1 = p1->next;
            }
            else{
                p2 = p2->next;
            }
        }
        if (p1 == nullptr) {
            while (p2 != nullptr)
            {
                ListNode *curp = new ListNode(p2->val);
                p->next = curp;
                p = p->next;
                p2 = p2->next;
            }
        }
        else {
            while (p1 != nullptr)
            {
                ListNode *curp = new ListNode(p1->val);
                p->next = curp;
                p = p->next;
                p1 = p1->next;
            }
        }
        return reshead->next;
    }
};


// 递归做法
/*
    如果l1[0] < l2[0]: merge(l1, l2) = l1[0] <- merge(l1->next, l2)
    否则反之
*/
class Solution2 {
public:
    ListNode* mergeTwoLists(ListNode *list1, ListNode *list2) {
        // edge case
        if (list1 == nullptr) {
            return list2;
        }
        if (list2 == nullptr) {
            return list1;
        }

        // recursive process
        if (list1->val < list2->val) {
            list1->next = mergeTwoLists(list1->next, list2);
            return list1;
        }
        else
        {
            list2->next = mergeTwoLists(list2->next, list1);
            return list2;
        }

    }
};


/////////////////////// 测试辅助函数 ///////////////
// 辅助函数：根据vector创建链表
ListNode* createList(const std::vector<int>& vals) {
    ListNode dummy(0);
    ListNode* cur = &dummy;
    for (int v : vals) {
        cur->next = new ListNode(v);
        cur = cur->next;
    }
    return dummy.next;
}

// 辅助函数：打印链表
void printList(ListNode* head) {
    while (head) {
        std::cout << head->val;
        if (head->next) std::cout << " -> ";
        head = head->next;
    }
    std::cout << std::endl;
}


int main() {
    // 构造测试用例
    std::vector<int> v1 = {1, 2, 4};
    std::vector<int> v2 = {1, 3, 4};
    ListNode* l1 = createList(v1);
    ListNode* l2 = createList(v2);

    Solution2 sol;
    ListNode* merged = sol.mergeTwoLists(l1, l2);

    std::cout << "Merged List: ";
    printList(merged);

    // 释放不写
    return 0;
}