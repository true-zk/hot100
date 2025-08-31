/*
    easy
*/
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


// 贪心，只找在i后面的，最大的即可，
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int minv = prices[0];
        int res = 0;
        for (int i = 1; i < prices.size(); ++i) {
            if (prices[i] < minv) {
                minv = prices[i];
                continue;
            }

            res = max(res, prices[i] - minv);

        }
        return res;
    }
};


int main() {
    vector<int> prices;
    Solution sol;

    prices = {7,1,5,3,6,4};
    cout << sol.maxProfit(prices) << endl;

    prices = {7,6,4,3,1};
    cout << sol.maxProfit(prices) << endl;

    return 0;
}