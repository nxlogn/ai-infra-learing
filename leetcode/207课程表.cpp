#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    // 课程依赖转换为有向图，拓扑排序判断是否存在环；
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // 邻接表 graph[b] 存储所有以b为先修课程的课程a
        vector<vector<int>> graph(numCourses);

        // indegree[i] 表示课程i的先修课程数量
        vector<int> indegree(numCourses, 0);

        // 遍历边，初始化邻接表和入度表
        for (auto& p: prerequisites) {
            int a = p[0];
            int b = p[1];
            graph[b].push_back(a);
            indegree[a]++;
        }

        // 入度为0的课程入队
        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        // 记录已修完的课程数
        int finished = 0;
        while (!q.empty()) {
            int course = q.front();
            q.pop();
            finished++;

            // 解除它对后继课程的限制
            for (int next: graph[course]) {
                if (--indegree[next] == 0) {
                    q.push(next);
                }
            }
        }

        return finished == numCourses;
    }
};