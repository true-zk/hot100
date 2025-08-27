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


/*
    Limitation: 尝试用一次扫描完成
    间隔n距离的双指针！p1和p2间隔n的话，p2到头了p1就恰好到-n
*/
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *fakehead = new ListNode;
        fakehead->next = head;  // 添加pseudo head来避免head的额外判断

        ListNode *p1 = fakehead, *p2 = fakehead;
        while (n > 0)
        {
            p2 = p2->next;
            --n;
        }

        while (p2->next != nullptr)
        {
            p1 = p1->next;
            p2 = p2->next;
        }

        // p1 at prev of to-be-deleted node
        p2 = p1->next;
        p1->next = p1->next->next;
        delete p2;  // free

        p1 = fakehead->next;  // 这里不是直接返回原来的head，因为注意到当只有一个节点，删一个节点的时候，
        // head已经被删了，真正的要返回的是fakehead->next，也就是nullptr
        // 其他要删head的情况也是如此，所以引入pseudo head有这样的好处

        // free pseudo head
        delete fakehead;

        return p1;
    }
};


//////////// 测试辅助代码 /////////////////////
ListNode* createList(const vector<int>& vals) {
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
        cout << head->val;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << endl;
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
    vector<int> vals = {1, 2, 3, 4, 5};
    int n = 2; // 删除倒数第2个节点
    ListNode* head = createList(vals);

    Solution sol;
    ListNode* newHead = sol.removeNthFromEnd(head, n);

    cout << "Result: ";
    printList(newHead);

    freeList(newHead);
    return 0;
}