"""
347. 前k个高频元素

mapping记录元素和频率
小顶堆维护，如果超过k则弹出，到
"""
from typing import List
import collections
import heapq

class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        freq_mapping = collections.defaultdict(int)
        for i in range(len(nums)):
            freq_mapping[nums[i]] += 1
        
        min_heap = []
        for key, value in freq_mapping.items():
            heapq.heappush(min_heap, (value, key))

            if len(min_heap) > k:
                heapq.heappop(min_heap)
        
        res = [0] * k
        for i in range(len(min_heap) - 1, -1, -1):
            res[i] = heapq.heappop(min_heap)[1]
        
        return res