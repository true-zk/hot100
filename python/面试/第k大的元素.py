"""
一道典型的快排思路

给一个数组, 找到第k大的元素

最简单是排序, 可以用堆排序, 但是最差是nlogn

o(n)是用快排的思路:
第一次 n ,第二次 n/2
n + n/2 + n/4 ... 平均是O(n)
"""

class Solution:

    def partition(self, nums, left, right):
        """
        在子数组[left, right]中随机选择 pivot,
        根据 pivot 划分数组: 比 <= pivot 在左边, >= pivot 在右边
        返回 pivot 在重新排列后的nums中的下标
        特殊情况: 如果子数组所有元素都等于 pivot, 返回中心下标, 避免退化
        """
        # 1. select pivot
        pivot = nums[left]

        # 2. 双指针遍历
        # [pivot | <= pivot | 尚未遍历 | >= pivot]
        #  ^                  ^     ^           ^
        # left                i     j         right

        i = left + 1
        j = right
        while True:
            while i <= j and nums[i] < pivot:
                i += 1
            # 此时 nums[i] >= pivot

            while i <= j and nums[j] > pivot:
                j -= 1
            # 此时 nums[j] <= pivot

            if i >= j:
                break

            # 交换 nums[i] nums[j]
            nums[i], nums[j] = nums[j], nums[i]
            # 步进
            i += 1
            j -= 1
        
        # 循环结束后
        # [pivot | <= pivot | >= pivot]
        #  ^              ^   ^      ^
        # left            j   i     right

        # 为了保证 pivot左边的都 <= pivot
        # 把nums[j] 和 pivot交换
        nums[left], nums[j] = nums[j], nums[left]

        # 交换后
        # [ <= pivot | pivot | >= pivot]
        #                ^
        #                j

        # 返回pivot下标
        return j

    def findKthLargest(self, nums: list[int], k: int) -> int:
        n = len(nums)
        target_index = n - k
        left = 0
        right = n - 1
        while True:
            i = self.partition(nums, left, right)
            if i == target_index:
                return nums[i]
            elif i > target_index:
                right = i - 1
            else:
                left = i + 1