/*
    easy
    stk
*/
#include <string>
#include <stack>
#include <iostream>
#include <unordered_map>

using namespace std;


class Solution {
public:
    unordered_map<char, char> validmap {
        {'{', '}'},
        {'(', ')'},
        {'[', ']'},
    };

    bool isValid(string s) {
        if (!s.size()) return true;
        if (s.size() % 2 == 1) return false; // 奇数不用看 肯定滚蛋
        
        stack<char> stk;
        char tmp;
        for (int i = 0; i < s.size(); ++i) {
            tmp = s[i];
            if (tmp == '(' || tmp == '[' || tmp =='{') {
                stk.push(tmp);
            }
            else if (!stk.empty() && validmap[stk.top()] == tmp) {
                stk.pop();
            }
            else return false;
        }
        return stk.empty();
    }
};


int main() {
    Solution sol;
    cout << boolalpha << sol.isValid("()") << endl;       // true
    cout << boolalpha << sol.isValid("()[]{}") << endl;   // true
    cout << boolalpha << sol.isValid("(]") << endl;       // false
    cout << boolalpha << sol.isValid("([)]") << endl;     // false
    cout << boolalpha << sol.isValid("{[]}") << endl;     // true
    cout << boolalpha << sol.isValid("") << endl;         // true

    return 0;
}