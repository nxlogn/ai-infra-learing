//
// Created by 55340 on 2026/11/26.
//
#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        // 按照身高降序
        sort(people.begin(), people.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[0] != b[0]) return a[0] > b[0];
            // 同身高按照k值升序排序
            return a[1] < b[1];
        });

        vector<vector<int>> ans;

        // 逐个插入到位置k
        for (const auto& p : people) {
            ans.insert(ans.begin() + p[1], p);
        }

        return ans;
    }
};