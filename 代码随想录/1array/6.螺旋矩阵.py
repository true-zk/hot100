"""
59.螺旋矩阵II
给 n ，生成从 1 - n^2 的螺旋矩阵

最经典的模拟题，主要是边界怎么处理
"""

# 首先，每个边都是左闭右开 
# [0, 0]         -> [0, n - 2], 
# [0, n - 1]     -> [n - 2, n - 1]
# [n - 1, n - 1] -> [n - 1, 1]
# [n - 1, 0]     -> [1, 0]

# 然后 总共循环多少层？
# k = n // 2，例如 n = 3 实际上只需要循环 1 层

# 最后 奇数怎么处理？
# 最后中间元素单独填充

def generateMatrix(n):
    matrix = [ [0] * n for _ in range(n) ]
    startx, starty = 0, 0

    loop = n // 2
    cur_value = 1

    for k in range(loop):
        # 上层，从左到右
        # 左闭右开：starty -> n - k - 2
        for j in range(starty, n - k - 1):
            matrix[startx][j] = cur_value
            cur_value += 1
        # 右层，从上到下
        for i in range(startx, n - k - 1):
            matrix[i][n - k - 1] = cur_value
            cur_value += 1
        # 下层，从右往左
        for j in range(n - k - 1, starty, -1):
            matrix[n - k - 1][j] = cur_value
            cur_value += 1
        # 左层，从下往上
        for i in range(n - k - 1, startx, -1):
            matrix[i][starty] = cur_value
            cur_value += 1
        
        # 更新起始点
        startx += 1
        starty += 1
        
    # 处理奇数
    if n % 2 == 1:
        matrix[n // 2][n // 2] = cur_value
    
    return matrix

print(generateMatrix(3))
print(generateMatrix(4))