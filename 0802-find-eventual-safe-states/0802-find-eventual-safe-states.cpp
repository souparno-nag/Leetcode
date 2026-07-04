class Solution {
    static const int MAX = 10001;
    bool dfs(int node, vector<vector<int>>& graph, int visited[], int pathVisited[], int check[]) {
        visited[node] = 1;
        pathVisited[node] = 1;
        check[node] = 0;

        for (int neighbour : graph[node]) {
            if (!visited[neighbour]) {
                if (dfs(neighbour, graph, visited, pathVisited, check)) return true;
            }
            else if (pathVisited[neighbour]) return true;
        }

        check[node] = 1;
        pathVisited[node] = 0;
        return false;
    }
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int V = graph.size();
        int visited[MAX] = {0}, pathVisited[MAX] = {0}, check[MAX] = {0};
        vector<int> safeNodes;

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                dfs(i, graph, visited, pathVisited, check);
            }
        }
        
        for (int i = 0; i < V; i++) {
            if (check[i]) safeNodes.push_back(i);
        }

        return safeNodes;
    }
};