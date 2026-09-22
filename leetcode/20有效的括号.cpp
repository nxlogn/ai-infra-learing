#include <string>
#include <stack>
using namespace std;

class Solution {
public:
    /*
    遇到左括号将其入栈
    遇到右括号
      1. 栈为空，说明没有对应的左括号，返回false
      2. 栈顶元素和右括号不匹配，返回false
      3. 匹配成功，弹出栈顶
    遍历结束后，栈为空才有效，返回true
    */
    bool isValid(string s) {
      if (s.size() % 2 != 0) return false;

      stack<char> st;

      for (char c : s) {
        if (c == '(' || c == '[' || c == '{') {
          st.push(c);
        } else {
          if (st.empty()) {
            return false;
          }

          char left = st.top();

          if (c == ')' && left != '(' || c == ']' && left != '[' || c == '}' && left != '{') {
            return false;
          }

          st.pop();
        }
      }

      return st.empty();
    }
};
