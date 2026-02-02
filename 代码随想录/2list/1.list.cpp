/*
    设计一个可以在任意位置增删查元素的列表
*/

class MyLinkedList {
    struct Node {
        int val;
        Node *next;
        Node(int x): val(x), next(nullptr) {}
        Node(int x, Node *next_): val(x), next(next_) {}
    };
    Node *head;
    Node *tail;
    int n;
public:
    MyLinkedList() {
        // create pseudohead
        head = new Node(0);
        tail = head;
        n = 0;
    }

    int get(int index) {
        if (index < 0 || index >= n) {
            return -1;
        }
        Node *tmp = head;
        while (index >= 0) {
            tmp = tmp -> next;
            --index;
        }
        return tmp->val;
    }

    void addAtHead(int val) {
        Node *tmp = new Node(val, head->next);
        head->next = tmp;
        if (n == 0) {
            tail = tmp;
        }
        ++n;
    }

    void addAtTail(int val) {
        Node *tmp = new Node(val);
        tail->next = tmp;
        tail = tmp;
        ++n;
    }

    void addAtIndex(int index, int val) {
        if (index > n || index < 0) return;
        else if (index == n) {
            addAtTail(val);
        }
        else {
            Node *tmp = head;
            while (index > 0) {
                tmp = tmp->next;
                --index;
            }
            Node *newnode = new Node(val, tmp->next);
            tmp->next = newnode;
            ++n;
        }
    }

    void deleteAtIndex(int index) {
        if (index >= 0 && index < n) {
            Node *tmp = head;
            while (index > 0) {
                tmp = tmp->next;
                --index;
            }
            if (tmp->next == tail) {
                tail = tmp;
            }
            Node *del_node = tmp->next;
            tmp->next = del_node->next;
            delete del_node;
            --n;
        }
    }
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */