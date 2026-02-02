"""
454. 四数相加

给定四个包含整数的数组列表 A , B , C , D ,计算有多少个元组 (i, j, k, l) ，
使得 A[i] + B[j] + C[k] + D[l] = 0。

经典hash题：
先算 A + B 的哈希
然后遍历 C + D
"""
from typing import List
import collections

class Solution:
    def fourSumCount(self, nums1: List[int], nums2: List[int], nums3: List[int], nums4: List[int]) -> int:
        A_B_sum_mapping = collections.defaultdict(int)

        for a in nums1:
            for b in nums2:
                A_B_sum_mapping[a + b] += 1
        
        res = 0
        for c in nums3:
            for d in nums4:
                    res += A_B_sum_mapping[- (c + d)]
        
        return res


nums1 = [-1, -1]
nums2 = [-1, 1]
nums3 = [-1, 1]
nums4 = [1, -1]

print(Solution().fourSumCount(nums1, nums2, nums3, nums4))  # 6