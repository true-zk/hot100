/*
    medium
*/
#include <string>
#include <stack>
#include <vector>
#include <limits>
#include <iostream>
#include <algorithm>

using namespace std;


/*
    stk
    1. cur <= top,  push(cur)
    2. cur > top, update res[top], pop, until cur <= top
*/
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> res(n, 0);
        stack<pair<int, int>> stk;  // (val, idx)
        stk.push(pair<int, int>{numeric_limits<int>::max(), -1});
        int curtemp;
        for (int i = 0; i < n; ++i) {
            curtemp = temperatures[i];
            if (curtemp <= stk.top().first) {
                stk.push(pair<int, int> {curtemp, i});
            }
            else {
                while (curtemp > stk.top().first)
                {
                    res[stk.top().second] = i - stk.top().second;
                    stk.pop();
                }
                stk.push(pair<int, int> {curtemp, i});
            }
        }
        return res;
    }
};


void printres(vector<int> &res) {
    cout << "[";
    for (int i = 0; i < res.size(); ++i) {
        cout << res[i] << (i == res.size() - 1 ? "" : ", "); 
    }
    cout << "]" << endl;
}


int main() {
    Solution sol;
    vector<int> temperatures {73,74,75,71,69,72,76,73};
    vector<int> res = sol.dailyTemperatures(temperatures);
    printres(res);

    temperatures = {30,40,50,60};
    res = sol.dailyTemperatures(temperatures);
    printres(res);
    return 0;
}