"""
203. 移除链表元素

删除链表中等于给定值的所有结点
"""

from typing import Optional


class ListNode:

    def __init__(self, v: int, next: Optional['ListNode'] = None):
        self.val = v
        self.next = next if next else None


class Solution:

    def removeElements(self, head: ListNode, val: int) -> ListNode:
        dummy_head = ListNode(0)
        dummy_head.next = head

        cur = dummy_head
        while cur and cur.next:
            if cur.next.val == val:
                # 删除next
                tmp = cur.next
                cur.next = tmp.next
                del tmp
                continue    # 删完之后可能下个还是 == val，不能迭代到下一个node

            cur = cur.next

        return dummy_head.next



