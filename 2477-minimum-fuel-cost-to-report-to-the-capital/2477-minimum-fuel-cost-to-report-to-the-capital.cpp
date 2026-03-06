class Solution {
public:
    long long dfs_recursive(int node, vector<vector<int>>& adj, int parent, long long* total_fuel_cost, int seats) {
        long long subtreeSize = 1; // count this node (1 person)
        
        for (int neighbor : adj[node]) {
            if (neighbor != parent) {
                long long childSubtreeSize = dfs_recursive(neighbor, adj, node, total_fuel_cost, seats);
                long long carsNeeded = (childSubtreeSize + seats - 1) / seats;
                *total_fuel_cost += carsNeeded;
                subtreeSize += childSubtreeSize;
            }
        }
        
        return subtreeSize;
    }
    
    long long minimumFuelCost(vector<vector<int>>& roads, int seats) {
        int n = roads.size() + 1; // n cities (0 to n-1)
        
        vector<vector<int>> adj(n);
        for (auto& road : roads) {
            adj[road[0]].push_back(road[1]);
            adj[road[1]].push_back(road[0]);
        }
        
        long long total_fuel_cost = 0;
        dfs_recursive(0, adj, -1, &total_fuel_cost, seats);
        
        return total_fuel_cost;
    }
};