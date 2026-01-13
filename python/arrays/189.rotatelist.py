"""
189 旋转数组
1. 循环交换
2. 还可以用反转的方法实现，先全反转，然后反转[0, k - 1], [k, n - 1]
"""
from typing import List

class Solution:
    def rotate(self, nums: List[int], k: int) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        n = len(nums)

        i = 0
        swap_cnt = 0
        start = 0
        while swap_cnt < n:
            current = start
            prev = nums[start]

            while True:
                next = (current + k) % n
                tmp = nums[next]
                nums[next] = prev
                prev = tmp
                current = next
                swap_cnt += 1

                if start == current:
                    break
            
            start += 1

            
