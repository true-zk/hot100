"""
去除一些栅栏，得到的最大面积
"""
from typing import List


class Solution:

    def get_edges(self, fences: List[int], border: int) -> set:
        points = sorted([1] + fences + [border])
        edges = set()
        l = len(points)
        for i in range(l):
            for j in range(i + 1, l):
                edges.add(points[j] - points[i])
        return edges

    def maximizeSquareArea(self, m: int, n: int, hFences: List[int], vFences: List[int]) -> int:
        MOD = 10 ** 9 + 7
        h_edges = self.get_edges(hFences, m)
        v_edges = self.get_edges(vFences, n)

        max_edges = max(h_edges & v_edges, default=0)
        if max_edges == 0:
            return -1
        else:
            return max_edges ** 2 % MOD