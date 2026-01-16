/*
    中等，多解法
*/

#include <iostream>
#include <vector>
#include <unordered_map>

using std::vector;
using std::unordered_map;
using std::cout; using std::endl;


class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};


void printList(Node* head) {
    Node* cur = head;
    int idx = 0;
    while (cur) {
        cout << "Node " << idx << ": val=" << cur->val;
        if (cur->random)
            cout << ", random->val=" << cur->random->val;
        else
            cout << ", random->val=nullptr";
        cout << endl;
        cur = cur->next;
        ++idx;
    }
}


// 数组，比较差的解法，复杂度是N^2
class Solution {
public:
    // return the index of target Node in the List
    // if target == null, return -1
    int findNodeIndex(Node *head, Node *target) {
        if (target == nullptr) {
            return -1;
        }
        int res = 0;
        while (head != nullptr)
        {
            if (head == target) {
                return res;
            }
            ++res;
            head = head->next;
        }
        return res;  // this should never occur, only for return type
    }

    Node* copyRandomList(Node* head) {
        if (head == nullptr)
        {
            return head;
        }
        
        Node *cur = head;
        Node *newhead = new Node(cur->val);
        vector<int> random_index;
        Node *cur2 = newhead;
        // cur2 = new Node(cur->val);
        random_index.push_back(findNodeIndex(head, cur->random));
        cur = cur->next;
        
        while (cur != nullptr)
        {
            cur2->next = new Node(cur->val);
            random_index.push_back(findNodeIndex(head, cur->random));
            cur = cur->next;
            cur2 = cur2->next;            
        }

        cur2 = newhead;
        for (int i = 0; i < random_index.size(); ++i) {
            if (random_index[i] == -1) {
                cur2->random = nullptr;
            }
            else
            {
                cur = newhead;
                while (random_index[i] > 0)
                {
                    --random_index[i];
                    cur = cur->next;
                }
                cur2->random =cur;
            }
            cur2 = cur2->next;
            
        }
        
        return newhead;
    }
};


// hashmap + 回溯
// 当前head可能复制过，也可能没有。
// 有的话就直接返回；没有的话就递归调用来获取
// 用全局的hashmap记录randomenode
// O(n) O(n)
class Solution2 {
public:
    unordered_map<Node*, Node*> cachedNode;
    Node *copyRandomList(Node *head) {
        if (head == nullptr) {
            return head;
        }

        if (cachedNode.count(head) == 0) {
            Node *newnode = new Node(head->val);
            cachedNode[head] = newnode;  // 已经创建了就可以加入到缓存
            newnode->next = copyRandomList(head->next);  // recursive call
            newnode->random = copyRandomList(head->random);  // revursive call
        }

        return cachedNode[head];
    }
};


// Tricky的方法
/*
    在每个原节点后面加个新拷贝节点，这样可以做到O(1)额外空间
    random就是原节点的random的后一个节点
    A -> A' -> B -> B' -> ...
*/
class Solution3 {
public:
    Node *copyRandomList(Node *head) {
        if (head == nullptr) {
            return head;
        }

        Node *p = head;
        while (p != nullptr)
        {
            Node *newnode = new Node(p->val);
            newnode->next = p->next;
            p->next = newnode;
            p = p->next->next;
        }
        
        // assign random
        p = head;
        while (p != nullptr)
        {
            if (p->random == nullptr) {
                p->next->random = nullptr;
            }
            else
            {
                p->next->random = p->random->next;
            }
            p = p->next->next;
        }
        
        // separate
        p = head;
        Node *newhead = p->next;
        Node *p2 = newhead;
        while (p != nullptr)
        {
            p->next = p->next->next;
            p2->next = (p2->next != nullptr) ? p2->next->next : nullptr;
            p = p->next;
            p2 = p2->next;
        }
        
        return newhead;
    }
};


int main() {
    // 构造测试链表: 1->2->3, random分别指向3,1,nullptr
    Node* n1 = new Node(1);
    Node* n2 = new Node(2);
    Node* n3 = new Node(3);
    n1->next = n2;
    n2->next = n3;
    n1->random = n3;
    n2->random = n1;
    n3->random = nullptr;

    cout << "原链表:" << endl;
    printList(n1);

    Solution3 sol;
    Node* copied = sol.copyRandomList(n1);

    cout << "\n复制后的链表:" << endl;
    printList(copied);

    // 释放原链表内存
    delete n1;
    delete n2;
    delete n3;

    // 释放复制链表内存
    Node* tmp;
    while (copied) {
        tmp = copied->next;
        delete copied;
        copied = tmp;
    }

    return 0;
}