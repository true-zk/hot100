struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};


struct DListNode
{
    int val;
    DListNode *prev;
    DListNode *next;
    DListNode(int x): val(x), prev(nullptr), next(nullptr) {}
};
