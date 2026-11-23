
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>
//
// Created by 55340 on 2026/11/23.
//
using namespace std;
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        // key：排序后的字符串
        // value：属于这一组的所有原字符串
        unordered_map<string, vector<string>> groups;

        for (const string& s : strs) {
            string key = s; // 复制一份，不破坏原串
            sort(key.begin(), key.end());
            groups[key].push_back(s);
        }

        // 把每一组收集道结果中
        vector<vector<string>> ans;
        for (auto& [key, group] : groups) {
            ans.push_back(move(group)); // move 避免拷贝整组字符串
        }
        return ans;
    }
};