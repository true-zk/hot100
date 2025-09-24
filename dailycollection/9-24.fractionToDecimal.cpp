/*
    166.分数到小数
    medium

    给定两个整数，分别表示分数的分子 numerator 和分母 denominator，以 字符串形式返回小数 。
    如果小数部分为循环小数，则将循环的部分括在括号内。
    如果存在多个答案，只需返回 任意一个 。
    对于所有给定的输入，保证 答案字符串的长度小于 104 。
*/
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;


class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        string res;
        long nume = numerator;
        long denom = denominator;

        // special case: 可整除
        if (nume % denom == 0) {
            return to_string(nume / denom);
        }

        // 负号
        if (nume < 0 ^ denom < 0) {
            res += "-";
        }
        nume = abs(nume);
        denom = abs(denom);

        // 整数
        long integer_part = nume / denom;
        res += to_string(integer_part);
        res += ".";

        // 小数
        string decimal_res;
        unordered_map<long, int> dividend_map;
        int idx = 0;
        long dividend = nume % denom;
        while (dividend != 0 && !dividend_map.count(dividend)) {
            dividend_map[dividend] = idx;
            ++idx;
            dividend = dividend * 10;
            decimal_res += to_string(dividend / denom);
            dividend = dividend % denom;
        }

        if (dividend != 0) {  // infinite loop
            // [idx, endone]
            int iidx = dividend_map[dividend];
            decimal_res = decimal_res.substr(0, iidx) + "(" + decimal_res.substr(iidx) + ")";
        }

        res = res + decimal_res;
        return res;
    }
};


int main() {
    Solution sol;

    cout << 1 << ", " << 2 << ": " << sol.fractionToDecimal(1, 2) << endl;

    cout << 2 << ", " << 1 << ": " << sol.fractionToDecimal(2, 1) << endl;

    cout << 4 << ", " << 333 << ": " << sol.fractionToDecimal(4, 333) << endl;


    return 0;
}