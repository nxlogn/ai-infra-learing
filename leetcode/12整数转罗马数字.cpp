#include <bits/stdc++.h>

using namespace std;

class Solution {
  public:
    /**
     * 4表示为IV，同理，整理所有情况的表，按贪心算法从大值取到小值
     */
    string intToRoman(int num) {
        const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
        const string symbols[] = {"M",  "CM", "D",  "CD", "C",  "XC", "L",
                                  "XL", "X",  "IX", "V",  "IV", "I"};

        string result;

        for (int i = 0; i < 13; i++) {
            while (num >= values[i]) {
                result += symbols[i];
                num -= values[i];
            }
        }

        return result;
    }
};