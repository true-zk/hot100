/*
    medium
*/
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;


// 尽可能多划分 + 一样的字母在一个片段
class Solution {
public:
    vector<int> partitionLabels(string s) {
        if (s.size() == 1) return vector<int> {1};

        int n = s.size();
        vector<int> res;
        unordered_map<char, int> lastidx;
        // 找到每个字母的最后出现位置 ababcc -> a:2, b:3, c:5
        for (int i = 0; i < n; ++i) {
            lastidx[s[i]] = i;
        }
        // 找到每个区间的最后位置，可以切一刀
        // ababcc, 什么时候划分：当 maxidx = i 的时候切
        int maxidx = -1;
        int lastres = -1;  // 上一个划分的下标
        for (int i = 0; i < n; ++i) {
            maxidx = max(maxidx, lastidx[s[i]]);
            if (maxidx == i) {
                res.push_back(i - lastres);
                lastres = i;
            }
        }
        return res;
    }
};


int main() {
    string s;
    Solution sol;

    s = "ababcc";
    for (auto &el: sol.partitionLabels(s)) {
        cout << el << ",";
    }
    cout<<endl;

    s = "ababcbacadefegdehijhklij";
    for (auto &el: sol.partitionLabels(s)) {
        cout << el << ",";
    }
    cout<<endl;

    s = "eccbbbbdec";
    for (auto &el: sol.partitionLabels(s)) {
        cout << el << ",";
    }
    cout<<endl;
    return 0;
}