class Solution {
public:
    bool checkBipartiteDFS(vector<vector<int>>& graph, vector<int>& colours, int node, int colour) {
        colours[node] = colour;
        for (int neighbour : graph[node]) {
            if (colours[neighbour] == -1) {
                if (!checkBipartiteDFS(graph, colours, neighbour, !colour)) return false;
            } else if (colours[neighbour] == colour) return false;
        }
        return true;
    }
    bool isBipartite(vector<vector<int>>& graph) {
        int V = graph.size();
        vector<int> colours(V, -1);

        for (int i = 0; i < V; i++) {
            if (colours[i] == -1) {
                if (!checkBipartiteDFS(graph, colours, i, 0)) return false;
            }
        }

        return true;
    }
};