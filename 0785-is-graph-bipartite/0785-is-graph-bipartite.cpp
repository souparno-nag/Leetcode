class Solution {
public:
    bool checkBipartite(vector<vector<int>>& graph, vector<int>& colours, int start) {
        queue<int> q;

        colours[start] = 0;
        q.push(start);

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (int n : graph[node]) {
                if (colours[n] == -1) {
                    colours[n] = !colours[node];
                    q.push(n);
                } else if (colours[n] == colours[node]) {
                    return false;
                }
            }
        }

        return true;
    }
    bool isBipartite(vector<vector<int>>& graph) {
        int V = graph.size();
        vector<int> colours(V, -1);

        for (int i = 0; i < V; i++) {
            if (colours[i] == -1) {
                if (!checkBipartite(graph, colours, i)) return false;
            }
        }

        return true;
    }
};