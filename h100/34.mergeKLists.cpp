/*
    hard
    总链数k，每条链长度为n
*/
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;


struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {} 
};


// 分治+递归，分治做法的话，递归是很容易实现的
// 第一次合并 k/2次 每次时间 2n
// 第二次合并 k/4次 每次时间 4n
// ...
// O(\sum_{i = 1}^{∞} k/2^i 2^i n)
// O(nklogk)
// 空间：需要调用栈，O(logk)
class Solution {
public:
    ListNode *mergeTwo(ListNode *h1, ListNode *h2) {
        // special case: 有空，直接返回另一个
        if (h1 == nullptr || h2 == nullptr) {
            return (h1 == nullptr) ? h2 : h1;
        }
        // pseudo head
        ListNode *pseudohead = new ListNode();
        ListNode *p = pseudohead;
        while (h1 != nullptr && h2 != nullptr)
        {
            if (h1->val < h2->val) {
                p->next = h1;
                h1 = h1->next;
            }
            else
            {
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

    // 分治， 每次合并两条
    // 分治算法可以优雅写成递归形式
    ListNode *merge(vector<ListNode*> &lists, int l, int r) {
        if (l == r) {
            return lists[l];
        }
        else if (l > r)  // should not occur, only for input case check
        {
            return nullptr;
        }
        int mid = l + (r - l) / 2;
        return mergeTwo(merge(lists, l, mid), merge(lists, mid + 1, r));
    }

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.size() == 0) {
            return nullptr;
        }
        // else if (lists.size() == 1)
        // {
        //     return lists[0];
        // }
        return merge(lists, 0, lists.size() - 1);
    }
};


// 优先队列（最小堆）
// 最小堆维护每个list最小值，每次维护耗费O(logk)
// 总共维护O(kn)次
// 总时间 O(knlogk) 和分治一样
// 总空间 O(k)
class Solution2 {
public:
    struct Status
    {
        int val;
        ListNode *p;
        Status (int v, ListNode *pp) : val(v), p(pp) {}
        bool operator<(const Status &rhs) const {
            return val > rhs.val;  // reverse, 为了实现最小堆，priority_queue默认是最大堆
        }
    };
    
    priority_queue<Status> pq;

    ListNode *mergeKLists(vector<ListNode*> &lists) {
        if (lists.size() == 0) {
            return nullptr;
        }

        for (auto head: lists) {
            if (head != nullptr) {
                pq.push(Status(head->val, head));
            }
        }

        // 永远初始化指针
        ListNode *pseudohead = new ListNode(), *p = pseudohead;
        while (!pq.empty())
        {
            Status cur = pq.top();
            pq.pop();
            p->next = cur.p;
            p = p->next;
            if (cur.p->next != nullptr) {
                pq.push(Status(cur.p->next->val, cur.p->next));
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

int main() {
    // 构造3个有序链表
    ListNode* l1 = new ListNode(1, new ListNode(4, new ListNode(5)));
    ListNode* l2 = new ListNode(1, new ListNode(3, new ListNode(4)));
    ListNode* l3 = new ListNode(2, new ListNode(6));
    vector<ListNode*> lists = {l1, l2, l3};

    // Solution1测试
    Solution sol1;
    ListNode* merged1 = sol1.mergeKLists(lists);
    cout << "分治合并结果: ";
    printList(merged1);

    // 释放内存
    while (merged1) {
        ListNode* tmp = merged1;
        merged1 = merged1->next;
        delete tmp;
    }

    // 重新构造链表，避免上面释放后链表失效
    l1 = new ListNode(1, new ListNode(4, new ListNode(5)));
    l2 = new ListNode(1, new ListNode(3, new ListNode(4)));
    l3 = new ListNode(2, new ListNode(6));
    lists = {l1, l2, l3};

    // Solution2测试
    Solution2 sol2;
    ListNode* merged2 = sol2.mergeKLists(lists);
    cout << "优先队列合并结果: ";
    printList(merged2);

    // 释放内存
    while (merged2) {
        ListNode* tmp = merged2;
        merged2 = merged2->next;
        delete tmp;
    }

    return 0;
}