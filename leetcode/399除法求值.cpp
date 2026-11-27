//
// Created by 55340 on 2026/11/26.
//
// LeetCode 399. 除法求值
// 思路：把变量看成图的节点，a/b = v 看成一条带权边 a --v--> b（反向边权为 1/v）。
// 查询 a/b 等价于：从 a 走到 b，把路径上的边权连乘。
// 例如 a/b=2, b/c=3，则 a/c = (a/b)*(b/c) = 6。
// 用 BFS 找路径，队列里同时记录"从起点走到当前节点累积的乘积"。
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        // 建图graph[a][b] = a / b 的值
        unordered_map<string, unordered_map<string, double>> graph;
        for (int i = 0; i < static_cast<int>(equations.size()); i++) {
            string& a = equations[i][0];
            string& b = equations[i][1];
            graph[a][b] = values[i];
            graph[b][a] = 1.0 / values[i];
        }

        // 遍历query
        vector<double> ans;
        for (const auto& query : queries) {
            const string& src = query[0]; // 起点
            const string& dst = query[1]; // 终点

            // 不含该字母，答案为-1.0
            if (!graph.count(src) || !graph.count(dst)) {
                ans.push_back(-1.0);
                continue; // 继续
            }

            // 自己除以自己，答案为1.0
            if (src == dst) {
                ans.push_back(1.0);
                continue;
            }

            // 正常情况进入bfs开始找计算路径并积累乘积作为答案
            unordered_set<string> visited; // 是否已经访问过，bfs用
            queue<pair<string, double>> q; // 到当前节点的累计乘积
            q.emplace(src, 1.0);
            visited.insert(src);

            double res = -1.0;
            while (!q.empty()) {
                auto [fst, snd] = q.front();
                q.pop();

                if (fst == dst) { // 到达终点
                    res = snd;
                    break;
                }

                // 没有到达终点，遍历后续路径，更新乘积
                for (const auto &[nextNode, weight] : graph[fst]) {
                    const string& next = nextNode;
                    const double w = weight;
                    if (!visited.count(next)) { // 已访问过的不再入队，防止沿反向边绕圈
                        visited.insert(next);
                        q.emplace(next, w * snd);
                    }
                }
            }
            ans.push_back(res);
        }
        return ans;
    }
};
