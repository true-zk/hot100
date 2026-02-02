"""
151. 反转字符串中的单词
给定一个字符串，逐个翻转字符串中的每个单词。
如果两个单词间有多余的空格，将反转后单词间的空格减少到只含一个。

输入: "a good   example"
输出: "example good a"

要求原地操作 O(1)额外空间
"""

# 先完全反转
# 然后逐个单词反转

# 注意要去除空格
# 先用双指针去除空格 然和再翻转
class Solution:
    def reverseEach(self, s, left, right):
        while left < right:
            s[left], s[right] = s[right], s[left]
            left += 1
            right -= 1

    def reverseWords(self, s: str) -> str:
        start = 0
        n = len(s)

        s = list(s)

        # ab  cd e
        while s[start] == ' ':
            start += 1
        
        slow = fast = start
        extra_space = 0 
        while fast < n:
            if fast + 1 < n and s[fast] == ' ' and s[fast + 1] == ' ':
                fast += 1
                extra_space += 1
                continue
            else:
                s[slow] = s[fast]
                slow += 1
                fast += 1

        while extra_space > 0:
            n -= 1
            extra_space -= 1
        if s[n - 1] == ' ':
            n -= 1

        # reverse
        self.reverseEach(s, start, n - 1)

        # reverse each word
        left = right = start
        while right < n and left < n:
            if right == n - 1 or s[right + 1] == ' ':
                self.reverseEach(s, left, right)
                right += 2
                left = right
                continue
            right += 1
        
        return "".join(s[start:n])


sol = Solution()
print(sol.reverseWords("a good   example"))
print(sol.reverseWords("  hello world  "))