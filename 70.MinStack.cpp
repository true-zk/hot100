/*
    medium
    [MinStack]：常数时间检索最小元素的栈
*/
#include <string>
#include <stack>
#include <limits>
#include <iostream>


using namespace std;


// 通过辅助栈实现：minstk存对应元素的最小值，和stk同步push和pop
// 注意到：如果顶不出栈，则后续元素永远在栈里，
// 所以之前入栈的元素的最小值永远不会变，而且栈顶不出栈，则minstk的top就是对应最小值
class MinStack {
    stack<int> stk;
    stack<int> minstk;
public:
    MinStack() {
        minstk.push(numeric_limits<int>::max());
    }
    
    void push(int val) {
        stk.push(val);
        minstk.push((val < minstk.top()) ? val: minstk.top());
    }
    
    void pop() {
        stk.pop();
        minstk.pop();
    }
    
    int top() {
        return stk.top();
    }
    
    int getMin() {
        return minstk.top();
    }
};


int main() {
    MinStack minStack;
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    cout << minStack.getMin() << endl; // -3
    minStack.pop();
    cout << minStack.top() << endl;    // 0
    cout << minStack.getMin() << endl; // -2

    return 0;
}