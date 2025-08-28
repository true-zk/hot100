/*
    medium
    Limitation: O(1)的get和put
*/
#include <iostream>
#include <unordered_map>

using namespace std;


// 双向链表存值，头部是最近使用，尾部是LRUeviction的
struct DLinkedNode
{
    int key;
    int val;
    DLinkedNode *prev;
    DLinkedNode *next;
    DLinkedNode() : key(0), val(0), prev(nullptr), next(nullptr) {}
    DLinkedNode(int k, int v) : key(k), val(v), prev(nullptr), next(nullptr) {}
};


class LRUCache {
public:
    LRUCache(int capacity) : capacity(capacity), size(0) {
        // 创建伪头和尾来减少特殊判断！
        head = new DLinkedNode();
        tail = new DLinkedNode();
        head->next = tail;
        tail->prev = head;
    }
    
    int get(int key) {
        // 找不到，-1
        if (!cache.count(key)) {
            return -1;
        }
        DLinkedNode *find = cache[key];
        // 更新在链表的位置after head
        moveToAfterHead(find);
        return find->val;
    }
    
    void put(int key, int value) {
        // 找得到，更新值
        if (cache.count(key)) {
            DLinkedNode *find = cache[key];
            moveToAfterHead(find);
            find->val = value;
        }
        // 找不到，加入
        else
        {
            DLinkedNode *newnode = new DLinkedNode(key, value);
            cache[key] = newnode;
            addAfterHead(newnode);
            ++size;
            // 判断是否需要eviction
            if (size > capacity) {
                DLinkedNode *LRU_node = tail->prev;
                removeNode(LRU_node);
                cache.erase(LRU_node->key);
                delete LRU_node;
                --size;
            }
        }
        
    }

private:
    // capacity and size
    // size <= capacity
    int capacity;
    int size;
    // unordered_map来实现O(1)的get: key -> *node (位置)
    unordered_map<int, DLinkedNode*> cache;
    // pseudo head and tail, to eliminate special cases
    DLinkedNode *head;
    DLinkedNode *tail;

    void removeNode(DLinkedNode *p) {
        // 摘除p
        p->next->prev = p->prev;
        p->prev->next = p->next;
    }

    void addAfterHead(DLinkedNode *p) {
        // 置于head后
        p->next = head->next;
        p->prev = head;
        head->next->prev = p;
        head->next = p;
    }

    void moveToAfterHead(DLinkedNode *p) {
        removeNode(p);
        addAfterHead(p);
    }
};


int main() {
    // 创建容量为2的LRU缓存
    LRUCache cache(2);

    // put(1, 1)
    cache.put(1, 1);
    // put(2, 2)
    cache.put(2, 2);
    // get(1) -> 1
    cout << cache.get(1) << endl; // 输出: 1

    // put(3, 3)，此时1被访问过，2是最久未用，应该被淘汰
    cache.put(3, 3);
    // get(2) -> -1 (未找到)
    cout << cache.get(2) << endl; // 输出: -1

    // put(4, 4)，此时1是最久未用，应该被淘汰
    cache.put(4, 4);
    // get(1) -> -1 (未找到)
    cout << cache.get(1) << endl; // 输出: -1
    // get(3) -> 3
    cout << cache.get(3) << endl; // 输出: 3
    // get(4) -> 4
    cout << cache.get(4) << endl; // 输出: 4

    return 0;
}