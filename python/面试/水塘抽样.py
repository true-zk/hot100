"""
水塘抽样用于：

从一个 未知大小 的数据流中，
随机采样 k 个样本

思路：
1. 初始化一个 k size 的样本池 pool
2. 前 k 个元素直接放入样本池
3. 对于第 i 个元素 (i 从 k+1 开始)：
    - 从 [0, i] 中随机采样 j 
    - if j < k: pool[j] = element[i]  # 用当前元素，替换样本池中的第 j 个元素
    - else: continue
4. 重复步骤 3，直到数据流结束
5. 返回样本池 pool
"""


class ReservoirSampler:
    def __init__(self, k):
        self.k = k
        self.pool = []
    
    def sample(self, stream):
        import random

        for i, element in enumerate(stream):
            if i < self.k:
                self.pool.append(element)
            else:
                j = random.randint(0, i)
                if j < self.k:
                    self.pool[j] = element
                else:
                    continue
        
        return self.pool


# 示例用法
stream = range(1, 1001)  # 模拟一个数据流
k = 10
sampler = ReservoirSampler(k)
samples = sampler.sample(stream)
print("随机采样的样本:", samples)


