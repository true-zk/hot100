"""
2
3 4
6 5 7
4 1 8 3
"""
from typing import List


class Solution:
    def minimumTotal(self, triangle: List[List[int]]) -> int:
        n = len(triangle)
        m = len(triangle[-1])

        dp = [[float('inf')] * n for _ in range(n)]
        dp[0][0] = triangle[0][0]

        # dp[i][j]: 到i,j的最短距离
        # dp[i][j] = min(dp[i - 1][j - 1], dp[i - 1][j]) + self

        for i in range(1, n):

            for j in range(i + 1):
                if j == 0:
                    dp[i][j] = dp[i - 1][j] + triangle[i][j]
                elif j == i:
                    dp[i][j] = dp[i - 1][j - 1] + triangle[i][j]
                else:
                    dp[i][j] = min(dp[i - 1][j - 1], dp[i - 1][j]) + triangle[i][j] 
        
        return min(dp[-1])