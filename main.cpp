#include <vector>

using std::vector;

// 引入头文件
#include <iostream>
#include "27.mergeTowLists.cpp"

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

// 辅助函数：释放链表
void freeList(ListNode* head) {
    while (head) {
        ListNode* tmp = head;
        head = head->next;
        delete tmp;
    }
}

int main() {
    // 构造测试用例
    std::vector<int> v1 = {1, 2, 4};
    std::vector<int> v2 = {1, 3, 4};
    ListNode* l1 = createList(v1);
    ListNode* l2 = createList(v2);

    Solution sol;
    ListNode* merged = sol.mergeTwoLists(l1, l2);

    std::cout << "Merged List: ";
    printList(merged);

    // 释放内存
    freeList(merged);
    freeList(l1);
    freeList(l2);
    return 0;
}