"""
寻找众数

1. 可以用分治算法
2. 也可以用Boyer-Moore 投票算法，众数一定会被保留
"""
from typing import List

class Solution:
    def majorityElement(self, nums: List[int]) -> int:
        candidate = None
        cnt = 0
        for num in nums:
            if cnt == 0:
                candidate = num
                cnt = 1
            
            elif num == candidate:
                cnt += 1
            else:
                cnt -= 1
        
        return candidate