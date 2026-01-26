"""
子序列不需要连续，所以本质n^2 dp
但是可以用贪心 + 二分变成一个nlogn
"""
from typing import List


# dp
class Solution:
    def lengthOfLIS(self, nums: List[int]) -> int:
        n = len(nums)
        if not nums:
            return 0
        
        # dp[i]：到 i 的最长子序列
        # dp[i] = j:从 0 到 i - 1的最长子序列 + 1 if nums[j] < nums[i]
        dp = [1] * n
        for i in range(1, n):
            for j in range(0, i):
                if nums[j] > nums[i]:
                    dp[i] = max(dp[i], dp[j] + 1)
        
        # 最后不一定是最长的
        return max(dp)


# 贪心 + 2分
class Solution2:
    """
    思想：我们希望子序列长得尽可能 慢
        即新加入的尾巴应该尽可能小，如果比原来的更小，而且长度一致，那我们就换尾巴
    
    例如 3, 5, 4,
    当我们遍历到 [3, 5]的时候，长度2的子序列，尾巴是5
    继续遍历到4，发现长度为2的子序列尾巴可以更新成4，我们就可以贪心的更新：
    因为继续往后遍历的时候，4一定比5有“优势”

    d[k] 表示 长度为k的子序列的 结尾的数值 
    cur_len 表示 当前的最长长度

    遍历nums，
    如果nums[i] > d[cur_len]， 可以直接加入尾巴，更新cur_len +=1，然后 d[cur_len] = nums[i]

    否则nums[i] <= d[cur_len]，我们要更新 d 数组：
    由于 d 数组是递增的，二分找到比nums[i]小的位置，更新

    """

    def lengthOfLIS(self, nums: List[int]) -> int:
        n = len(nums)
        d = []
        cur_len = 0
        for i in range(n):
            # 如果比最后一个大，直接更新
            if cur_len == 0 or nums[i] > d[cur_len - 1]:
                d.append(nums[i])
                cur_len += 1
            
            # 二分查找 比 nums[i] 大的位置
            # 2，3，5，7当前nums[i]值为 4，找到第一个比 4 大的，是5
            else:
                l, r = 0, cur_len - 1
                loc = r
                while l <= r:
                    mid = (l + r) // 2
                    if d[mid] >= nums[i]:
                        loc = mid
                        r = mid - 1
                    else:
                        l = mid + 1
                d[loc] = nums[i]
        
        return cur_len

a = [10,9,2,5,3,7,101,18]
sol = Solution2()
print(sol.lengthOfLIS(a))