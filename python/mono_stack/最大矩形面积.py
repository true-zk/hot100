"""
最大矩形面积

给一个heights的数组,求最大矩形面积

遍历每个高度,对于任何一个高度,其最大面积就是能向左和右扩展的最大宽度
高度枚举了,宽度贪心最大的情况,所以不会漏掉

最大宽度用两边的单调栈
"""

class Solution:

    def largestRectangleArea(self, heights: list[int]) -> int:
        n = len(heights)

        # 左侧的最大宽度的下标
        left = [0] * n
        mono_stack = []
        for i in range(n):
            # 如果单调栈不空，而且栈顶的值 >= heights[i]
            # 说明找到了左边界，pop栈
            while mono_stack and heights[mono_stack[-1]] >= heights[i]:
                mono_stack.pop()
            # 如果单调栈不为空，则 栈顶 < heights[i]，即左边界
            # 为空，说明左边所有的都 >= heights[i] ，左边界可以看作是 -1
            left[i] = mono_stack[-1] if mono_stack else -1
            # 入栈
            mono_stack.append(i)
        
        # 右侧最大宽度的下标
        right = [0] * n
        mono_stack.clear()
        for i in range(n - 1, -1, -1):
            while mono_stack and heights[mono_stack[-1]] >= heights[i]:
                mono_stack.pop()
            right[i] = mono_stack[-1] if mono_stack else n  # 最右边的边界用 n -1 + 1
            mono_stack.append(i)

        # 对每个柱子高度遍历，计算最大面积
        res = 0
        for i in range(n):
            h = heights[i]
            w = right[i] - left[i] - 1
            res = max(res, h * w)
        
        return res