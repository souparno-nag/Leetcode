class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> indegree(numCourses, 0);
        vector<vector<int>> adjList(numCourses, vector<int>());

        for (int i = 0; i < prerequisites.size(); i++) {
            adjList[prerequisites[i][1]].push_back(prerequisites[i][0]);
        }
        for (int node = 0; node < numCourses; node++) {
            for (int adj : adjList[node]) indegree[adj]++;
        }

        queue<int> q;
        for (int node = 0; node < numCourses; node++) {
            if (indegree[node] == 0) q.push(node);
        }

        vector<int> result;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            result.push_back(node);

            for (int adj : adjList[node]) {
                indegree[adj]--;
                if (indegree[adj] == 0) q.push(adj);
            }
        }

        if (result.size() != numCourses) return vector<int>();
        return result;
    }
};