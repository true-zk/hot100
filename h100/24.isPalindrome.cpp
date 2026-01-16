/*
    234. 回文链表
    easy

    给你一个单链表的头节点 head ，请你判断该链表是否为回文链表。
    如果是，返回 true ；否则，返回 false 。

    最简单的方法是把每个元素存到vec

    空间O(1)：
    快慢指针！
        - 用快慢指针定位到中点；如果是奇数，把中间视作左边的
        - 翻转后半部分（用翻转链表方法）
        - 然后比较即可
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
Limitation: O(n)时间复杂度 + O(1)空间复杂度
*/
class Solution {
public:

    ListNode *reverseList(ListNode* head) {
        ListNode *prv = head, *cur = head->next;
        ListNode *tmp = nullptr;
        prv->next = nullptr;
        while (cur != nullptr)
        {
            tmp = cur->next;
            cur->next = prv;
            prv = cur;
            cur = tmp;
        }
        return prv;
    }

    // 计数找到右侧开始的节点
    ListNode *findRightStart1(ListNode* head) {
        int cnt = 0;
        ListNode *tmp = head;
        while (tmp != nullptr)
        {
            ++cnt;
            tmp = tmp->next;
        }
        int mid = cnt / 2 - 1; // before mid
        tmp = head;
        while (mid > 0)
        {
            tmp = tmp->next;
            --mid;
        }
        if (cnt % 2 == 0) {
            tmp = tmp->next;
        }
        else {
            tmp = tmp->next->next;
        }
        return tmp;
    }

    // **快慢指针**
    /*
        一个指针每次动一步，一个指针每次动两步
        第二指针到尾的时候，第一个指针到中间
    */
    ListNode *findRightStart2(ListNode* head) {
        ListNode *fast = head, *slow = head;
        while (fast != nullptr && fast->next != nullptr)
        {
            fast = fast->next->next;
            slow = slow->next;
        }
        if (fast == nullptr) {  // 偶数，slow恰好到右边第一个
            return slow;
        }
        else {  // 奇数，slow到恰好中间位置
            return slow->next;
        }
    }

    bool isPalindrome(ListNode* head) {
        if (head->next == nullptr) {  // special case
            return true;
        }

        // 1. find mid node
        ListNode *right_start = findRightStart2(head);

        // 2. reverse right part
        right_start = reverseList(right_start);
        
        ListNode *tmp = head;
        // 3. check if is Palindrome
        while (right_start != nullptr)
        {
            if (right_start->val != tmp->val) {
                return false;
            }
            right_start = right_start->next;
            tmp = tmp->next;
        }
        return true;
    }
};



int main() {
    int n;
    cout << "请输入链表长度: ";
    cin >> n;
    if (n == 0) {
        cout << "true" << endl;
        return 0;
    }
    cout << "请输入链表元素: ";
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        ListNode* node = new ListNode(x);
        if (!head) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }

    Solution sol;
    bool res = sol.isPalindrome(head);
    cout << (res ? "true" : "false") << endl;

    // 释放链表内存（面试可省略）
    while (head) {
        ListNode* tmp = head;
        head = head->next;
        delete tmp;
    }
    return 0;
}