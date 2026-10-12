#include <stack>
using namespace std;

class MinStack {
private:
    stack<int> dataSt;
    // minSt: top存储到目前位置的最小元素
    stack<int> minSt;   
public:
    MinStack() {
        
    }
    
    void push(int value) {
        dataSt.push(value);
        if (minSt.empty() || value <= minSt.top()) {
            minSt.push(value);
        }
    }
    
    void pop() {
        if (dataSt.top() == minSt.top()) {
            minSt.pop();
        }
        dataSt.pop();
    }
    
    int top() {
        return dataSt.top();
    }
    
    int getMin() {
        return minSt.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(value);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */