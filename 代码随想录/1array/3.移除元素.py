"""
涉及到原地操作数组，移除元素

一个常见思路是双指针，
- 慢指针维护当前合法的区间
- 快指针指向下个要处理的位置

例题：
283. 移动零
"""

def move_zeroes(nums):
    n = len(nums)
    slow_ptr = 0
    fast_ptr = 0

    while fast_ptr < n:
        # 如果遇到的不是0，放到慢指针的地方
        if nums[fast_ptr] != 0:
            nums[slow_ptr] = nums[fast_ptr]
            slow_ptr += 1
        fast_ptr += 1
    
    # 为了保证把0移动到末尾
    for i in range(slow_ptr, n):
        nums[i] = 0
    
    return nums

a = [0,1,0,3,12]
print(move_zeroes(a))  # 输出 [1,3,12]