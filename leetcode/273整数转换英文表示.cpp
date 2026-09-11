#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    /**
     * 1,000,000,000 每个区域最多999，分块转换
     */
    string numberToWords(int num) {
        if (num == 0) return "Zero";

        static const int units[] = {1000000000, 1000000, 1000, 1};
        // 4个区域的后缀
        static const string unitNames[] = {"Billion", "Million", "Thousand", ""};
        
        string result;

        for (int i = 0; i < 4; i++) {
            if (num >= units[i]) {
                if (!result.empty()) result += " ";
                result += threeDigits(num / units[i]);
                // 针对于前3个区域加后缀
                if (!unitNames[i].empty()) result += " " + unitNames[i];
                num %= units[i]; 
            }
        }

        return result;
    }

private:
    string threeDigits(int n) {
        static const string belowTwenty[] = {
            "",        "One",     "Two",       "Three",    "Four",
            "Five",    "Six",     "Seven",     "Eight",    "Nine",
            "Ten",     "Eleven",  "Twelve",    "Thirteen", "Fourteen",
            "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
        static const string tens[] = {"",       "",      "Twenty", "Thirty",
                                      "Forty",  "Fifty", "Sixty",  "Seventy",
                                      "Eighty", "Ninety"};
        string res;

        if (n >= 100) {
            // 999
            res += belowTwenty[n / 100] + " Hundred";
            n %= 100;
            if (n == 0) return res;
            res += " ";
        }
        if (n >= 20) {
            // 99
            res += tens[n / 10];
            n %= 10;
            if (n == 0) return res;
            res += " " + belowTwenty[n];
        } else if (n > 0) {
            // 9
            res += belowTwenty[n];
        }
        return res;
    }
};