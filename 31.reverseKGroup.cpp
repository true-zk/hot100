
#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x): val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
    int val;
    ListNode *next;
};

void printList(ListNode* head) {
    while (head) {
        cout << head->val;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << endl;
}


/*
    Limitation: O(1)的内存
*/
class Solution {
public:

    // reserse between head and tail, keep head and tail unchanged.
    // return last node before tail after reverse.
    ListNode* reverseK(ListNode *const head, ListNode *const tail) {
        ListNode *prev = head->next, *cur = prev->next;
        ListNode *tmp;
        prev->next = tail;
        while (cur != tail)
        {
            tmp = cur->next;    // node 3
            cur->next = prev;   // node 2 -> node 1
            prev = cur;
            cur = tmp;
        }
        tmp = head->next;  // last node before tail
        head->next = prev;
        return tmp;
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        if (k == 1 || head == nullptr || head->next == nullptr)
        {
            return head;
        }

        ListNode *pseudohead = new ListNode(0);
        pseudohead->next = head;
        ListNode *leftp = pseudohead, *rightp = pseudohead;
        ListNode *tmp;
        int tmp_cnt = k;
        while (tmp_cnt > 0)
        {
            rightp = rightp->next;
            --tmp_cnt;
        }
        // printList(pseudohead);
        rightp = reverseK(leftp, rightp->next);
        // printList(pseudohead);
        tmp_cnt = k;
        while (rightp != nullptr) {
            if (tmp_cnt == 0) {
                rightp = reverseK(leftp, rightp->next);
                tmp_cnt = k;
                continue;
            }

            --tmp_cnt;
            leftp = leftp->next;
            rightp = rightp->next;
        }

        leftp = pseudohead->next;
        delete pseudohead;
        return leftp;
    }
};

// ====== 以下为面试手撕代码测试部分 ======
ListNode* createList(const vector<int>& vals) {
    ListNode dummy(0);
    ListNode* cur = &dummy;
    for (int v : vals) {
        cur->next = new ListNode(v);
        cur = cur->next;
    }
    return dummy.next;
}

void freeList(ListNode* head) {
    while (head) {
        ListNode* tmp = head;
        head = head->next;
        delete tmp;
    }
}

int main() {
    vector<int> vals = {1, 2, 3, 4, 5};
    int k = 2;
    ListNode* head = createList(vals);
    Solution sol;
    ListNode* newHead = sol.reverseKGroup(head, k);
    cout << "reverseKGroup result: ";
    printList(newHead);
    freeList(newHead);
    return 0;
}