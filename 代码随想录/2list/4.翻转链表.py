"""
206.反转链表

史上最经典的题
"""
from typing import Optional


class ListNode:

    def __init__(self, v: int, next: Optional['ListNode'] = None):
        self.val = v
        self.next = next if next else None


class Solution:

    def reverseList(self, head: ListNode):

        prev = None
        cur = head

        while cur:
            # prev  cur -> next
            #               ^
            #              tmp

            tmp = cur.next
            cur.next = prev
            prev = cur
            cur = tmp

        # 现在 cur == None
        return prev

    def recur_reverseList(self, head: ListNode):
        # 用 递归 来做
        # 子任务：反向翻转链表，返回头节点
        # 然后把当前的位置翻转即可

        # 边界
        if head == None:    # 遍历到最后一个节点之后
            return None
        if head.next == None:   # 只有一个节点
            return head

        last = self.recur_reverseList(head.next)    # 翻转从 next 开始的链表，返回反转后头节点
        head.next.next = head
        head.next = None    # 当前节点变成最后一个节点，next 置空
        return last

s = Solution()
n1 = ListNode(1)
n2 = ListNode(2)
n3 = ListNode(3)
n4 = ListNode(4)
n5 = ListNode(5)

n1.next = n2
n2.next = n3
n3.next = n4
n4.next = n5

res = s.recur_reverseList(n1)
while res:
    print(res.val)
    res = res.next
