class Solution {
public:
    int climbStairs(int n) {
        if (n <= 2) return n;
        // 滚动dp
        int a = 1;
        int b = 2;

        for (int i = 3; i <= n; i++) {
          int c = a + b;
          a = b;
          b = c;
        }

        return b;
    }
};