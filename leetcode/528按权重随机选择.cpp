#include <random>
#include <vector>

using namespace std;

class Solution {
private:
  vector<int> prefix;
  int total = 0;
  mt19937 gen;

public:
  Solution(vector<int> &w) : gen(random_device{}()) {
    for (int x : w) {
      total += x;
      prefix.push_back(total);
    }
  }

  int pickIndex() {
    uniform_int_distribution<int> dis(1, total);
    int target = dis(gen);
    return lower_bound(prefix.begin(), prefix.end(), target) - prefix.begin();
  }
};