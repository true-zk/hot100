"""
3651. 带传送的最小路径成本

给一个grid，和 k 
最多可以传送 k 次

- 要么向 右 / 下 走，成本 为目标单元格的值 grid[i + 1][j] or grid[i][j + 1]

- 要么传送到任意 grid[x][y] <= grid[i][j] 的 x, y 单元格，移动成本为 0 
"""

# 如果没有传送就是普通的最短路径成本 2维dp
# 加上传送，需要 3维dp

# dp[t][i][j]: 传送 t 次，到 i, j 的最小成本
# 更新：
# 
# t = 0，就是普通的 2维dp
# t > 0, 先通过 t - 1 传送到 t，然后 2维 dp

# 关键在于怎么从 dp[t - 1] 得到 dp[t]
# 需要在第 t 层，遍历 t - 1 的 dp 数组

# 为了找到最小值，需要维护一个 suffix_min 数组
# suffix_min[v] : 表示第 t - 1 层中， 满足 grid[x][y] >= v 的最小 dp 的值
# 因为这样的 x, y 才能传送到 t 层的 grid[i][j] 上

class Solution:
    def minCost(self, grid: list[list[int]], k: int) -> int:
        # n 行 m 列
        n = len(grid)
        m = len(grid[0])
        # 最大值
        max_v = 0
        for i in range(n):
            for j in range(m):
                max_v = max(max_v, grid[i][j])

        dp = [[float('inf')] * m for _ in range(n)]

        # 初始化，不传送
        for i in range(n):
            for j in range(m):
                if i == 0 and j == 0:   # 初始化，成本为 0
                    dp[i][j] = 0
                elif i == 0:    # 第一行，只能从左边来
                    dp[i][j] = dp[i][j - 1] + grid[i][j]
                elif j == 0:    # 第一列，只能从上面来
                    dp[i][j] = dp[i - 1][j] + grid[i][j]
                else:
                    dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j]
        
        # 传送
        res = dp[n - 1][m - 1]
        for t in range(1, k + 1):
            # 找到可以传送到 i, j 的，第 t - 1 层的最小成本
            suffix_min = [float("inf")] * (max_v + 1)

            # 遍历 dp （第 t - 1 层），更新 suffix_min
            for i in range(n):
                for j in range(m):
                    v = grid[i][j]
                    suffix_min[v] = min(suffix_min[v], dp[i][j])
            # 从大到小遍历 suffix_min 更新 suffix_min
            # 使得 suffix_min[v] 表示 grid[x][y] >= v 的最小值
            for v in range(max_v, 0, -1):
                suffix_min[v - 1] = min(suffix_min[v - 1], suffix_min[v])
            
            # 传送
            for i in range(n):
                for j in range(m):
                    v = grid[i][j]
                    # 要么传送，要么不传送本身就最小
                    dp[i][j] = min(dp[i][j], suffix_min[v])
            
            # 普通的 2维 dp 更新
            for i in range(n):
                for j in range(m):
                    if i == 0 and j == 0:
                        continue
                    elif i == 0:
                        dp[i][j] = min(dp[i][j], dp[i][j - 1] + grid[i][j])
                    elif j == 0:
                        dp[i][j] = min(dp[i][j], dp[i - 1][j] + grid[i][j])
                    else:
                        dp[i][j] = min(dp[i][j], min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j])

            res = min(res, dp[n - 1][m - 1])
        
        return res
                    

