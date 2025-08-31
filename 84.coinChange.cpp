/*
    medium
    dp
*/
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>

using namespace std;


class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        if (amount == 0) return 0;
        vector<int> dp(amount + 1, amount + 1);  // dp[i] := 到i的最少硬币数
        dp[0] = 0;

        for (int i = 1; i <= amount; ++i) {
            int tmp = amount + 1;
            // for each coin
            for (auto &coin: coins) {
                if (coin > i) continue;
                tmp = min(dp[i - coin] + 1, tmp); 
            }
            dp[i] = tmp;
        }
        return dp[amount] == amount + 1 ? -1 : dp[amount];
    }
};


// dp的递归形式，对amount记忆化搜索，小的amount会重复多次，记下来
class Solution2 {
public:
    int dp(vector<int> &cache, vector<int> &coins, int amount) {
        if (amount == 0) return 0;  // 恰好
        if (amount < 0) return -1;  // 无法达成
        if (cache[amount] != 0) return cache[amount];  // 如果已经cache过，用cache结果
        
        int res = numeric_limits<int>::max();
        for (int &coin: coins) {
            int tmp =  dp(cache, coins, amount - coin);
            if (tmp == -1) continue;
            res = min(res, tmp + 1);  // 加上当前硬币
        }
        // 考虑没有符合的情况，res == MAX，应该是-1
        cache[amount] = res == numeric_limits<int>::max() ? -1 : res;
        return cache[amount];
    }

    int coinChange(vector<int> &coins, int amount) {
        if (amount == 0) return 0;
        vector<int> cache(amount + 1);
        return dp(cache, coins, amount);
    }
};


int main() {
    int amout;
    vector<int> coins;
    Solution sol;

    coins = {1, 2, 5};
    amout = 11;
    cout << sol.coinChange(coins, amout) << endl;

    coins = {2};
    amout = 3;
    cout << sol.coinChange(coins, amout) << endl;

    coins = {1};
    amout = 0;
    cout << sol.coinChange(coins, amout) << endl;

    return 0;
}