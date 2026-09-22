#include <vector>
using namespace std;
class Solution {
public:
    /*
    假设今天卖出，最佳买入价格就是今天之前的最低价格
    */
    int maxProfit(vector<int>& prices) {
        int minPrice = prices[0];
        int maxProfit = 0;

        for (int i = 1; i < prices.size(); ++i) {
          // 使用之前的最低价格买入，今天卖出
          maxProfit = max(maxProfit, prices[i] - minPrice);

          // 更新最低价格
          minPrice = min(minPrice, prices[i]);
        }

        return maxProfit;
    }
};