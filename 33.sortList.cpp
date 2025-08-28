/*
    中等
    Limitation: O(nlogn)时间复杂度，常数空间复杂度
*/
#include <iostream>
#include <algorithm>

using namespace std;


struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {} 
};


// 自顶向下归并排序
class Solution {
public:

    ListNode *findMid(ListNode *head, ListNode *tail) {
        ListNode *fastp = head, *slowp = head;
        while (fastp != tail && fastp->next != tail)
        {
            slowp = slowp->next;
            fastp = fastp->next->next;
        }
        return slowp;
    }

    // merge操作即把两个升序List合并成一条链
    ListNode *merge(ListNode *lp, ListNode *rp) {
        ListNode *pseudohead = new ListNode(0);
        ListNode *p = pseudohead;
        while (lp != nullptr && rp != nullptr)
        {
            int tmp = min(lp->val, rp->val);
            if (tmp == lp->val) {
                p->next = lp;
                lp = lp->next;
            }
            else {
                p->next = rp;
                rp = rp->next;
            }
            p = p->next;
        }

        // 这里是拼接，如果不是null说明后面都是大的，直接拼上，不需要while
        if (lp != nullptr) {
            p->next = lp;
        }
        else if (rp != nullptr)
        {
            p->next = rp;
        }
        
        return pseudohead->next;
    }

    ListNode *mergeSort(ListNode *head, ListNode *tail) {
        if (head == nullptr) {
            return head;
        }

        if (head->next == tail) {
            head->next = nullptr;  // 拆成单独的链
            return head;
        }

        // find mid and slice
        ListNode *mid = findMid(head, tail);
        return merge(mergeSort(head, mid), mergeSort(mid, tail));
    }

    ListNode* sortList(ListNode* head) {
        return mergeSort(head, nullptr);
    }

};


// O(1)空间需要自底向上的合并排序，去掉递归调用栈的空间
// 初始时subLen = 1，每次迭代*2，直到>=链表长度结束
class Solution2 {
public:
    ListNode *merge(ListNode *h1, ListNode *h2) {
        ListNode *pseudohead = new ListNode(0);
        ListNode *p = pseudohead;
        while (h1 != nullptr && h2 != nullptr)
        {
            if (h1->val < h2->val) {
                p->next = h1;
                h1 = h1->next;
            }
            else {
                p->next = h2;
                h2 = h2->next;
            }
            p = p->next;
        }

        if (h1 != nullptr) {
            p->next = h1;
        }
        else if (h2 != nullptr)
        {
            p->next = h2;
        }
        p = pseudohead->next;
        delete pseudohead;
        return p;
    }

    ListNode* sortList(ListNode* head) {
        if (head == nullptr) {
            return head;
        }

        int n = 0;
        ListNode *p = head;

        // find num of List
        while (p != nullptr)
        {
            ++n;
            p = p->next;
        }

        ListNode *pseudohead = new ListNode(0, head);
        for (int sublen = 1; sublen <= n; sublen <<= 1) {
            ListNode *prev = pseudohead, *cur = pseudohead->next;
            while (cur != nullptr)
            {
                // head1
                ListNode *head1 = cur;
                for (int i = 1; i < sublen && cur->next != nullptr; ++i) {
                    cur = cur->next;
                }

                // head2
                ListNode *head2 = cur->next;
                cur->next = nullptr;  // 截断第一段
                cur = head2;
                for (int i = 1; i < sublen && cur != nullptr && cur->next != nullptr; ++i)
                {
                    cur = cur->next;
                }
                ListNode *next = nullptr;
                if (cur != nullptr) {
                    next = cur->next;
                    cur->next = nullptr; // 截断第二段，如果cur不是null；否则不用截断
                }
                ListNode *merged = merge(head1, head2);  // merged的List的结尾是null，因为h1 h2都是截断后的
                // update prev
                prev->next = merged;  // 拼回去
                while (prev->next != nullptr)  // 迭代到merged的尾前
                {
                    prev = prev->next;
                }
                cur = next;
            }
            
        }
        p = pseudohead->next;
        delete pseudohead;
        return p; 
    }
};


void printList(ListNode* head) {
    while (head) {
        cout << head->val;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << endl;
}

// 手撕测试代码
int main() {
    // 构造链表 4 -> 2 -> 1 -> 3
    ListNode* n1 = new ListNode(4);
    ListNode* n2 = new ListNode(2);
    ListNode* n3 = new ListNode(1);
    ListNode* n4 = new ListNode(3);
    n1->next = n2;
    n2->next = n3;
    n3->next = n4;

    cout << "原链表: ";
    printList(n1);

    Solution sol;
    ListNode* sorted = sol.sortList(n1);

    cout << "排序后: ";
    printList(sorted);

    // 释放内存
    while (sorted) {
        ListNode* tmp = sorted;
        sorted = sorted->next;
        delete tmp;
    }

    return 0;
}