/*
    3516 找最近的人
    easiest
*/
#include <iostream>
#include <algorithm>

using namespace std;


class Solution {
public:
    int findClosest(int x, int y, int z) {
        x = abs(x - z);
        y = abs(y - z);
        return (x == y) ? 0 : (x > y ? 2 : 1);
    }
};


int main() {
    Solution sol;
    cout << sol.findClosest(2, 7, 4) << endl; // 1
    cout << sol.findClosest(2, 5, 6) << endl; // 2
    cout << sol.findClosest(1, 5, 3) << endl; // 0
    return 0;
}