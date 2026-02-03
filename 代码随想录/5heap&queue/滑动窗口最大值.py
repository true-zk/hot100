"""
239. 滑动窗口最大值

经典的单调队列问题
"""

# 单调队列维护当前 窗口内 的 最大值
# 单调减
# 例如 1 2 3 2 1
# 把 1 入队 遇到 2 的时候，1显然就没用了，可以踢掉
# 但是 3 2 的时候，不能踢掉 3

from typing import List
from collections import deque


class MyQueue:
    def __init__(self):
        self.q = deque()

    # 只有当等于队列头的时候才弹出
    def pop(self, value):
        if self.q and value == self.q[0]:
            self.q.popleft()
    
    # 保证队列单调减的push
    def push(self, value):
        while self.q and value > self.q[-1]:
            self.q.pop()
        self.q.append(value)
    
    # 拿出队列头，最大的值
    def front(self):
        if self.q:
            return self.q[0]
        else:
            return None

class Solution:
    def maxSlidingWindow(self, nums: List[int], k :int) -> List[int]:
        q = MyQueue()
        res = []

        # 前k个，维护单调队列
        for i in range(k):
            q.push(nums[i])
        res.append(q.front())

        # 滑窗，维护单调队列
        for i in range(k, len(nums)):
            q.pop(nums[i - k])
            q.push(nums[i])
            res.append(q.front())

        return res
    


