"""
求区间内的累加：前缀和

注意前缀和 
prefix_sum[i]: 表示从 [0, i] 的和

那么区间 [i, j] 的和:
interval_sum = prefix_sum[j] - prefix_sum[i - 1]

要特殊处理 i - 1 == -1 的情况
"""

print(abs(-1))