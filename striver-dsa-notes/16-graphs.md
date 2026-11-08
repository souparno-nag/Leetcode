# Graphs — Striver's A2Z DSA Sheet Notes

Section 16 of 20 · 44 problems · 42 with video, 2 without · [All sections](00-index.md)

[← Heaps](15-heaps.md) | [Dynamic Programming →](17-dynamic-programming.md)

> **How these notes were made:** for problems with a video, the notes follow the video's auto-generated transcript (approaches, intuition, dry runs, complexity). Code is written in C++ and Java for every approach discussed. Anything not covered in the video is marked *(not in video)*. Problems without a video are marked as such and the notes are prepared independently.

<a id="contents"></a>

## Contents

**Theory and traversals**

1. [Traversal Techniques](#p341) — Core
2. [Connected Components](#p342) — Core

**Traversal Problems**

3. [Number of provinces](#p343) — Core
4. [Number of islands](#p344) — Core
5. [Flood fill algorithm](#p345) — Core
6. [Number of enclaves](#p346) — Core
7. [Rotten Oranges](#p347) — Core
8. [Distance of nearest cell having one](#p348) — Core
9. [Surrounded Regions](#p349) — Core
10. [Number of distinct islands](#p350) — Core

**Cycles**

11. [Detect a cycle in an undirected graph](#p351) — Core
12. [Bipartite graph](#p352) — Core
13. [Topological sort or Kahn's algorithm](#p353) — Core
14. [Detect a cycle in a directed graph](#p354) — Core

**Hard Problems**

15. [Find eventual safe states](#p355) — Pro
16. [Course Schedule I](#p356) — Pro
17. [Course Schedule II](#p357) — Pro
18. [Alien Dictionary](#p358) — Pro
19. [Shortest path in DAG](#p359) — Core
20. [Shortest path in undirected graph with unit weights](#p360) — Core
21. [Word ladder I](#p361) — Pro
22. [Word ladder II](#p362) — Pro

**Shortest Path Algorithms**

23. [Dijkstra's algorithm](#p363) — Core
24. [Print Shortest Path](#p364) — Core
25. [Shortest Distance in a Binary Maze](#p365) — Core
26. [Path with minimum effort](#p366) — Core
27. [Cheapest flight within K stops](#p367) — Pro
28. [Minimum multiplications to reach end](#p368) — Pro
29. [Number of ways to arrive at destination](#p369) — Pro
30. [Bellman ford algorithm](#p370) — Pro
31. [Floyd warshall algorithm](#p371) — Pro
32. [Find the city with the smallest number of neighbors](#p372) — Pro
33. [Network Delay Time](#p373) — Core · *no video*
34. [Swim in Rising Water](#p374) — Pro · *no video*

**Minimum Spanning Tree**

35. [Disjoint Set](#p375) — Core
36. [Find the MST weight](#p376) — Core

**Hard Problems II**

37. [Number of operations to make network connected](#p377) — Core
38. [Accounts merge](#p378) — Core
39. [Number of islands II](#p379) — Pro
40. [Making a large island](#p380) — Pro
41. [Most stones removed with same row or column](#p381) — Pro

**Additional Algorithms**

42. [Kosaraju's algorithm](#p382) — Pro
43. [Bridges in graph](#p383) — Pro
44. [Articulation point in graph](#p384) — Pro

---

## Theory and traversals

<a id="p341"></a>

### 1. Traversal Techniques

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Theory and traversals | Core | Yes | — | [Watch](https://youtu.be/Qzf1a--rhp8) |

> **Graph conventions in this section:** vertices are `0 … V−1`, and the graph is stored as an **adjacency list** `adj` (`vector<vector<int>>` in C++, `List<List<Integer>>` in Java). For an undirected graph, every edge `u–v` appears in both lists. Grids use `n × m` arrays with 4-directional moves `(−1,0), (0,1), (1,0), (0,−1)` unless stated otherwise.

#### Problem Statement
Implement the two fundamental graph traversals from source `0`: **BFS** (breadth-first search, level by level) and **DFS** (depth-first search, going as deep as possible before backtracking). Return the order in which the vertices are visited.

```text
V = 5, edges: 0-1, 0-2, 0-3, 2-4   (adjacency lists in that order)
BFS: [0, 1, 2, 3, 4]       DFS: [0, 1, 2, 4, 3]
```

#### Approach 1: BFS with a queue (Striver's G-5)
- Mark the source as visited and push it into a queue.
- Pop a node, record it, and push every **unvisited** neighbour, marking it visited **when it's pushed**. Marking at push time means a node is never queued twice.
- Nodes come out in order of distance from the source.

**Complexity:** O(V + 2E) time for an undirected graph, since every adjacency entry is scanned once. O(V) space for the queue and the visited array.

**C++**
```cpp
vector<int> bfsOfGraph(int V, vector<vector<int>>& adj) {
    vector<int> vis(V, 0), bfs;
    queue<int> q;
    q.push(0);
    vis[0] = 1;
    while (!q.empty()) {
        int node = q.front(); q.pop();
        bfs.push_back(node);
        for (int it : adj[node]) {
            if (!vis[it]) { vis[it] = 1; q.push(it); }   // mark when pushed
        }
    }
    return bfs;
}
```

**Java**
```java
class Solution {
    static List<Integer> bfsOfGraph(int V, List<List<Integer>> adj) {
        int[] vis = new int[V];
        List<Integer> bfs = new ArrayList<>();
        Queue<Integer> q = new LinkedList<>();
        q.add(0);
        vis[0] = 1;
        while (!q.isEmpty()) {
            int node = q.remove();
            bfs.add(node);
            for (int it : adj.get(node)) {
                if (vis[it] == 0) { vis[it] = 1; q.add(it); }
            }
        }
        return bfs;
    }
}
```

#### Approach 2: DFS with recursion (as in the video, G-6)
- Mark the node visited and record it.
- For each neighbour that hasn't been visited, recurse **immediately**: go deep first, then come back.

**Complexity:** O(V + 2E) time. O(V) space for the visited array plus a recursion stack of up to O(V).

**C++**
```cpp
void dfsRec(int node, vector<vector<int>>& adj, vector<int>& vis, vector<int>& ls) {
    vis[node] = 1;
    ls.push_back(node);
    for (int it : adj[node])
        if (!vis[it]) dfsRec(it, adj, vis, ls);
}
vector<int> dfsOfGraph(int V, vector<vector<int>>& adj) {
    vector<int> vis(V, 0), ls;
    dfsRec(0, adj, vis, ls);
    return ls;
}
```

**Java**
```java
class Solution {
    static void dfsRec(int node, List<List<Integer>> adj, int[] vis, List<Integer> ls) {
        vis[node] = 1;
        ls.add(node);
        for (int it : adj.get(node))
            if (vis[it] == 0) dfsRec(it, adj, vis, ls);
    }
    static List<Integer> dfsOfGraph(int V, List<List<Integer>> adj) {
        int[] vis = new int[V];
        List<Integer> ls = new ArrayList<>();
        dfsRec(0, adj, vis, ls);
        return ls;
    }
}
```

#### Edge Cases & Pitfalls
- **Disconnected graphs:** to visit **every** vertex, loop over all vertices and start a new BFS or DFS from each unvisited one.
- **The visiting order depends on adjacency-list order.** Problems usually specify "in the order given".

#### Key Takeaways
- BFS explores by distance (shortest paths in unweighted graphs). DFS explores by depth (cycles, topological order, connectivity).
- Both cost O(V + E).

[↑ Contents](#contents) · [Next →](#p342)

---

<a id="p342"></a>

### 2. Connected Components

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Theory and traversals | Core | Yes | [LeetCode](https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/) | [Watch](https://youtu.be/lea-Wl_uWXY) |

#### Problem Statement
Given `n` vertices `0 … n−1` and a list of undirected `edges`, return the number of **connected components**.

```text
n = 5, edges = [[0,1],[1,2],[3,4]]   ->  2   ({0,1,2} and {3,4})
n = 5, edges = [[0,1],[1,2],[2,3],[3,4]]   ->  1
```

#### Intuition (Striver's G-4)
A graph may be split into several disconnected pieces, the components. One BFS or DFS started from a vertex visits **exactly its component**. So count how many traversals you need to start before every vertex is visited.

#### Approach 1: DFS from every unvisited vertex
**Complexity:** O(V + 2E) time, O(V + E) space for the adjacency list, plus the visited array and the stack.

**C++**
```cpp
void dfsComp(int node, vector<vector<int>>& adj, vector<int>& vis) {
    vis[node] = 1;
    for (int it : adj[node]) if (!vis[it]) dfsComp(it, adj, vis);
}
int countComponents(int n, vector<vector<int>>& edges) {
    vector<vector<int>> adj(n);
    for (auto& e : edges) { adj[e[0]].push_back(e[1]); adj[e[1]].push_back(e[0]); }
    vector<int> vis(n, 0);
    int cnt = 0;
    for (int i = 0; i < n; i++)
        if (!vis[i]) { cnt++; dfsComp(i, adj, vis); }
    return cnt;
}
```

**Java**
```java
class Solution {
    static void dfsComp(int node, List<List<Integer>> adj, int[] vis) {
        vis[node] = 1;
        for (int it : adj.get(node)) if (vis[it] == 0) dfsComp(it, adj, vis);
    }
    static int countComponents(int n, int[][] edges) {
        List<List<Integer>> adj = new ArrayList<>();
        for (int i = 0; i < n; i++) adj.add(new ArrayList<>());
        for (int[] e : edges) { adj.get(e[0]).add(e[1]); adj.get(e[1]).add(e[0]); }
        int[] vis = new int[n];
        int cnt = 0;
        for (int i = 0; i < n; i++)
            if (vis[i] == 0) { cnt++; dfsComp(i, adj, vis); }
        return cnt;
    }
}
```

#### Approach 2: Disjoint Set Union *(covered later in this section)*
Start with `n` components. Every edge that joins two **different** sets reduces the count by one.

**Complexity:** O(E·α(n)) time, O(n) space.

**C++**
```cpp
int findPar(vector<int>& par, int x) { return par[x] == x ? x : par[x] = findPar(par, par[x]); }
int countComponentsDSU(int n, vector<vector<int>>& edges) {
    vector<int> par(n);
    iota(par.begin(), par.end(), 0);
    int comps = n;
    for (auto& e : edges) {
        int a = findPar(par, e[0]), b = findPar(par, e[1]);
        if (a != b) { par[a] = b; comps--; }
    }
    return comps;
}
```

**Java**
```java
class Solution {
    static int findPar(int[] par, int x) { return par[x] == x ? x : (par[x] = findPar(par, par[x])); }
    static int countComponentsDSU(int n, int[][] edges) {
        int[] par = new int[n];
        for (int i = 0; i < n; i++) par[i] = i;
        int comps = n;
        for (int[] e : edges) {
            int a = findPar(par, e[0]), b = findPar(par, e[1]);
            if (a != b) { par[a] = b; comps--; }
        }
        return comps;
    }
}
```

#### Key Takeaways
- Components = the number of times you have to start a fresh traversal. The "loop over all vertices, traverse if unvisited" wrapper is used by almost every graph algorithm.

[↑ Contents](#contents) · [← Previous](#p341) · [Next →](#p343)

---

## Traversal Problems

<a id="p343"></a>

### 3. Number of provinces

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Traversal Problems | Core | No | [LeetCode](https://leetcode.com/problems/number-of-provinces/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/number-of-provinces) | [Watch](https://youtu.be/ACzkVtewUYA) |

#### Problem Statement
`isConnected[i][j] = 1` means cities `i` and `j` are directly connected. A **province** is a group of directly or indirectly connected cities. Return the number of provinces.

```text
isConnected = [[1,1,0],[1,1,0],[0,0,1]]   ->  2
isConnected = [[1,0,0],[0,1,0],[0,0,1]]   ->  3
```

#### Approach: Convert to an adjacency list, then count components with DFS (as in the video)
- **The matrix is an adjacency matrix.** Optionally convert it to an adjacency list, as the video does.
- **Count the DFS starts.** Run DFS from every unvisited city. The number of starts is the number of provinces.

**Complexity:** O(V²) to read the matrix, plus O(V + 2E) for the DFS. O(V + E) space.

**C++**
```cpp
void dfsProv(int node, vector<vector<int>>& adj, vector<int>& vis) {
    vis[node] = 1;
    for (int it : adj[node]) if (!vis[it]) dfsProv(it, adj, vis);
}
int findCircleNum(vector<vector<int>>& isConnected) {
    int V = isConnected.size();
    vector<vector<int>> adj(V);
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            if (isConnected[i][j] == 1 && i != j) adj[i].push_back(j);
    vector<int> vis(V, 0);
    int cnt = 0;
    for (int i = 0; i < V; i++)
        if (!vis[i]) { cnt++; dfsProv(i, adj, vis); }
    return cnt;
}
```

**Java**
```java
class Solution {
    static void dfsProv(int node, List<List<Integer>> adj, int[] vis) {
        vis[node] = 1;
        for (int it : adj.get(node)) if (vis[it] == 0) dfsProv(it, adj, vis);
    }
    static int findCircleNum(int[][] isConnected) {
        int V = isConnected.length;
        List<List<Integer>> adj = new ArrayList<>();
        for (int i = 0; i < V; i++) adj.add(new ArrayList<>());
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                if (isConnected[i][j] == 1 && i != j) adj.get(i).add(j);
        int[] vis = new int[V];
        int cnt = 0;
        for (int i = 0; i < V; i++)
            if (vis[i] == 0) { cnt++; dfsProv(i, adj, vis); }
        return cnt;
    }
}
```

#### Key Takeaways
- Provinces are connected components of an adjacency-matrix graph.

[↑ Contents](#contents) · [← Previous](#p342) · [Next →](#p344)

---

<a id="p344"></a>

### 4. Number of islands

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Traversal Problems | Core | No | [LeetCode](https://leetcode.com/problems/number-of-islands/) | [Watch](https://youtu.be/muncqlKJrH0) |

#### Problem Statement
In a grid of `'1'` (land) and `'0'` (water), count the **islands**: groups of land cells connected horizontally or vertically. (Striver's G-8 solves the GfG version, where **diagonal** neighbours also connect; the code below takes the direction set as a switch.)

```text
grid = [["1","1","0","0","0"],
        ["1","1","0","0","0"],
        ["0","0","1","0","0"],
        ["0","0","0","1","1"]]   ->  3   (4-directional)
```

#### Approach: BFS from every unvisited land cell (as in the video)
- Scan the grid. Each unvisited `'1'` starts a new island: `cnt++`, then BFS over all connected land, marking it visited.
- **Neighbours:**
  - 4-directional: `(−1,0), (0,1), (1,0), (0,−1)`;
  - 8-directional (GfG and the video): every `(dr, dc)` with `dr, dc ∈ {−1, 0, 1}` except `(0,0)`.

**Complexity:** O(n·m · directions) time, O(n·m) space for the visited array and the queue.

**C++**
```cpp
void bfsIsland(int r, int c, vector<vector<char>>& grid, vector<vector<int>>& vis, bool diag) {
    int n = grid.size(), m = grid[0].size();
    queue<pair<int, int>> q;
    q.push({r, c});
    vis[r][c] = 1;
    while (!q.empty()) {
        auto [row, col] = q.front(); q.pop();
        for (int dr = -1; dr <= 1; dr++)
            for (int dc = -1; dc <= 1; dc++) {
                if (dr == 0 && dc == 0) continue;
                if (!diag && dr != 0 && dc != 0) continue;     // 4-directional only
                int nr = row + dr, nc = col + dc;
                if (nr >= 0 && nr < n && nc >= 0 && nc < m && grid[nr][nc] == '1' && !vis[nr][nc]) {
                    vis[nr][nc] = 1;
                    q.push({nr, nc});
                }
            }
    }
}
int numIslands(vector<vector<char>>& grid, bool diag = false) {
    int n = grid.size(), m = grid[0].size(), cnt = 0;
    vector<vector<int>> vis(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (grid[i][j] == '1' && !vis[i][j]) { cnt++; bfsIsland(i, j, grid, vis, diag); }
    return cnt;
}
```

**Java**
```java
class Solution {
    static void bfsIsland(int r, int c, char[][] grid, int[][] vis, boolean diag) {
        int n = grid.length, m = grid[0].length;
        Queue<int[]> q = new LinkedList<>();
        q.add(new int[]{r, c});
        vis[r][c] = 1;
        while (!q.isEmpty()) {
            int[] cur = q.remove();
            for (int dr = -1; dr <= 1; dr++)
                for (int dc = -1; dc <= 1; dc++) {
                    if (dr == 0 && dc == 0) continue;
                    if (!diag && dr != 0 && dc != 0) continue;
                    int nr = cur[0] + dr, nc = cur[1] + dc;
                    if (nr >= 0 && nr < n && nc >= 0 && nc < m && grid[nr][nc] == '1' && vis[nr][nc] == 0) {
                        vis[nr][nc] = 1;
                        q.add(new int[]{nr, nc});
                    }
                }
        }
    }
    static int numIslands(char[][] grid, boolean diag) {
        int n = grid.length, m = grid[0].length, cnt = 0;
        int[][] vis = new int[n][m];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (grid[i][j] == '1' && vis[i][j] == 0) { cnt++; bfsIsland(i, j, grid, vis, diag); }
        return cnt;
    }
}
```

#### Key Takeaways
- A grid is an implicit graph whose neighbours are the adjacent cells. Islands are its connected components.

[↑ Contents](#contents) · [← Previous](#p343) · [Next →](#p345)

---

<a id="p345"></a>

### 5. Flood fill algorithm

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Traversal Problems | Core | No | [LeetCode](https://leetcode.com/problems/flood-fill/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/flood-fill-algorithm) | [Watch](https://youtu.be/C-2_uSRli8o) |

#### Problem Statement
Starting from pixel `(sr, sc)`, recolour every pixel **4-directionally connected** to it that has the **same colour as the start** to `newColor`. Return the image.

```text
image = [[1,1,1],[1,1,0],[1,0,1]], sr = 1, sc = 1, newColor = 2
     ->  [[2,2,2],[2,2,0],[2,0,1]]
```

#### Approach: DFS from the start, recolouring matching cells (as in the video, G-9)
- **Work on a copy** of the image, as the video does, so the input isn't modified.
- **Record `initColor`**, the start pixel's colour.
- **DFS:** recolour the current cell, then recurse into each 4-neighbour that is in bounds, has `initColor`, and hasn't already been recoloured.

The recoloured cells double as the "visited" marker, so no extra array is needed, **provided `newColor != initColor`**.

**Complexity:** O(n·m) time, since each cell is visited at most once with 4 checks. O(n·m) space for the copy and the recursion stack.

**C++**
```cpp
void dfsFill(int r, int c, vector<vector<int>>& ans, vector<vector<int>>& image, int newColor, int initColor) {
    ans[r][c] = newColor;
    int n = image.size(), m = image[0].size();
    int dr[] = {-1, 0, 1, 0}, dc[] = {0, 1, 0, -1};
    for (int k = 0; k < 4; k++) {
        int nr = r + dr[k], nc = c + dc[k];
        if (nr >= 0 && nr < n && nc >= 0 && nc < m && image[nr][nc] == initColor && ans[nr][nc] != newColor)
            dfsFill(nr, nc, ans, image, newColor, initColor);
    }
}
vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
    int initColor = image[sr][sc];
    vector<vector<int>> ans = image;
    if (initColor == newColor) return ans;            // nothing to do (and avoids infinite loop)
    dfsFill(sr, sc, ans, image, newColor, initColor);
    return ans;
}
```

**Java**
```java
class Solution {
    static void dfsFill(int r, int c, int[][] ans, int[][] image, int newColor, int initColor) {
        ans[r][c] = newColor;
        int n = image.length, m = image[0].length;
        int[] dr = {-1, 0, 1, 0}, dc = {0, 1, 0, -1};
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k], nc = c + dc[k];
            if (nr >= 0 && nr < n && nc >= 0 && nc < m && image[nr][nc] == initColor && ans[nr][nc] != newColor)
                dfsFill(nr, nc, ans, image, newColor, initColor);
        }
    }
    static int[][] floodFill(int[][] image, int sr, int sc, int newColor) {
        int initColor = image[sr][sc];
        int[][] ans = new int[image.length][];
        for (int i = 0; i < image.length; i++) ans[i] = image[i].clone();
        if (initColor == newColor) return ans;
        dfsFill(sr, sc, ans, image, newColor, initColor);
        return ans;
    }
}
```

#### Edge Cases & Pitfalls
- **`newColor == initColor`:** without the early return, an in-place version would recurse forever, because recoloured cells still match.

#### Key Takeaways
- Flood fill is DFS or BFS over a component defined by colour equality. It's the paint-bucket tool.

[↑ Contents](#contents) · [← Previous](#p344) · [Next →](#p346)

---

<a id="p346"></a>

### 6. Number of enclaves

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Traversal Problems | Core | No | [LeetCode](https://leetcode.com/problems/number-of-enclaves/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/number-of-enclaves) | [Watch](https://youtu.be/rxKcepXQgU4) |

#### Problem Statement
In a binary grid, `1` is land and `0` is sea. Count the land cells from which you **cannot** walk off the boundary of the grid, moving 4-directionally over land.

```text
grid = [[0,0,0,0],
        [1,0,1,0],
        [0,1,1,0],
        [0,0,0,0]]   ->  3   (the land at (1,0) touches the boundary; the other 3 are enclosed)
```

#### Intuition
A land cell can escape iff it is connected to some **boundary land cell**. So mark everything reachable from boundary land, and count the land left unmarked.

#### Approach: Multi-source BFS from the boundary land (as in the video)
- Push every boundary `1` into a queue and mark it visited.
- BFS over land.
- Count the `1`s that were never visited.

**Complexity:** O(n·m·4) time, O(n·m) space.

**C++**
```cpp
int numEnclaves(vector<vector<int>>& grid) {
    int n = grid.size(), m = grid[0].size();
    vector<vector<int>> vis(n, vector<int>(m, 0));
    queue<pair<int, int>> q;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if ((i == 0 || j == 0 || i == n - 1 || j == m - 1) && grid[i][j] == 1) {
                q.push({i, j});
                vis[i][j] = 1;
            }
    int dr[] = {-1, 0, 1, 0}, dc[] = {0, 1, 0, -1};
    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k], nc = c + dc[k];
            if (nr >= 0 && nr < n && nc >= 0 && nc < m && grid[nr][nc] == 1 && !vis[nr][nc]) {
                vis[nr][nc] = 1;
                q.push({nr, nc});
            }
        }
    }
    int cnt = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (grid[i][j] == 1 && !vis[i][j]) cnt++;
    return cnt;
}
```

**Java**
```java
class Solution {
    static int numEnclaves(int[][] grid) {
        int n = grid.length, m = grid[0].length;
        int[][] vis = new int[n][m];
        Queue<int[]> q = new LinkedList<>();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if ((i == 0 || j == 0 || i == n - 1 || j == m - 1) && grid[i][j] == 1) {
                    q.add(new int[]{i, j});
                    vis[i][j] = 1;
                }
        int[] dr = {-1, 0, 1, 0}, dc = {0, 1, 0, -1};
        while (!q.isEmpty()) {
            int[] cur = q.remove();
            for (int k = 0; k < 4; k++) {
                int nr = cur[0] + dr[k], nc = cur[1] + dc[k];
                if (nr >= 0 && nr < n && nc >= 0 && nc < m && grid[nr][nc] == 1 && vis[nr][nc] == 0) {
                    vis[nr][nc] = 1;
                    q.add(new int[]{nr, nc});
                }
            }
        }
        int cnt = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (grid[i][j] == 1 && vis[i][j] == 0) cnt++;
        return cnt;
    }
}
```

#### Key Takeaways
- "Cells that can't reach the boundary" means: traverse **from** the boundary inward, then count what wasn't reached.

[↑ Contents](#contents) · [← Previous](#p345) · [Next →](#p347)

---

<a id="p347"></a>

### 7. Rotten Oranges

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Traversal Problems | Core | No | [LeetCode](https://leetcode.com/problems/rotting-oranges/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/rotting-oranges) | [Watch](https://youtu.be/yf3oUhkvqA0) |

#### Problem Statement
In a grid, `0` is empty, `1` is a fresh orange and `2` is a rotten one. Each minute, rotten oranges rot their 4-directional fresh neighbours. Return the minimum number of minutes until no fresh orange remains, or −1 if that's impossible.

```text
grid = [[2,1,1],[1,1,0],[0,1,1]]   ->  4
grid = [[2,1,1],[0,1,1],[1,0,1]]   ->  -1   (bottom-left orange is unreachable)
grid = [[0,2]]                     ->  0
```

#### Approach: Multi-source BFS with time stamps (as in the video)
- **Why BFS, not DFS.** Rot spreads **simultaneously** from every rotten orange, one layer per minute, which is BFS from multiple sources at once. DFS would follow one chain at a time and get the timing wrong.
- **The BFS:**
  - push every initially rotten cell with time 0, and count the fresh oranges;
  - pop `(r, c, t)`, and for each fresh neighbour, mark it rotten (in a visited copy) and push it with `t + 1`;
  - track the maximum `t` and how many fresh oranges were rotted.
- **The answer:** if the rotted count equals the fresh count, return the maximum time; otherwise −1.

**Complexity:** O(n·m·4) time, O(n·m) space.

**C++**
```cpp
int orangesRotting(vector<vector<int>>& grid) {
    int n = grid.size(), m = grid[0].size();
    queue<pair<pair<int, int>, int>> q;                 // {{r, c}, time}
    vector<vector<int>> vis(n, vector<int>(m, 0));
    int fresh = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 2) { q.push({{i, j}, 0}); vis[i][j] = 2; }
            if (grid[i][j] == 1) fresh++;
        }
    int tm = 0, cnt = 0;
    int dr[] = {-1, 0, 1, 0}, dc[] = {0, 1, 0, -1};
    while (!q.empty()) {
        auto [rc, t] = q.front(); q.pop();
        tm = max(tm, t);
        for (int k = 0; k < 4; k++) {
            int nr = rc.first + dr[k], nc = rc.second + dc[k];
            if (nr >= 0 && nr < n && nc >= 0 && nc < m && vis[nr][nc] != 2 && grid[nr][nc] == 1) {
                vis[nr][nc] = 2;
                q.push({{nr, nc}, t + 1});
                cnt++;
            }
        }
    }
    return cnt == fresh ? tm : -1;
}
```

**Java**
```java
class Solution {
    static int orangesRotting(int[][] grid) {
        int n = grid.length, m = grid[0].length;
        Queue<int[]> q = new LinkedList<>();             // {r, c, time}
        int[][] vis = new int[n][m];
        int fresh = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 2) { q.add(new int[]{i, j, 0}); vis[i][j] = 2; }
                if (grid[i][j] == 1) fresh++;
            }
        int tm = 0, cnt = 0;
        int[] dr = {-1, 0, 1, 0}, dc = {0, 1, 0, -1};
        while (!q.isEmpty()) {
            int[] cur = q.remove();
            tm = Math.max(tm, cur[2]);
            for (int k = 0; k < 4; k++) {
                int nr = cur[0] + dr[k], nc = cur[1] + dc[k];
                if (nr >= 0 && nr < n && nc >= 0 && nc < m && vis[nr][nc] != 2 && grid[nr][nc] == 1) {
                    vis[nr][nc] = 2;
                    q.add(new int[]{nr, nc, cur[2] + 1});
                    cnt++;
                }
            }
        }
        return cnt == fresh ? tm : -1;
    }
}
```

#### Key Takeaways
- "Simultaneous spreading" means multi-source BFS. The answer is the BFS depth at which the last cell is reached.

[↑ Contents](#contents) · [← Previous](#p346) · [Next →](#p348)

---

<a id="p348"></a>

### 8. Distance of nearest cell having one

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Traversal Problems | Core | No | [LeetCode](https://leetcode.com/problems/01-matrix/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/distance-of-the-nearest-cell-having-1-in-a-binary-matrix) | [Watch](https://youtu.be/edXdVwkYHF8) |

#### Problem Statement
For every cell of a binary grid, return the distance to the **nearest cell containing 1**: Manhattan distance `|r1 − r2| + |c1 − c2|`, moving 4-directionally. LeetCode 542 (01 Matrix) asks the mirror question, the distance to the nearest **0**.

```text
grid = [[0,1,1,0],[1,1,0,0],[0,0,1,1]]   ->  [[1,0,0,1],[0,0,1,1],[1,1,0,0]]
```

#### Approach: Multi-source BFS from all the 1s (as in the video, G-13)
- **Why it works.** Running BFS separately from every cell would be O((nm)²). Instead, start the BFS from **every source at once**: all 1s at distance 0. BFS reaches each cell first from its nearest source, so the first time a cell is reached gives its answer.
- **The BFS:** push every `1` with step 0 and mark it visited. Pop `(r, c, s)`, record `dist[r][c] = s`, and push each unvisited neighbour with `s + 1`.

**Complexity:** O(n·m·4) time, O(n·m) space.

**C++**
```cpp
vector<vector<int>> nearest(vector<vector<int>>& grid) {
    int n = grid.size(), m = grid[0].size();
    vector<vector<int>> vis(n, vector<int>(m, 0)), dist(n, vector<int>(m, 0));
    queue<pair<pair<int, int>, int>> q;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (grid[i][j] == 1) { q.push({{i, j}, 0}); vis[i][j] = 1; }    // all sources at once
    int dr[] = {-1, 0, 1, 0}, dc[] = {0, 1, 0, -1};
    while (!q.empty()) {
        auto [rc, steps] = q.front(); q.pop();
        dist[rc.first][rc.second] = steps;
        for (int k = 0; k < 4; k++) {
            int nr = rc.first + dr[k], nc = rc.second + dc[k];
            if (nr >= 0 && nr < n && nc >= 0 && nc < m && !vis[nr][nc]) {
                vis[nr][nc] = 1;
                q.push({{nr, nc}, steps + 1});
            }
        }
    }
    return dist;
}
```

**Java**
```java
class Solution {
    static int[][] nearest(int[][] grid) {
        int n = grid.length, m = grid[0].length;
        int[][] vis = new int[n][m], dist = new int[n][m];
        Queue<int[]> q = new LinkedList<>();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (grid[i][j] == 1) { q.add(new int[]{i, j, 0}); vis[i][j] = 1; }
        int[] dr = {-1, 0, 1, 0}, dc = {0, 1, 0, -1};
        while (!q.isEmpty()) {
            int[] cur = q.remove();
            dist[cur[0]][cur[1]] = cur[2];
            for (int k = 0; k < 4; k++) {
                int nr = cur[0] + dr[k], nc = cur[1] + dc[k];
                if (nr >= 0 && nr < n && nc >= 0 && nc < m && vis[nr][nc] == 0) {
                    vis[nr][nc] = 1;
                    q.add(new int[]{nr, nc, cur[2] + 1});
                }
            }
        }
        return dist;
    }
}
```

#### Edge Cases & Pitfalls
- **LeetCode 01 Matrix:** use the **0** cells as the sources.
- **The grid must contain at least one source**, or no distances are defined.

#### Key Takeaways
- Nearest-source distance for every cell is one multi-source BFS.

[↑ Contents](#contents) · [← Previous](#p347) · [Next →](#p349)

---

<a id="p349"></a>

### 9. Surrounded Regions

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Traversal Problems | Core | No | [LeetCode](https://leetcode.com/problems/surrounded-regions/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/surrounded-regions) | [Watch](https://youtu.be/BtdgAys4yMk) |

#### Problem Statement
A board holds `'X'` and `'O'`. **Capture** every region of `'O'` that is completely surrounded by `'X'` by flipping it to `'X'`. Regions connected to the **border** survive.

```text
X X X X        X X X X
X O O X   ->   X X X X
X X O X        X X X X
X O X X        X O X X     (the bottom O touches the border, so it survives)
```

#### Approach: DFS from the border O's, then flip everything else (as in the video)
- **Find the survivors.** An `'O'` survives iff it is connected to an `'O'` on the border. DFS from every border `'O'` and mark everything reachable.
- **Flip the rest.** Every **unmarked** `'O'` becomes `'X'`.

**Complexity:** O(n·m·4) time, O(n·m) space for the visited array and the recursion.

**C++**
```cpp
void dfsMark(int r, int c, vector<vector<char>>& board, vector<vector<int>>& vis) {
    vis[r][c] = 1;
    int n = board.size(), m = board[0].size();
    int dr[] = {-1, 0, 1, 0}, dc[] = {0, 1, 0, -1};
    for (int k = 0; k < 4; k++) {
        int nr = r + dr[k], nc = c + dc[k];
        if (nr >= 0 && nr < n && nc >= 0 && nc < m && !vis[nr][nc] && board[nr][nc] == 'O')
            dfsMark(nr, nc, board, vis);
    }
}
void solve(vector<vector<char>>& board) {
    int n = board.size(), m = board[0].size();
    vector<vector<int>> vis(n, vector<int>(m, 0));
    for (int j = 0; j < m; j++) {
        if (board[0][j] == 'O' && !vis[0][j]) dfsMark(0, j, board, vis);
        if (board[n - 1][j] == 'O' && !vis[n - 1][j]) dfsMark(n - 1, j, board, vis);
    }
    for (int i = 0; i < n; i++) {
        if (board[i][0] == 'O' && !vis[i][0]) dfsMark(i, 0, board, vis);
        if (board[i][m - 1] == 'O' && !vis[i][m - 1]) dfsMark(i, m - 1, board, vis);
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (board[i][j] == 'O' && !vis[i][j]) board[i][j] = 'X';   // surrounded
}
```

**Java**
```java
class Solution {
    static void dfsMark(int r, int c, char[][] board, int[][] vis) {
        vis[r][c] = 1;
        int n = board.length, m = board[0].length;
        int[] dr = {-1, 0, 1, 0}, dc = {0, 1, 0, -1};
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k], nc = c + dc[k];
            if (nr >= 0 && nr < n && nc >= 0 && nc < m && vis[nr][nc] == 0 && board[nr][nc] == 'O')
                dfsMark(nr, nc, board, vis);
        }
    }
    static void solve(char[][] board) {
        int n = board.length, m = board[0].length;
        int[][] vis = new int[n][m];
        for (int j = 0; j < m; j++) {
            if (board[0][j] == 'O' && vis[0][j] == 0) dfsMark(0, j, board, vis);
            if (board[n - 1][j] == 'O' && vis[n - 1][j] == 0) dfsMark(n - 1, j, board, vis);
        }
        for (int i = 0; i < n; i++) {
            if (board[i][0] == 'O' && vis[i][0] == 0) dfsMark(i, 0, board, vis);
            if (board[i][m - 1] == 'O' && vis[i][m - 1] == 0) dfsMark(i, m - 1, board, vis);
        }
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (board[i][j] == 'O' && vis[i][j] == 0) board[i][j] = 'X';
    }
}
```

#### Key Takeaways
- This is the same "work inward from the boundary" trick as Number of Enclaves.

[↑ Contents](#contents) · [← Previous](#p348) · [Next →](#p350)

---

<a id="p350"></a>

### 10. Number of distinct islands

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Traversal Problems | Core | Yes | [LeetCode](https://leetcode.com/problems/number-of-distinct-islands/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/number-of-distinct-islands) | [Watch](https://youtu.be/7zmgQSJghpo) |

#### Problem Statement
Count the islands of `1`s (4-directional) that are **distinct in shape**. Two islands are the same if one can be **translated**, without rotation or reflection, onto the other.

```text
grid = [[1,1,0,1,1],
        [1,0,0,0,0],
        [0,0,0,0,1],
        [1,1,0,1,1]]   ->  3
```

#### Approach: DFS recording each cell relative to the island's first cell (as in the video, G-16)
- **Normalise the position.** Translation-invariance means: subtract the coordinates of the island's **base cell**, the first cell found in row-major order, from every cell of the island.
- **Record a canonical shape.** DFS in a fixed neighbour order, so the same shape always produces the same list of offsets.
- **Count distinct lists.** Insert each island's list into a **set** of vectors. The set's size is the answer.

**Complexity:**
- Time: O(n·m·4) for the DFS, plus O(n·m · log(n·m)) for the set insertions.
- Space: O(n·m).

**C++**
```cpp
void dfsShape(int r, int c, vector<vector<int>>& grid, vector<vector<int>>& vis,
              vector<pair<int, int>>& shape, int r0, int c0) {
    vis[r][c] = 1;
    shape.push_back({r - r0, c - c0});                      // relative to base cell
    int n = grid.size(), m = grid[0].size();
    int dr[] = {-1, 0, 1, 0}, dc[] = {0, 1, 0, -1};
    for (int k = 0; k < 4; k++) {
        int nr = r + dr[k], nc = c + dc[k];
        if (nr >= 0 && nr < n && nc >= 0 && nc < m && !vis[nr][nc] && grid[nr][nc] == 1)
            dfsShape(nr, nc, grid, vis, shape, r0, c0);
    }
}
int countDistinctIslands(vector<vector<int>>& grid) {
    int n = grid.size(), m = grid[0].size();
    vector<vector<int>> vis(n, vector<int>(m, 0));
    set<vector<pair<int, int>>> shapes;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (grid[i][j] == 1 && !vis[i][j]) {
                vector<pair<int, int>> shape;
                dfsShape(i, j, grid, vis, shape, i, j);
                shapes.insert(shape);
            }
    return shapes.size();
}
```

**Java**
```java
class Solution {
    static void dfsShape(int r, int c, int[][] grid, int[][] vis, List<String> shape, int r0, int c0) {
        vis[r][c] = 1;
        shape.add((r - r0) + "," + (c - c0));
        int n = grid.length, m = grid[0].length;
        int[] dr = {-1, 0, 1, 0}, dc = {0, 1, 0, -1};
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k], nc = c + dc[k];
            if (nr >= 0 && nr < n && nc >= 0 && nc < m && vis[nr][nc] == 0 && grid[nr][nc] == 1)
                dfsShape(nr, nc, grid, vis, shape, r0, c0);
        }
    }
    static int countDistinctIslands(int[][] grid) {
        int n = grid.length, m = grid[0].length;
        int[][] vis = new int[n][m];
        Set<List<String>> shapes = new HashSet<>();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (grid[i][j] == 1 && vis[i][j] == 0) {
                    List<String> shape = new ArrayList<>();
                    dfsShape(i, j, grid, vis, shape, i, j);
                    shapes.add(shape);
                }
        return shapes.size();
    }
}
```

#### Key Takeaways
- To compare shapes up to translation, store coordinates relative to a canonical base cell and traverse in a fixed order. Then de-duplicate with a set.

[↑ Contents](#contents) · [← Previous](#p349) · [Next →](#p351)

---

## Cycles

<a id="p351"></a>

### 11. Detect a cycle in an undirected graph

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Cycles | Core | Yes | [LeetCode](https://leetcode.com/problems/course-schedule/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/detect-a-cycle-in-an-undirected-graph) | [Watch](https://youtu.be/zQ3zgFypzX4) |

#### Problem Statement
Return `true` if an **undirected** graph with `V` vertices (possibly disconnected) contains a **cycle**.

```text
V = 5, edges: 0-1, 1-2, 2-3, 3-1, 3-4   ->  true   (1-2-3-1)
V = 4, edges: 0-1, 1-2, 2-3             ->  false  (a tree)
```

#### Intuition
- **What a cycle looks like during traversal.** In an undirected graph you can walk back along the edge you came from, but that isn't a cycle. A cycle exists iff during BFS or DFS you find an **already visited** neighbour **that isn't your parent**: two different paths reached the same vertex.
- **Disconnected graphs.** Run the check from every unvisited vertex.

#### Approach 1: BFS with (node, parent) (Striver's G-11)
**Complexity:** O(V + 2E) time, O(V) space.

**C++**
```cpp
bool bfsCycle(int src, vector<vector<int>>& adj, vector<int>& vis) {
    queue<pair<int, int>> q;                       // {node, parent}
    q.push({src, -1});
    vis[src] = 1;
    while (!q.empty()) {
        auto [node, parent] = q.front(); q.pop();
        for (int it : adj[node]) {
            if (!vis[it]) { vis[it] = 1; q.push({it, node}); }
            else if (it != parent) return true;   // visited by another path
        }
    }
    return false;
}
bool isCycleBFS(int V, vector<vector<int>>& adj) {
    vector<int> vis(V, 0);
    for (int i = 0; i < V; i++)
        if (!vis[i] && bfsCycle(i, adj, vis)) return true;
    return false;
}
```

**Java**
```java
class Solution {
    static boolean bfsCycle(int src, List<List<Integer>> adj, int[] vis) {
        Queue<int[]> q = new LinkedList<>();
        q.add(new int[]{src, -1});
        vis[src] = 1;
        while (!q.isEmpty()) {
            int[] cur = q.remove();
            int node = cur[0], parent = cur[1];
            for (int it : adj.get(node)) {
                if (vis[it] == 0) { vis[it] = 1; q.add(new int[]{it, node}); }
                else if (it != parent) return true;
            }
        }
        return false;
    }
    static boolean isCycleBFS(int V, List<List<Integer>> adj) {
        int[] vis = new int[V];
        for (int i = 0; i < V; i++)
            if (vis[i] == 0 && bfsCycle(i, adj, vis)) return true;
        return false;
    }
}
```

#### Approach 2: DFS with a parent parameter (as in the video, G-12)
**Complexity:** O(V + 2E) time, O(V) space.

**C++**
```cpp
bool dfsCycle(int node, int parent, vector<vector<int>>& adj, vector<int>& vis) {
    vis[node] = 1;
    for (int it : adj[node]) {
        if (!vis[it]) { if (dfsCycle(it, node, adj, vis)) return true; }
        else if (it != parent) return true;
    }
    return false;
}
bool isCycle(int V, vector<vector<int>>& adj) {
    vector<int> vis(V, 0);
    for (int i = 0; i < V; i++)
        if (!vis[i] && dfsCycle(i, -1, adj, vis)) return true;
    return false;
}
```

**Java**
```java
class Solution {
    static boolean dfsCycle(int node, int parent, List<List<Integer>> adj, int[] vis) {
        vis[node] = 1;
        for (int it : adj.get(node)) {
            if (vis[it] == 0) { if (dfsCycle(it, node, adj, vis)) return true; }
            else if (it != parent) return true;
        }
        return false;
    }
    static boolean isCycle(int V, List<List<Integer>> adj) {
        int[] vis = new int[V];
        for (int i = 0; i < V; i++)
            if (vis[i] == 0 && dfsCycle(i, -1, adj, vis)) return true;
        return false;
    }
}
```

#### Edge Cases & Pitfalls
- **Parallel edges** (two edges `u–v`) form a cycle that the parent check misses. Track the parent **edge id** if multigraphs are possible.
- **This check is for undirected graphs only.** In a directed graph, a visited neighbour doesn't imply a cycle; see the directed version.

#### Key Takeaways
- Undirected cycle = reaching a visited vertex other than the one you came from.

[↑ Contents](#contents) · [← Previous](#p350) · [Next →](#p352)

---

<a id="p352"></a>

### 12. Bipartite graph

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Cycles | Core | No | [LeetCode](https://leetcode.com/problems/is-graph-bipartite/) | [Watch](https://youtu.be/KG5YFfR0j8A) |

#### Problem Statement
A graph is **bipartite** if its vertices can be coloured with **two colours** so that every edge joins different colours. Return whether the graph (possibly disconnected) is bipartite.

```text
graph = [[1,3],[0,2],[1,3],[0,2]]         ->  true    (a 4-cycle)
graph = [[1,2,3],[0,2],[0,1,3],[0,2]]     ->  false   (triangle 0-1-2)
```

#### Intuition
- **Two-colour as you traverse.** Colour the start 0, its neighbours 1, their neighbours 0, and so on.
- **A conflict means "not bipartite".** If you ever find a neighbour that **already has the same colour**, the graph isn't bipartite. That happens exactly when the graph has an **odd-length cycle**. Linear graphs and even cycles are always bipartite.

#### Approach 1: BFS colouring (Striver's G-17)
**Complexity:** O(V + 2E) time, O(V) space.

**C++**
```cpp
bool bfsColor(int src, vector<vector<int>>& graph, vector<int>& color) {
    queue<int> q;
    q.push(src);
    color[src] = 0;
    while (!q.empty()) {
        int node = q.front(); q.pop();
        for (int it : graph[node]) {
            if (color[it] == -1) { color[it] = !color[node]; q.push(it); }
            else if (color[it] == color[node]) return false;   // same colour on an edge
        }
    }
    return true;
}
bool isBipartiteBFS(vector<vector<int>>& graph) {
    int V = graph.size();
    vector<int> color(V, -1);
    for (int i = 0; i < V; i++)
        if (color[i] == -1 && !bfsColor(i, graph, color)) return false;
    return true;
}
```

**Java**
```java
class Solution {
    static boolean bfsColor(int src, int[][] graph, int[] color) {
        Queue<Integer> q = new LinkedList<>();
        q.add(src);
        color[src] = 0;
        while (!q.isEmpty()) {
            int node = q.remove();
            for (int it : graph[node]) {
                if (color[it] == -1) { color[it] = 1 - color[node]; q.add(it); }
                else if (color[it] == color[node]) return false;
            }
        }
        return true;
    }
    static boolean isBipartiteBFS(int[][] graph) {
        int V = graph.length;
        int[] color = new int[V];
        Arrays.fill(color, -1);
        for (int i = 0; i < V; i++)
            if (color[i] == -1 && !bfsColor(i, graph, color)) return false;
        return true;
    }
}
```

#### Approach 2: DFS colouring (as in the video, G-18)
**Complexity:** O(V + 2E) time, O(V) space.

**C++**
```cpp
bool dfsColor(int node, int col, vector<vector<int>>& graph, vector<int>& color) {
    color[node] = col;
    for (int it : graph[node]) {
        if (color[it] == -1) { if (!dfsColor(it, !col, graph, color)) return false; }
        else if (color[it] == col) return false;
    }
    return true;
}
bool isBipartite(vector<vector<int>>& graph) {
    int V = graph.size();
    vector<int> color(V, -1);
    for (int i = 0; i < V; i++)
        if (color[i] == -1 && !dfsColor(i, 0, graph, color)) return false;
    return true;
}
```

**Java**
```java
class Solution {
    static boolean dfsColor(int node, int col, int[][] graph, int[] color) {
        color[node] = col;
        for (int it : graph[node]) {
            if (color[it] == -1) { if (!dfsColor(it, 1 - col, graph, color)) return false; }
            else if (color[it] == col) return false;
        }
        return true;
    }
    static boolean isBipartite(int[][] graph) {
        int V = graph.length;
        int[] color = new int[V];
        Arrays.fill(color, -1);
        for (int i = 0; i < V; i++)
            if (color[i] == -1 && !dfsColor(i, 0, graph, color)) return false;
        return true;
    }
}
```

#### Key Takeaways
- Bipartite ⇔ 2-colourable ⇔ no odd cycle. Check it by colouring alternately during BFS or DFS.

[↑ Contents](#contents) · [← Previous](#p351) · [Next →](#p353)

---

<a id="p353"></a>

### 13. Topological sort or Kahn's algorithm

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Cycles | Core | No | — | [Watch](https://youtu.be/5lZ0iJMrUMk) |

#### Problem Statement
Return a **topological ordering** of a **DAG** (directed acyclic graph): a linear order of the vertices such that for every edge `u → v`, `u` comes before `v`.

```text
V = 6, edges: 5->0, 5->2, 4->0, 4->1, 2->3, 3->1   ->  e.g. [5, 4, 2, 3, 1, 0]   (many valid orders)
```

#### Approach 1: DFS + stack (as in the video, G-21)
- **Finish before you push.** A vertex is pushed onto a stack **after** all of its descendants have been fully explored, i.e. in postorder.
- **Read the stack.** Popping it gives a valid topological order: everything a vertex points to is already below it in the stack.

**Complexity:** O(V + E) time, O(V) space.

**C++**
```cpp
void dfsTopo(int node, vector<vector<int>>& adj, vector<int>& vis, stack<int>& st) {
    vis[node] = 1;
    for (int it : adj[node]) if (!vis[it]) dfsTopo(it, adj, vis, st);
    st.push(node);                                  // all descendants are done
}
vector<int> topoSortDFS(int V, vector<vector<int>>& adj) {
    vector<int> vis(V, 0), ans;
    stack<int> st;
    for (int i = 0; i < V; i++) if (!vis[i]) dfsTopo(i, adj, vis, st);
    while (!st.empty()) { ans.push_back(st.top()); st.pop(); }
    return ans;
}
```

**Java**
```java
class Solution {
    static void dfsTopo(int node, List<List<Integer>> adj, int[] vis, Deque<Integer> st) {
        vis[node] = 1;
        for (int it : adj.get(node)) if (vis[it] == 0) dfsTopo(it, adj, vis, st);
        st.push(node);
    }
    static List<Integer> topoSortDFS(int V, List<List<Integer>> adj) {
        int[] vis = new int[V];
        Deque<Integer> st = new ArrayDeque<>();
        for (int i = 0; i < V; i++) if (vis[i] == 0) dfsTopo(i, adj, vis, st);
        List<Integer> ans = new ArrayList<>();
        while (!st.isEmpty()) ans.add(st.pop());
        return ans;
    }
}
```

#### Approach 2: Kahn's algorithm, BFS on in-degrees (Striver's G-22)
- **Start with the sources.** A vertex with **in-degree 0** has no prerequisites, so it can go first. Put every such vertex in a queue.
- **Remove vertices one by one.** Pop a vertex and append it to the order. "Remove" its outgoing edges by decrementing each neighbour's in-degree. Any neighbour whose in-degree reaches 0 joins the queue.

**Complexity:** O(V + E) time, O(V) space.

**C++**
```cpp
vector<int> topoSort(int V, vector<vector<int>>& adj) {
    vector<int> indegree(V, 0), topo;
    for (int i = 0; i < V; i++) for (int it : adj[i]) indegree[it]++;
    queue<int> q;
    for (int i = 0; i < V; i++) if (indegree[i] == 0) q.push(i);
    while (!q.empty()) {
        int node = q.front(); q.pop();
        topo.push_back(node);
        for (int it : adj[node])
            if (--indegree[it] == 0) q.push(it);
    }
    return topo;
}
```

**Java**
```java
class Solution {
    static List<Integer> topoSort(int V, List<List<Integer>> adj) {
        int[] indegree = new int[V];
        for (int i = 0; i < V; i++) for (int it : adj.get(i)) indegree[it]++;
        Queue<Integer> q = new LinkedList<>();
        for (int i = 0; i < V; i++) if (indegree[i] == 0) q.add(i);
        List<Integer> topo = new ArrayList<>();
        while (!q.isEmpty()) {
            int node = q.remove();
            topo.add(node);
            for (int it : adj.get(node))
                if (--indegree[it] == 0) q.add(it);
        }
        return topo;
    }
}
```

#### Key Takeaways
- Topological order exists **iff** the graph is a DAG.
- DFS: push on finish, then reverse.
- Kahn: repeatedly remove in-degree-0 vertices. If fewer than V vertices come out, there is a cycle.

[↑ Contents](#contents) · [← Previous](#p352) · [Next →](#p354)

---

<a id="p354"></a>

### 14. Detect a cycle in a directed graph

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Cycles | Core | No | [LeetCode](https://leetcode.com/problems/course-schedule/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/detect-a-cycle-in-a-directed-graph) | [Watch](https://youtu.be/uzVUw90ZFIg) |

#### Problem Statement
Return `true` if a **directed** graph contains a cycle.

```text
V = 4, edges: 0->1, 1->2, 2->3, 3->1   ->  true
V = 3, edges: 0->1, 0->2, 1->2         ->  false   (two paths to 2, but no cycle)
```

#### Intuition — why the undirected check fails
In a directed graph, reaching an already visited vertex **isn't** a cycle by itself. In `0→1→2` plus `0→2`, vertex 2 is reached twice without any cycle. A cycle exists iff you reach a vertex **that is still on the current DFS path**, i.e. still on the recursion stack.

#### Approach 1: DFS with `vis` and `pathVis` (Striver's G-19)
- `pathVis[node] = 1` when entering a node, reset to 0 when leaving it (backtracking).
- If a neighbour has `pathVis == 1`, that's a back edge, so there's a cycle.

**Complexity:** O(V + E) time, O(2V) space.

**C++**
```cpp
bool dfsDirCycle(int node, vector<vector<int>>& adj, vector<int>& vis, vector<int>& pathVis) {
    vis[node] = pathVis[node] = 1;
    for (int it : adj[node]) {
        if (!vis[it]) { if (dfsDirCycle(it, adj, vis, pathVis)) return true; }
        else if (pathVis[it]) return true;            // back edge to the current path
    }
    pathVis[node] = 0;                                // leaving the path
    return false;
}
bool isCyclicDFS(int V, vector<vector<int>>& adj) {
    vector<int> vis(V, 0), pathVis(V, 0);
    for (int i = 0; i < V; i++)
        if (!vis[i] && dfsDirCycle(i, adj, vis, pathVis)) return true;
    return false;
}
```

**Java**
```java
class Solution {
    static boolean dfsDirCycle(int node, List<List<Integer>> adj, int[] vis, int[] pathVis) {
        vis[node] = pathVis[node] = 1;
        for (int it : adj.get(node)) {
            if (vis[it] == 0) { if (dfsDirCycle(it, adj, vis, pathVis)) return true; }
            else if (pathVis[it] == 1) return true;
        }
        pathVis[node] = 0;
        return false;
    }
    static boolean isCyclicDFS(int V, List<List<Integer>> adj) {
        int[] vis = new int[V], pathVis = new int[V];
        for (int i = 0; i < V; i++)
            if (vis[i] == 0 && dfsDirCycle(i, adj, vis, pathVis)) return true;
        return false;
    }
}
```

#### Approach 2: Kahn's algorithm — a cycle blocks the topological order (Striver's G-23)
Run Kahn's algorithm. Vertices on a cycle never reach in-degree 0. So if the topological order contains **fewer than V** vertices, there is a cycle.

**Complexity:** O(V + E) time, O(V) space.

**C++**
```cpp
bool isCyclic(int V, vector<vector<int>>& adj) {
    vector<int> indegree(V, 0);
    for (int i = 0; i < V; i++) for (int it : adj[i]) indegree[it]++;
    queue<int> q;
    for (int i = 0; i < V; i++) if (indegree[i] == 0) q.push(i);
    int cnt = 0;
    while (!q.empty()) {
        int node = q.front(); q.pop();
        cnt++;
        for (int it : adj[node]) if (--indegree[it] == 0) q.push(it);
    }
    return cnt != V;
}
```

**Java**
```java
class Solution {
    static boolean isCyclic(int V, List<List<Integer>> adj) {
        int[] indegree = new int[V];
        for (int i = 0; i < V; i++) for (int it : adj.get(i)) indegree[it]++;
        Queue<Integer> q = new LinkedList<>();
        for (int i = 0; i < V; i++) if (indegree[i] == 0) q.add(i);
        int cnt = 0;
        while (!q.isEmpty()) {
            int node = q.remove();
            cnt++;
            for (int it : adj.get(node)) if (--indegree[it] == 0) q.add(it);
        }
        return cnt != V;
    }
}
```

#### Key Takeaways
- Directed cycle detection has two forms: DFS with an on-path marker, or Kahn's algorithm, where an incomplete topological order means a cycle.

[↑ Contents](#contents) · [← Previous](#p353) · [Next →](#p355)

---

## Hard Problems

<a id="p355"></a>

### 15. Find eventual safe states

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Hard Problems | Pro | No | [LeetCode](https://leetcode.com/problems/find-eventual-safe-states/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/find-eventual-safe-states) | [Watch](https://youtu.be/2gtg3VsDGyc) |

#### Problem Statement
A node is **terminal** if it has no outgoing edges. A node is **safe** if every path starting from it leads to a terminal node, i.e. it can't reach a cycle. Return all safe nodes in **sorted** order.

```text
graph = [[1,2],[2,3],[5],[0],[5],[],[]]   ->  [2, 4, 5, 6]
```

#### Approach 1: DFS cycle detection (Striver's G-20)
- **Reuse the directed-cycle DFS.** Any node that is **on a cycle or can reach one** is unsafe.
- **When the DFS finishes a node without finding a cycle,** mark it `check = 1` (safe).
- **When a cycle is found,** return immediately **without** unmarking `pathVis`. Every node on that path stays marked as "on a path" and is never marked safe.

**Complexity:** O(V + E) time, O(3V) space.

**C++**
```cpp
bool dfsSafe(int node, vector<vector<int>>& adj, vector<int>& vis, vector<int>& pathVis, vector<int>& check) {
    vis[node] = pathVis[node] = 1;
    check[node] = 0;
    for (int it : adj[node]) {
        if (!vis[it]) { if (dfsSafe(it, adj, vis, pathVis, check)) return true; }
        else if (pathVis[it]) return true;                 // cycle: leave pathVis marked
    }
    check[node] = 1;                                       // no cycle reachable: safe
    pathVis[node] = 0;
    return false;
}
vector<int> eventualSafeNodesDFS(vector<vector<int>>& graph) {
    int V = graph.size();
    vector<int> vis(V, 0), pathVis(V, 0), check(V, 0), safe;
    for (int i = 0; i < V; i++) if (!vis[i]) dfsSafe(i, graph, vis, pathVis, check);
    for (int i = 0; i < V; i++) if (check[i]) safe.push_back(i);
    return safe;
}
```

**Java**
```java
class Solution {
    static boolean dfsSafe(int node, int[][] adj, int[] vis, int[] pathVis, int[] check) {
        vis[node] = pathVis[node] = 1;
        check[node] = 0;
        for (int it : adj[node]) {
            if (vis[it] == 0) { if (dfsSafe(it, adj, vis, pathVis, check)) return true; }
            else if (pathVis[it] == 1) return true;
        }
        check[node] = 1;
        pathVis[node] = 0;
        return false;
    }
    static List<Integer> eventualSafeNodesDFS(int[][] graph) {
        int V = graph.length;
        int[] vis = new int[V], pathVis = new int[V], check = new int[V];
        for (int i = 0; i < V; i++) if (vis[i] == 0) dfsSafe(i, graph, vis, pathVis, check);
        List<Integer> safe = new ArrayList<>();
        for (int i = 0; i < V; i++) if (check[i] == 1) safe.add(i);
        return safe;
    }
}
```

#### Approach 2: Reverse the edges + Kahn's algorithm (as in the video, G-25)
- **Terminal nodes are safe.** A node is safe if **all** of its outgoing edges lead to safe nodes.
- **Reverse every edge.** Terminal nodes now have **in-degree 0**. Run Kahn's algorithm on the reversed graph; each in-degree there is the node's original out-degree.
- **Whatever comes out is safe.** A node reaches in-degree 0 exactly when all of its original successors are known safe. Sort the result.

**Complexity:** O(V + E) time, plus O(V log V) for the sort. O(V + E) space.

**C++**
```cpp
vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
    int V = graph.size();
    vector<vector<int>> rev(V);
    vector<int> indegree(V, 0), safe;
    for (int i = 0; i < V; i++)
        for (int it : graph[i]) { rev[it].push_back(i); indegree[i]++; }   // reversed edge it -> i
    queue<int> q;
    for (int i = 0; i < V; i++) if (indegree[i] == 0) q.push(i);           // terminal nodes
    while (!q.empty()) {
        int node = q.front(); q.pop();
        safe.push_back(node);
        for (int it : rev[node]) if (--indegree[it] == 0) q.push(it);
    }
    sort(safe.begin(), safe.end());
    return safe;
}
```

**Java**
```java
class Solution {
    static List<Integer> eventualSafeNodes(int[][] graph) {
        int V = graph.length;
        List<List<Integer>> rev = new ArrayList<>();
        for (int i = 0; i < V; i++) rev.add(new ArrayList<>());
        int[] indegree = new int[V];
        for (int i = 0; i < V; i++)
            for (int it : graph[i]) { rev.get(it).add(i); indegree[i]++; }
        Queue<Integer> q = new LinkedList<>();
        for (int i = 0; i < V; i++) if (indegree[i] == 0) q.add(i);
        List<Integer> safe = new ArrayList<>();
        while (!q.isEmpty()) {
            int node = q.remove();
            safe.add(node);
            for (int it : rev.get(node)) if (--indegree[it] == 0) q.add(it);
        }
        Collections.sort(safe);
        return safe;
    }
}
```

#### Key Takeaways
- Safe nodes = the nodes that can't reach a cycle. Use either directed-cycle DFS with a "safe" mark, or topological peeling from the terminal nodes on the reversed graph.

[↑ Contents](#contents) · [← Previous](#p354) · [Next →](#p356)

---

<a id="p356"></a>

### 16. Course Schedule I

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Hard Problems | Pro | No | [LeetCode](https://leetcode.com/problems/course-schedule/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/course-schedule-i) | [Watch](https://youtu.be/WAOfKpxYHR8) |

#### Problem Statement
There are `numCourses` courses. `prerequisites[i] = [a, b]` means you must take `b` before `a`. Return `true` if you can finish all the courses.

```text
numCourses = 2, prerequisites = [[1,0]]          ->  true
numCourses = 2, prerequisites = [[1,0],[0,1]]    ->  false   (circular dependency)
```

#### Intuition
Build a directed graph with an edge `b → a`. All courses can be finished **iff the graph has no cycle**, i.e. a topological order of all `numCourses` vertices exists.

#### Approach: Kahn's algorithm (as in the video)
Run Kahn's algorithm and count the vertices removed. You can finish iff `count == numCourses`.

**Complexity:** O(V + E) time, O(V + E) space.

**C++**
```cpp
bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> adj(numCourses);
    vector<int> indegree(numCourses, 0);
    for (auto& p : prerequisites) { adj[p[1]].push_back(p[0]); indegree[p[0]]++; }
    queue<int> q;
    for (int i = 0; i < numCourses; i++) if (indegree[i] == 0) q.push(i);
    int taken = 0;
    while (!q.empty()) {
        int node = q.front(); q.pop();
        taken++;
        for (int it : adj[node]) if (--indegree[it] == 0) q.push(it);
    }
    return taken == numCourses;
}
```

**Java**
```java
class Solution {
    static boolean canFinish(int numCourses, int[][] prerequisites) {
        List<List<Integer>> adj = new ArrayList<>();
        for (int i = 0; i < numCourses; i++) adj.add(new ArrayList<>());
        int[] indegree = new int[numCourses];
        for (int[] p : prerequisites) { adj.get(p[1]).add(p[0]); indegree[p[0]]++; }
        Queue<Integer> q = new LinkedList<>();
        for (int i = 0; i < numCourses; i++) if (indegree[i] == 0) q.add(i);
        int taken = 0;
        while (!q.isEmpty()) {
            int node = q.remove();
            taken++;
            for (int it : adj.get(node)) if (--indegree[it] == 0) q.add(it);
        }
        return taken == numCourses;
    }
}
```

#### Key Takeaways
- Prerequisite scheduling is the same as checking whether a topological order exists (no directed cycle).

[↑ Contents](#contents) · [← Previous](#p355) · [Next →](#p357)

---

<a id="p357"></a>

### 17. Course Schedule II

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Hard Problems | Pro | No | [LeetCode](https://leetcode.com/problems/course-schedule-ii/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/course-schedule-ii) | [Watch](https://youtu.be/WAOfKpxYHR8) |

#### Problem Statement
Same setup as Course Schedule I, but return **an order** in which to take all the courses, or an empty array if that's impossible.

```text
numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]   ->  [0, 1, 2, 3]  (or [0, 2, 1, 3])
```

#### Approach: Kahn's algorithm, returning the order (as in the video)
**Complexity:** O(V + E) time, O(V + E) space.

**C++**
```cpp
vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> adj(numCourses);
    vector<int> indegree(numCourses, 0), order;
    for (auto& p : prerequisites) { adj[p[1]].push_back(p[0]); indegree[p[0]]++; }
    queue<int> q;
    for (int i = 0; i < numCourses; i++) if (indegree[i] == 0) q.push(i);
    while (!q.empty()) {
        int node = q.front(); q.pop();
        order.push_back(node);
        for (int it : adj[node]) if (--indegree[it] == 0) q.push(it);
    }
    if ((int)order.size() != numCourses) return {};       // cycle: impossible
    return order;
}
```

**Java**
```java
class Solution {
    static int[] findOrder(int numCourses, int[][] prerequisites) {
        List<List<Integer>> adj = new ArrayList<>();
        for (int i = 0; i < numCourses; i++) adj.add(new ArrayList<>());
        int[] indegree = new int[numCourses];
        for (int[] p : prerequisites) { adj.get(p[1]).add(p[0]); indegree[p[0]]++; }
        Queue<Integer> q = new LinkedList<>();
        for (int i = 0; i < numCourses; i++) if (indegree[i] == 0) q.add(i);
        int[] order = new int[numCourses];
        int idx = 0;
        while (!q.isEmpty()) {
            int node = q.remove();
            order[idx++] = node;
            for (int it : adj.get(node)) if (--indegree[it] == 0) q.add(it);
        }
        return idx == numCourses ? order : new int[0];
    }
}
```

#### Key Takeaways
- Course Schedule II is the topological order itself, or empty if there is a cycle.

[↑ Contents](#contents) · [← Previous](#p356) · [Next →](#p358)

---

<a id="p358"></a>

### 18. Alien Dictionary

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Hard Problems | Pro | Yes | [LeetCode](https://leetcode.com/problems/alien-dictionary/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/alien-dictionary) | [Watch](https://youtu.be/U3N_je7tWAs) |

#### Problem Statement
You're given words sorted **lexicographically** in an unknown alien alphabet of the first `K` lowercase letters. Return **an** ordering of those letters consistent with the dictionary. GfG also guarantees the dictionary is valid; LeetCode 269 returns `""` if it isn't.

```text
words = ["baa","abcd","abca","cab","cad"], K = 4   ->  "bdac"
words = ["caa","aaa","aab"], K = 3                 ->  "cab"
```

#### Intuition — adjacent words give ordering constraints
- **Compare neighbours.** For each pair of **adjacent** words, the **first position where they differ** tells you `word1[i]` comes before `word2[i]` in the alphabet. That's a directed edge.
- **Read off the order.** A topological sort of the letters is then a valid alphabet.
- **Invalid input.** If `word1` is longer and `word2` is a **prefix** of it (e.g. `"abc"` before `"ab"`), no alphabet works. Likewise, a cycle among the letters means no order exists.

#### Approach: Build the edges from adjacent pairs + Kahn's algorithm (as in the video)
**Complexity:**
- Time: O(N · L) to build the edges for N words of length L, plus O(K + E) for the topological sort.
- Space: O(K + E).

**C++**
```cpp
string findOrderAlien(vector<string>& dict, int K) {
    vector<vector<int>> adj(K);
    for (size_t i = 0; i + 1 < dict.size(); i++) {
        const string &s1 = dict[i], &s2 = dict[i + 1];
        size_t len = min(s1.size(), s2.size()), p = 0;
        while (p < len && s1[p] == s2[p]) p++;
        if (p < len) adj[s1[p] - 'a'].push_back(s2[p] - 'a');   // s1[p] before s2[p]
        else if (s1.size() > s2.size()) return "";             // prefix violation: invalid
    }
    vector<int> indegree(K, 0);
    for (int u = 0; u < K; u++) for (int v : adj[u]) indegree[v]++;
    queue<int> q;
    for (int i = 0; i < K; i++) if (indegree[i] == 0) q.push(i);
    string order;
    while (!q.empty()) {
        int node = q.front(); q.pop();
        order += char('a' + node);
        for (int it : adj[node]) if (--indegree[it] == 0) q.push(it);
    }
    return (int)order.size() == K ? order : "";             // cycle -> invalid
}
```

**Java**
```java
class Solution {
    static String findOrderAlien(String[] dict, int K) {
        List<List<Integer>> adj = new ArrayList<>();
        for (int i = 0; i < K; i++) adj.add(new ArrayList<>());
        for (int i = 0; i + 1 < dict.length; i++) {
            String s1 = dict[i], s2 = dict[i + 1];
            int len = Math.min(s1.length(), s2.length()), p = 0;
            while (p < len && s1.charAt(p) == s2.charAt(p)) p++;
            if (p < len) adj.get(s1.charAt(p) - 'a').add(s2.charAt(p) - 'a');
            else if (s1.length() > s2.length()) return "";
        }
        int[] indegree = new int[K];
        for (int u = 0; u < K; u++) for (int v : adj.get(u)) indegree[v]++;
        Queue<Integer> q = new LinkedList<>();
        for (int i = 0; i < K; i++) if (indegree[i] == 0) q.add(i);
        StringBuilder order = new StringBuilder();
        while (!q.isEmpty()) {
            int node = q.remove();
            order.append((char) ('a' + node));
            for (int it : adj.get(node)) if (--indegree[it] == 0) q.add(it);
        }
        return order.length() == K ? order.toString() : "";
    }
}
```

#### Edge Cases & Pitfalls
- **Compare only adjacent words.** Constraints from non-adjacent pairs are implied by transitivity.
- **Only the first difference** in each pair matters. Later characters carry no information.

#### Key Takeaways
- Ordering from comparisons means a DAG plus a topological sort. "Find any consistent order" is the classic topological-sort word problem.

[↑ Contents](#contents) · [← Previous](#p357) · [Next →](#p359)

---

<a id="p359"></a>

### 19. Shortest path in DAG

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Hard Problems | Core | Yes | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/shortest-path-in-a-directed-acyclic-graph-dag) | [Watch](https://youtu.be/ZUFQfFaU-8U) |

#### Problem Statement
Given a weighted **DAG** with `N` vertices and edges `[u, v, wt]`, return the shortest distance from source `0` to every vertex, using −1 for unreachable vertices.

```text
N = 6, edges = [[0,1,2],[0,4,1],[4,5,4],[4,2,2],[1,2,3],[2,3,6],[5,3,1]]
->  [0, 2, 3, 6, 1, 5]
```

#### Intuition — relax the edges in topological order (as in the video, G-27)
- **Process vertices in topological order.** When you reach vertex `u`, every edge **into** `u` has already been relaxed, because all of its predecessors came earlier. So `dist[u]` is already final.
- **Relax outgoing edges.** Then `dist[v] = min(dist[v], dist[u] + wt)` for each edge `u → v`.
- **Why it's fast.** Each edge is relaxed exactly once, with no priority queue. Negative weights are fine too.

#### Approach: Topological sort (DFS) + one relaxation pass
**Complexity:** O(N + M) time, O(N + M) space.

**C++**
```cpp
void topoDFS(int node, vector<vector<pair<int, int>>>& adj, vector<int>& vis, stack<int>& st) {
    vis[node] = 1;
    for (auto& [v, w] : adj[node]) if (!vis[v]) topoDFS(v, adj, vis, st);
    st.push(node);
}
vector<int> shortestPathDAG(int N, int M, vector<vector<int>>& edges) {
    vector<vector<pair<int, int>>> adj(N);
    for (auto& e : edges) adj[e[0]].push_back({e[1], e[2]});
    vector<int> vis(N, 0);
    stack<int> st;
    for (int i = 0; i < N; i++) if (!vis[i]) topoDFS(i, adj, vis, st);
    vector<int> dist(N, INT_MAX);
    dist[0] = 0;
    while (!st.empty()) {
        int u = st.top(); st.pop();
        if (dist[u] == INT_MAX) continue;                 // unreachable so far
        for (auto& [v, w] : adj[u])
            if (dist[u] + w < dist[v]) dist[v] = dist[u] + w;
    }
    for (int& d : dist) if (d == INT_MAX) d = -1;
    return dist;
}
```

**Java**
```java
class Solution {
    static void topoDFS(int node, List<List<int[]>> adj, int[] vis, Deque<Integer> st) {
        vis[node] = 1;
        for (int[] e : adj.get(node)) if (vis[e[0]] == 0) topoDFS(e[0], adj, vis, st);
        st.push(node);
    }
    static int[] shortestPathDAG(int N, int M, int[][] edges) {
        List<List<int[]>> adj = new ArrayList<>();
        for (int i = 0; i < N; i++) adj.add(new ArrayList<>());
        for (int[] e : edges) adj.get(e[0]).add(new int[]{e[1], e[2]});
        int[] vis = new int[N];
        Deque<Integer> st = new ArrayDeque<>();
        for (int i = 0; i < N; i++) if (vis[i] == 0) topoDFS(i, adj, vis, st);
        int[] dist = new int[N];
        Arrays.fill(dist, Integer.MAX_VALUE);
        dist[0] = 0;
        while (!st.isEmpty()) {
            int u = st.pop();
            if (dist[u] == Integer.MAX_VALUE) continue;
            for (int[] e : adj.get(u))
                if (dist[u] + e[1] < dist[e[0]]) dist[e[0]] = dist[u] + e[1];
        }
        for (int i = 0; i < N; i++) if (dist[i] == Integer.MAX_VALUE) dist[i] = -1;
        return dist;
    }
}
```

#### Key Takeaways
- On a DAG, shortest (and longest) paths take one topological pass, O(V + E), with no Dijkstra needed.

[↑ Contents](#contents) · [← Previous](#p358) · [Next →](#p360)

---

<a id="p360"></a>

### 20. Shortest path in undirected graph with unit weights

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Hard Problems | Core | Yes | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/shortest-path-in-an-unweighted-undirected-graph-using-bfs) | [Watch](https://youtu.be/C4gxoTaI71U) |

#### Problem Statement
Given an undirected graph with **unit edge weights**, return the shortest distance from `src` to every vertex, using −1 for unreachable vertices.

```text
N = 9, edges: 0-1, 0-3, 3-4, 4-5, 5-6, 1-2, 2-6, 6-7, 7-8, 6-8, src = 0
->  [0, 1, 2, 1, 2, 3, 3, 4, 4]
```

#### Approach: Plain BFS (as in the video, G-28)
- **Why BFS works here.** With every edge weighing 1, BFS discovers vertices in non-decreasing order of distance. The first time a vertex is reached is its shortest distance.
- **The update.** Relax with `dist[v] = dist[u] + 1` when that's an improvement, and push `v`.

**Complexity:** O(V + 2E) time, O(V) space.

**C++**
```cpp
vector<int> shortestPathUnit(vector<vector<int>>& edges, int N, int src) {
    vector<vector<int>> adj(N);
    for (auto& e : edges) { adj[e[0]].push_back(e[1]); adj[e[1]].push_back(e[0]); }
    vector<int> dist(N, INT_MAX);
    queue<int> q;
    dist[src] = 0;
    q.push(src);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u])
            if (dist[u] + 1 < dist[v]) { dist[v] = dist[u] + 1; q.push(v); }
    }
    for (int& d : dist) if (d == INT_MAX) d = -1;
    return dist;
}
```

**Java**
```java
class Solution {
    static int[] shortestPathUnit(int[][] edges, int N, int src) {
        List<List<Integer>> adj = new ArrayList<>();
        for (int i = 0; i < N; i++) adj.add(new ArrayList<>());
        for (int[] e : edges) { adj.get(e[0]).add(e[1]); adj.get(e[1]).add(e[0]); }
        int[] dist = new int[N];
        Arrays.fill(dist, Integer.MAX_VALUE);
        Queue<Integer> q = new LinkedList<>();
        dist[src] = 0;
        q.add(src);
        while (!q.isEmpty()) {
            int u = q.remove();
            for (int v : adj.get(u))
                if (dist[u] + 1 < dist[v]) { dist[v] = dist[u] + 1; q.add(v); }
        }
        for (int i = 0; i < N; i++) if (dist[i] == Integer.MAX_VALUE) dist[i] = -1;
        return dist;
    }
}
```

#### Key Takeaways
- Unit weights mean BFS gives shortest paths. With 0/1 weights, use a deque (0-1 BFS); with general non-negative weights, use Dijkstra.

[↑ Contents](#contents) · [← Previous](#p359) · [Next →](#p361)

---

<a id="p361"></a>

### 21. Word ladder I

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Hard Problems | Pro | No | [LeetCode](https://leetcode.com/problems/word-ladder/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/word-ladder) | [Watch](https://youtu.be/tRPda0rcf8E) |

#### Problem Statement
Given `beginWord`, `endWord` and a `wordList`, return the number of words in the **shortest transformation sequence** from `beginWord` to `endWord`. Each step changes **one letter**, and every intermediate word must be in `wordList`. Return 0 if no sequence exists.

```text
begin = "hit", end = "cog", list = ["hot","dot","dog","lot","log","cog"]   ->  5   (hit hot dot dog cog)
begin = "hit", end = "cog", list = ["hot","dot","dog","lot","log"]         ->  0
```

#### Intuition — BFS over words
- **Words are vertices.** Two words are adjacent if they differ in exactly one letter. The answer is a shortest path in an unweighted graph, so use BFS.
- **Generate neighbours on the fly.** For each position, try all 26 letters and check membership in a **set**. Remove a word from the set the moment it's queued, which acts as "visited". Any later path to it would be at least as long.

#### Approach: BFS with a word set (as in the video, G-29)
**Complexity:**
- Time: O(N · L · 26 · log N) with an ordered set; drop the log with a hash set.
- Space: O(N · L).

**C++**
```cpp
int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    unordered_set<string> st(wordList.begin(), wordList.end());
    queue<pair<string, int>> q;
    q.push({beginWord, 1});
    st.erase(beginWord);
    while (!q.empty()) {
        auto [word, steps] = q.front(); q.pop();
        if (word == endWord) return steps;
        for (size_t i = 0; i < word.size(); i++) {
            char orig = word[i];
            for (char ch = 'a'; ch <= 'z'; ch++) {
                word[i] = ch;
                if (st.count(word)) { st.erase(word); q.push({word, steps + 1}); }
            }
            word[i] = orig;
        }
    }
    return 0;
}
```

**Java**
```java
class Solution {
    static int ladderLength(String beginWord, String endWord, List<String> wordList) {
        Set<String> st = new HashSet<>(wordList);
        Queue<Object[]> q = new LinkedList<>();
        q.add(new Object[]{beginWord, 1});
        st.remove(beginWord);
        while (!q.isEmpty()) {
            Object[] cur = q.remove();
            String word = (String) cur[0];
            int steps = (Integer) cur[1];
            if (word.equals(endWord)) return steps;
            char[] arr = word.toCharArray();
            for (int i = 0; i < arr.length; i++) {
                char orig = arr[i];
                for (char ch = 'a'; ch <= 'z'; ch++) {
                    arr[i] = ch;
                    String nw = new String(arr);
                    if (st.contains(nw)) { st.remove(nw); q.add(new Object[]{nw, steps + 1}); }
                }
                arr[i] = orig;
            }
        }
        return 0;
    }
}
```

#### Key Takeaways
- An implicit graph plus BFS. Deleting from the set on enqueue doubles as the visited marker.

[↑ Contents](#contents) · [← Previous](#p360) · [Next →](#p362)

---

<a id="p362"></a>

### 22. Word ladder II

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Hard Problems | Pro | No | [LeetCode](https://leetcode.com/problems/word-ladder-ii/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/word-ladder-ii) | [Watch](https://youtu.be/AD4SFl7tu7I) |

#### Problem Statement
Same as Word Ladder I, but return **all** shortest transformation sequences.

```text
begin = "hit", end = "cog", list = ["hot","dot","dog","lot","log","cog"]
->  [["hit","hot","dot","dog","cog"], ["hit","hot","lot","log","cog"]]
```

#### Approach 1: BFS over whole sequences (Striver's G-30, the interview version)
- **The queue stores entire sequences.** At each BFS **level**, extend every sequence by one valid word.
- **Erase a level at once.** Words used on a level are erased from the set only **after the whole level** has been processed. Two sequences of the same length may legitimately share a word on that level.
- **Stop at the first level that reaches `endWord`.** Every sequence there is a shortest one.

**Complexity:** this can blow up exponentially in the number of sequences. It's fine for interviews, but it gets TLE on LeetCode.

**C++**
```cpp
vector<vector<string>> findSequencesBFS(string beginWord, string endWord, vector<string>& wordList) {
    unordered_set<string> st(wordList.begin(), wordList.end());
    queue<vector<string>> q;
    q.push({beginWord});
    vector<string> usedOnLevel = {beginWord};
    int level = 0;
    vector<vector<string>> ans;
    while (!q.empty()) {
        vector<string> vec = q.front(); q.pop();
        if ((int)vec.size() > level) {                   // a new level begins
            level++;
            for (auto& w : usedOnLevel) st.erase(w);
            usedOnLevel.clear();
        }
        string word = vec.back();
        if (word == endWord) {
            if (ans.empty() || ans[0].size() == vec.size()) ans.push_back(vec);
            continue;
        }
        for (size_t i = 0; i < word.size(); i++) {
            char orig = word[i];
            for (char c = 'a'; c <= 'z'; c++) {
                word[i] = c;
                if (st.count(word)) {
                    vec.push_back(word);
                    q.push(vec);
                    usedOnLevel.push_back(word);
                    vec.pop_back();
                }
            }
            word[i] = orig;
        }
    }
    return ans;
}
```

**Java**
```java
class Solution {
    static List<List<String>> findSequencesBFS(String beginWord, String endWord, List<String> wordList) {
        Set<String> st = new HashSet<>(wordList);
        Queue<List<String>> q = new LinkedList<>();
        q.add(new ArrayList<>(List.of(beginWord)));
        List<String> usedOnLevel = new ArrayList<>(List.of(beginWord));
        int level = 0;
        List<List<String>> ans = new ArrayList<>();
        while (!q.isEmpty()) {
            List<String> vec = q.remove();
            if (vec.size() > level) {
                level++;
                for (String w : usedOnLevel) st.remove(w);
                usedOnLevel.clear();
            }
            String word = vec.get(vec.size() - 1);
            if (word.equals(endWord)) {
                if (ans.isEmpty() || ans.get(0).size() == vec.size()) ans.add(vec);
                continue;
            }
            char[] arr = word.toCharArray();
            for (int i = 0; i < arr.length; i++) {
                char orig = arr[i];
                for (char c = 'a'; c <= 'z'; c++) {
                    arr[i] = c;
                    String nw = new String(arr);
                    if (st.contains(nw)) {
                        List<String> next = new ArrayList<>(vec);
                        next.add(nw);
                        q.add(next);
                        usedOnLevel.add(nw);
                    }
                }
                arr[i] = orig;
            }
        }
        return ans;
    }
}
```

#### Approach 2: Optimal — BFS for levels, then backtrack from `endWord` (as in the video, G-31)
The video calls this the "CP way". It's needed to pass LeetCode's strict limits.
1. **BFS from `beginWord`** storing only `level[word]`, the distance of each word. Erase words from the set when they're queued, as in Word Ladder I.
2. **DFS backwards** from `endWord`. Move to a neighbour `w` only if `level[w] == level[cur] − 1`, so every step goes one level closer to the start. When `beginWord` is reached, the reversed path is one answer.

Only edges on shortest paths are explored, so the search never wanders off into longer branches.

**Complexity:** O(N · L · 26) for the BFS, plus the size of the output for the backtracking.

**C++**
```cpp
void backtrackLadder(const string& word, const string& beginWord, unordered_map<string, int>& lvl,
                     vector<string>& seq, vector<vector<string>>& ans) {
    if (word == beginWord) {
        ans.push_back(vector<string>(seq.rbegin(), seq.rend()));
        return;
    }
    int steps = lvl[word];
    string w = word;
    for (size_t i = 0; i < w.size(); i++) {
        char orig = w[i];
        for (char c = 'a'; c <= 'z'; c++) {
            w[i] = c;
            auto it = lvl.find(w);
            if (it != lvl.end() && it->second + 1 == steps) {   // one level closer to begin
                seq.push_back(w);
                backtrackLadder(w, beginWord, lvl, seq, ans);
                seq.pop_back();
            }
        }
        w[i] = orig;
    }
}
vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
    unordered_set<string> st(wordList.begin(), wordList.end());
    unordered_map<string, int> lvl;
    queue<string> q;
    q.push(beginWord);
    lvl[beginWord] = 1;
    st.erase(beginWord);
    while (!q.empty()) {
        string word = q.front(); q.pop();
        int steps = lvl[word];
        if (word == endWord) break;
        for (size_t i = 0; i < word.size(); i++) {
            char orig = word[i];
            for (char c = 'a'; c <= 'z'; c++) {
                word[i] = c;
                if (st.count(word)) { q.push(word); st.erase(word); lvl[word] = steps + 1; }
            }
            word[i] = orig;
        }
    }
    vector<vector<string>> ans;
    if (lvl.count(endWord)) {
        vector<string> seq = {endWord};
        backtrackLadder(endWord, beginWord, lvl, seq, ans);
    }
    return ans;
}
```

**Java**
```java
class Solution {
    static void backtrackLadder(String word, String beginWord, Map<String, Integer> lvl,
                                List<String> seq, List<List<String>> ans) {
        if (word.equals(beginWord)) {
            List<String> path = new ArrayList<>(seq);
            Collections.reverse(path);
            ans.add(path);
            return;
        }
        int steps = lvl.get(word);
        char[] arr = word.toCharArray();
        for (int i = 0; i < arr.length; i++) {
            char orig = arr[i];
            for (char c = 'a'; c <= 'z'; c++) {
                arr[i] = c;
                String w = new String(arr);
                Integer l = lvl.get(w);
                if (l != null && l + 1 == steps) {
                    seq.add(w);
                    backtrackLadder(w, beginWord, lvl, seq, ans);
                    seq.remove(seq.size() - 1);
                }
            }
            arr[i] = orig;
        }
    }
    static List<List<String>> findLadders(String beginWord, String endWord, List<String> wordList) {
        Set<String> st = new HashSet<>(wordList);
        Map<String, Integer> lvl = new HashMap<>();
        Queue<String> q = new LinkedList<>();
        q.add(beginWord);
        lvl.put(beginWord, 1);
        st.remove(beginWord);
        while (!q.isEmpty()) {
            String word = q.remove();
            int steps = lvl.get(word);
            if (word.equals(endWord)) break;
            char[] arr = word.toCharArray();
            for (int i = 0; i < arr.length; i++) {
                char orig = arr[i];
                for (char c = 'a'; c <= 'z'; c++) {
                    arr[i] = c;
                    String nw = new String(arr);
                    if (st.contains(nw)) { q.add(nw); st.remove(nw); lvl.put(nw, steps + 1); }
                }
                arr[i] = orig;
            }
        }
        List<List<String>> ans = new ArrayList<>();
        if (lvl.containsKey(endWord)) {
            List<String> seq = new ArrayList<>(List.of(endWord));
            backtrackLadder(endWord, beginWord, lvl, seq, ans);
        }
        return ans;
    }
}
```

#### Key Takeaways
- To enumerate **all** shortest paths: BFS to compute distances, then DFS backwards along edges that decrease the distance by exactly 1.

[↑ Contents](#contents) · [← Previous](#p361) · [Next →](#p363)

---

## Shortest Path Algorithms

<a id="p363"></a>

### 23. Dijkstra's algorithm

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Shortest Path Algorithms | Core | Yes | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/dijkstras-algorithm) | [Watch](https://youtu.be/V6H1qAeB-l4) |

#### Problem Statement
Given a weighted graph with **non-negative** edge weights and a source `S`, return the shortest distance from `S` to every vertex.

```text
V = 3, adj: 0-1 (1), 0-2 (6), 1-2 (3), S = 2   ->  [4, 3, 0]
```

#### Intuition
- **Greedy.** Repeatedly take the **unfinalised vertex with the smallest tentative distance**. With non-negative weights, no later path can make it any shorter.
- **Relax.** Update its neighbours: `dist[v] = min(dist[v], dist[u] + w)`.

#### Approach 1: Priority queue / min-heap (as in the video, G-32)
- Push `{0, S}`.
- Pop `{d, u}`. If `d > dist[u]`, it's a **stale** entry: skip it.
- Relax each edge, pushing `{dist[v], v}` whenever `dist[v]` improves.

**Complexity:** O(E log V) time, O(V + E) space. Striver's G-34 derives the bound.

**C++**
```cpp
vector<int> dijkstra(int V, vector<vector<pair<int, int>>>& adj, int S) {   // adj[u] = {v, w}
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;     // {dist, node}
    vector<int> dist(V, INT_MAX);
    dist[S] = 0;
    pq.push({0, S});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;                       // stale entry
        for (auto& [v, w] : adj[u])
            if (d + w < dist[v]) { dist[v] = d + w; pq.push({dist[v], v}); }
    }
    return dist;
}
```

**Java**
```java
class Solution {
    static int[] dijkstra(int V, List<List<int[]>> adj, int S) {     // adj[u] = {v, w}
        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> Integer.compare(a[0], b[0]));
        int[] dist = new int[V];
        Arrays.fill(dist, Integer.MAX_VALUE);
        dist[S] = 0;
        pq.add(new int[]{0, S});
        while (!pq.isEmpty()) {
            int[] top = pq.poll();
            int d = top[0], u = top[1];
            if (d > dist[u]) continue;
            for (int[] e : adj.get(u))
                if (d + e[1] < dist[e[0]]) { dist[e[0]] = d + e[1]; pq.add(new int[]{dist[e[0]], e[0]}); }
        }
        return dist;
    }
}
```

#### Approach 2: Using a set (Striver's G-33)
A `set<{dist, node}>` lets you **erase** an outdated entry when a shorter distance is found, so the container never holds stale entries.

**Complexity:** O(E log V) time. Erasing costs log V, but it can save pushes.

**C++**
```cpp
vector<int> dijkstraSet(int V, vector<vector<pair<int, int>>>& adj, int S) {
    set<pair<int, int>> st;
    vector<int> dist(V, INT_MAX);
    dist[S] = 0;
    st.insert({0, S});
    while (!st.empty()) {
        auto [d, u] = *st.begin();
        st.erase(st.begin());
        for (auto& [v, w] : adj[u]) {
            if (d + w < dist[v]) {
                if (dist[v] != INT_MAX) st.erase({dist[v], v});   // remove the outdated entry
                dist[v] = d + w;
                st.insert({dist[v], v});
            }
        }
    }
    return dist;
}
```

**Java**
```java
class Solution {
    static int[] dijkstraSet(int V, List<List<int[]>> adj, int S) {
        TreeSet<int[]> st = new TreeSet<>((a, b) -> a[0] != b[0] ? Integer.compare(a[0], b[0]) : Integer.compare(a[1], b[1]));
        int[] dist = new int[V];
        Arrays.fill(dist, Integer.MAX_VALUE);
        dist[S] = 0;
        st.add(new int[]{0, S});
        while (!st.isEmpty()) {
            int[] top = st.pollFirst();
            int d = top[0], u = top[1];
            for (int[] e : adj.get(u)) {
                int v = e[0], w = e[1];
                if (d + w < dist[v]) {
                    if (dist[v] != Integer.MAX_VALUE) st.remove(new int[]{dist[v], v});
                    dist[v] = d + w;
                    st.add(new int[]{dist[v], v});
                }
            }
        }
        return dist;
    }
}
```

#### Edge Cases & Pitfalls
- **Negative weights break Dijkstra.** A finalised vertex could later improve. Use Bellman-Ford instead.
- **Why a priority queue and not a plain queue?** A plain queue still gives correct answers, but it may re-process vertices many times. The priority queue processes each vertex in distance order (G-34).

#### Key Takeaways
- Dijkstra is greedy extraction of the minimum tentative distance plus edge relaxation, O(E log V) with a heap.

[↑ Contents](#contents) · [← Previous](#p362) · [Next →](#p364)

---

<a id="p364"></a>

### 24. Print Shortest Path

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Shortest Path Algorithms | Core | Yes | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/print-shortest-path) | [Watch](https://youtu.be/rp1SMw7HSO8) |

#### Problem Statement
For a weighted undirected graph with vertices `1 … n`, return the **shortest path** from `1` to `n` as a list of vertices, or `[-1]` if `n` is unreachable. GfG's variant prepends the path's total weight to the list.

```text
n = 5, edges = [[1,2,2],[2,5,5],[2,3,4],[1,4,1],[4,3,3],[3,5,1]]   ->  [1, 4, 3, 5]   (weight 5)
```

#### Approach: Dijkstra with a `parent` array (as in the video, G-35)
- **Record where each improvement came from.** While relaxing, whenever `dist[v]` improves via `u`, set `parent[v] = u`.
- **Rebuild the path.** Walk from `n` back through `parent` until `parent[x] == x` (the source), then reverse.

**Complexity:** O(E log V) for Dijkstra, plus O(V) to rebuild. O(V + E) space.

**C++**
```cpp
vector<int> shortestPath(int n, int m, vector<vector<int>>& edges) {
    vector<vector<pair<int, int>>> adj(n + 1);
    for (auto& e : edges) { adj[e[0]].push_back({e[1], e[2]}); adj[e[1]].push_back({e[0], e[2]}); }
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    vector<int> dist(n + 1, INT_MAX), parent(n + 1);
    iota(parent.begin(), parent.end(), 0);
    dist[1] = 0;
    pq.push({0, 1});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto& [v, w] : adj[u])
            if (d + w < dist[v]) { dist[v] = d + w; parent[v] = u; pq.push({dist[v], v}); }
    }
    if (dist[n] == INT_MAX) return {-1};
    vector<int> path;
    for (int x = n; parent[x] != x; x = parent[x]) path.push_back(x);
    path.push_back(1);
    reverse(path.begin(), path.end());
    return path;
}
```

**Java**
```java
class Solution {
    static List<Integer> shortestPath(int n, int m, int[][] edges) {
        List<List<int[]>> adj = new ArrayList<>();
        for (int i = 0; i <= n; i++) adj.add(new ArrayList<>());
        for (int[] e : edges) { adj.get(e[0]).add(new int[]{e[1], e[2]}); adj.get(e[1]).add(new int[]{e[0], e[2]}); }
        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> Integer.compare(a[0], b[0]));
        int[] dist = new int[n + 1], parent = new int[n + 1];
        Arrays.fill(dist, Integer.MAX_VALUE);
        for (int i = 0; i <= n; i++) parent[i] = i;
        dist[1] = 0;
        pq.add(new int[]{0, 1});
        while (!pq.isEmpty()) {
            int[] top = pq.poll();
            int d = top[0], u = top[1];
            if (d > dist[u]) continue;
            for (int[] e : adj.get(u))
                if (d + e[1] < dist[e[0]]) { dist[e[0]] = d + e[1]; parent[e[0]] = u; pq.add(new int[]{dist[e[0]], e[0]}); }
        }
        List<Integer> path = new ArrayList<>();
        if (dist[n] == Integer.MAX_VALUE) { path.add(-1); return path; }
        for (int x = n; parent[x] != x; x = parent[x]) path.add(x);
        path.add(1);
        Collections.reverse(path);
        return path;
    }
}
```

#### Key Takeaways
- To print a shortest path rather than its length, store `parent` on every successful relaxation and backtrack from the target.

[↑ Contents](#contents) · [← Previous](#p363) · [Next →](#p365)

---

<a id="p365"></a>

### 25. Shortest Distance in a Binary Maze

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Shortest Path Algorithms | Core | No | [LeetCode](https://leetcode.com/problems/shortest-path-in-binary-matrix/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/shortest-distance-binary-maze) | [Watch](https://youtu.be/U5Mw4eyUmw4) |

#### Problem Statement
In an `n × n` binary matrix, find the length of the shortest **clear path** from the top-left to the bottom-right cell. You may only move through `0` cells, **8-directionally**, and the length counts the cells visited. Return −1 if there is no such path.

```text
grid = [[0,1],[1,0]]                 ->  2
grid = [[0,0,0],[1,1,0],[1,1,0]]     ->  4
grid = [[1,0,0],[1,1,0],[1,1,0]]     ->  -1
```

#### Approach: BFS (as in the video, G-36)
The video frames it as Dijkstra, but every step costs **1**, so a plain queue already pops cells in distance order and BFS **is** Dijkstra here.
- Start from `(0,0)` with `dist = 1` if it's 0.
- Relax the 8 neighbours. The first time `(n−1, n−1)` is reached, that's the answer.

**Complexity:** O(n² · 8) time, O(n²) space.

**C++**
```cpp
int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
    int n = grid.size();
    if (grid[0][0] != 0 || grid[n - 1][n - 1] != 0) return -1;
    vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
    queue<pair<int, int>> q;
    dist[0][0] = 1;
    q.push({0, 0});
    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        if (r == n - 1 && c == n - 1) return dist[r][c];
        for (int dr = -1; dr <= 1; dr++)
            for (int dc = -1; dc <= 1; dc++) {
                int nr = r + dr, nc = c + dc;
                if (nr >= 0 && nr < n && nc >= 0 && nc < n && grid[nr][nc] == 0 && dist[r][c] + 1 < dist[nr][nc]) {
                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
    }
    return -1;
}
```

**Java**
```java
class Solution {
    static int shortestPathBinaryMatrix(int[][] grid) {
        int n = grid.length;
        if (grid[0][0] != 0 || grid[n - 1][n - 1] != 0) return -1;
        int[][] dist = new int[n][n];
        for (int[] row : dist) Arrays.fill(row, Integer.MAX_VALUE);
        Queue<int[]> q = new LinkedList<>();
        dist[0][0] = 1;
        q.add(new int[]{0, 0});
        while (!q.isEmpty()) {
            int[] cur = q.remove();
            int r = cur[0], c = cur[1];
            if (r == n - 1 && c == n - 1) return dist[r][c];
            for (int dr = -1; dr <= 1; dr++)
                for (int dc = -1; dc <= 1; dc++) {
                    int nr = r + dr, nc = c + dc;
                    if (nr >= 0 && nr < n && nc >= 0 && nc < n && grid[nr][nc] == 0 && dist[r][c] + 1 < dist[nr][nc]) {
                        dist[nr][nc] = dist[r][c] + 1;
                        q.add(new int[]{nr, nc});
                    }
                }
        }
        return -1;
    }
}
```

#### Edge Cases & Pitfalls
- **Blocked endpoints.** If the start or the target is blocked, return −1.
- **A 1 × 1 grid of `[0]`** returns 1.
- **The GfG variant** has a given source and destination and 4-directional moves. Same BFS.

#### Key Takeaways
- On unit-weight grids, Dijkstra degenerates to BFS: a queue is enough.

[↑ Contents](#contents) · [← Previous](#p364) · [Next →](#p366)

---

<a id="p366"></a>

### 26. Path with minimum effort

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Shortest Path Algorithms | Core | No | [LeetCode](https://leetcode.com/problems/path-with-minimum-effort/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/path-with-minimum-effort) | [Watch](https://youtu.be/0ytpZyiZFhA) |

#### Problem Statement
`heights` is an `n × m` grid. The **effort** of a path is the **maximum absolute height difference** between consecutive cells on it. Moving 4-directionally from the top-left to the bottom-right, return the minimum possible effort.

```text
heights = [[1,2,2],[3,8,2],[5,3,5]]   ->  2   (1,3,5,3,5: max step 2)
heights = [[1,2,3],[3,8,4],[5,3,5]]   ->  1
```

#### Approach: Dijkstra with "max along the path" as the distance (as in the video, G-37)
- **Change what "distance" means.** `dist[cell]` is the minimum effort needed to reach that cell.
- **Relaxation.** `newEffort = max(dist[u], |h[u] − h[v]|)`; if it's smaller than `dist[v]`, update and push.
- **Why Dijkstra still works.** The path cost (a maximum of non-negative steps) never decreases along a path, so the greedy argument holds.
- **Early exit.** When the target is popped, its effort is final.

**Complexity:** O(n·m · 4 · log(n·m)) time, O(n·m) space.

**C++**
```cpp
int minimumEffortPath(vector<vector<int>>& heights) {
    int n = heights.size(), m = heights[0].size();
    vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;   // {effort, r, c}
    dist[0][0] = 0;
    pq.push({0, 0, 0});
    int dr[] = {-1, 0, 1, 0}, dc[] = {0, 1, 0, -1};
    while (!pq.empty()) {
        auto [diff, r, c] = pq.top(); pq.pop();
        if (r == n - 1 && c == m - 1) return diff;
        if (diff > dist[r][c]) continue;
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k], nc = c + dc[k];
            if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                int effort = max(diff, abs(heights[r][c] - heights[nr][nc]));
                if (effort < dist[nr][nc]) { dist[nr][nc] = effort; pq.push({effort, nr, nc}); }
            }
        }
    }
    return 0;
}
```

**Java**
```java
class Solution {
    static int minimumEffortPath(int[][] heights) {
        int n = heights.length, m = heights[0].length;
        int[][] dist = new int[n][m];
        for (int[] row : dist) Arrays.fill(row, Integer.MAX_VALUE);
        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> Integer.compare(a[0], b[0]));   // {effort, r, c}
        dist[0][0] = 0;
        pq.add(new int[]{0, 0, 0});
        int[] dr = {-1, 0, 1, 0}, dc = {0, 1, 0, -1};
        while (!pq.isEmpty()) {
            int[] top = pq.poll();
            int diff = top[0], r = top[1], c = top[2];
            if (r == n - 1 && c == m - 1) return diff;
            if (diff > dist[r][c]) continue;
            for (int k = 0; k < 4; k++) {
                int nr = r + dr[k], nc = c + dc[k];
                if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                    int effort = Math.max(diff, Math.abs(heights[r][c] - heights[nr][nc]));
                    if (effort < dist[nr][nc]) { dist[nr][nc] = effort; pq.add(new int[]{effort, nr, nc}); }
                }
            }
        }
        return 0;
    }
}
```

#### Key Takeaways
- Dijkstra works for any **monotone** path cost (sum, max, …), not just sums. "Minimise the maximum edge" is the bottleneck shortest path.

[↑ Contents](#contents) · [← Previous](#p365) · [Next →](#p367)

---

<a id="p367"></a>

### 27. Cheapest flight within K stops

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Shortest Path Algorithms | Pro | No | [LeetCode](https://leetcode.com/problems/cheapest-flights-within-k-stops/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/cheapest-flights-within-k-stops) | [Watch](https://youtu.be/9XybHVqTHcQ) |

#### Problem Statement
`n` cities and `flights[i] = [from, to, price]`. Return the cheapest price from `src` to `dst` using **at most `k` stops**, i.e. at most `k + 1` flights. Return −1 if there is no such route.

```text
n = 4, flights = [[0,1,100],[1,2,100],[2,0,100],[1,3,600],[2,3,200]], src = 0, dst = 3, k = 1   ->  700
(0->1->3 costs 700 with 1 stop; 0->1->2->3 costs 400 but needs 2 stops)
```

#### Intuition — why plain Dijkstra fails
Dijkstra orders by **cost**. Here the binding constraint is the **number of stops**, so a cheaper path with too many stops can lock in a vertex's distance and block a pricier path that uses fewer stops. Order by **stops** instead: BFS level by level. Each level adds exactly one stop, so a plain queue suffices.

#### Approach: BFS over (stops, node, cost) with distance relaxation (as in the video, G-38)
- Queue entries are `{stops, node, cost}`, starting from `{0, src, 0}`.
- Pop an entry. If `stops > k`, skip it: it can't take another flight.
- For each flight `node → v`, if `cost + price < dist[v]`, update `dist[v]` and push `{stops + 1, v, cost + price}`.
- The answer is `dist[dst]`, or −1.

Stops grow by exactly 1 per level, so a queue keeps the entries in order of stops.

**Complexity:** O(E · k) in the worst case, about O(N · E) in general. O(N + E) space.

**C++**
```cpp
int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
    vector<vector<pair<int, int>>> adj(n);
    for (auto& f : flights) adj[f[0]].push_back({f[1], f[2]});
    queue<tuple<int, int, int>> q;                       // {stops, node, cost}
    q.push({0, src, 0});
    vector<int> dist(n, INT_MAX);
    dist[src] = 0;
    while (!q.empty()) {
        auto [stops, node, cost] = q.front(); q.pop();
        if (stops > K) continue;
        for (auto& [v, w] : adj[node])
            if (cost + w < dist[v] && stops <= K) {
                dist[v] = cost + w;
                q.push({stops + 1, v, cost + w});
            }
    }
    return dist[dst] == INT_MAX ? -1 : dist[dst];
}
```

**Java**
```java
class Solution {
    static int findCheapestPrice(int n, int[][] flights, int src, int dst, int K) {
        List<List<int[]>> adj = new ArrayList<>();
        for (int i = 0; i < n; i++) adj.add(new ArrayList<>());
        for (int[] f : flights) adj.get(f[0]).add(new int[]{f[1], f[2]});
        Queue<int[]> q = new LinkedList<>();                  // {stops, node, cost}
        q.add(new int[]{0, src, 0});
        int[] dist = new int[n];
        Arrays.fill(dist, Integer.MAX_VALUE);
        dist[src] = 0;
        while (!q.isEmpty()) {
            int[] cur = q.remove();
            int stops = cur[0], node = cur[1], cost = cur[2];
            if (stops > K) continue;
            for (int[] e : adj.get(node))
                if (cost + e[1] < dist[e[0]] && stops <= K) {
                    dist[e[0]] = cost + e[1];
                    q.add(new int[]{stops + 1, e[0], cost + e[1]});
                }
        }
        return dist[dst] == Integer.MAX_VALUE ? -1 : dist[dst];
    }
}
```

#### Edge Cases & Pitfalls
- **Stops vs edges.** `k` stops means at most `k + 1` edges.
- **Correctness of the shared `dist` array.** Processing by stops level means a shorter-in-stops path is always explored before longer ones, so overwriting `dist` doesn't lose valid answers. A Bellman-Ford variant (k + 1 rounds over a copy of `dist`) is the textbook alternative.

#### Key Takeaways
- When a constraint other than cost bounds the path, such as a number of hops, run the search ordered by that constraint.

[↑ Contents](#contents) · [← Previous](#p366) · [Next →](#p368)

---

<a id="p368"></a>

### 28. Minimum multiplications to reach end

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Shortest Path Algorithms | Pro | Yes | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/minimum-multiplications-to-reach-end) | [Watch](https://youtu.be/_BvEJ3VIDWw) |

#### Problem Statement
Starting from `start`, one step multiplies the current number by any value in `arr` and takes the result **mod 100000**. Return the minimum number of steps to reach `end`, or −1 if that's impossible.

```text
arr = [2, 5, 7], start = 3, end = 30      ->  2   (3*2 = 6, 6*5 = 30)
arr = [3, 4, 65], start = 7, end = 66175  ->  4
```

#### Approach: BFS over residues 0 … 99999 (as in the video, G-39)
- **Treat each residue as a node.** There are only 100000 states, and every multiplication is an edge of weight 1.
- **Run BFS from `start`** with `dist[]` over all residues. The first time `end` is reached gives the answer.

**Complexity:** O(100000 · |arr|) time, O(100000) space.

**C++**
```cpp
int minimumMultiplications(vector<int>& arr, int start, int end) {
    const int MOD = 100000;
    if (start == end) return 0;
    vector<int> dist(MOD, INT_MAX);
    queue<pair<int, int>> q;                              // {node, steps}
    dist[start] = 0;
    q.push({start, 0});
    while (!q.empty()) {
        auto [node, steps] = q.front(); q.pop();
        for (int x : arr) {
            int num = (int)((1LL * node * x) % MOD);
            if (steps + 1 < dist[num]) {
                dist[num] = steps + 1;
                if (num == end) return steps + 1;
                q.push({num, steps + 1});
            }
        }
    }
    return -1;
}
```

**Java**
```java
class Solution {
    static int minimumMultiplications(int[] arr, int start, int end) {
        final int MOD = 100000;
        if (start == end) return 0;
        int[] dist = new int[MOD];
        Arrays.fill(dist, Integer.MAX_VALUE);
        Queue<int[]> q = new LinkedList<>();
        dist[start] = 0;
        q.add(new int[]{start, 0});
        while (!q.isEmpty()) {
            int[] cur = q.remove();
            int node = cur[0], steps = cur[1];
            for (int x : arr) {
                int num = (int) ((1L * node * x) % MOD);
                if (steps + 1 < dist[num]) {
                    dist[num] = steps + 1;
                    if (num == end) return steps + 1;
                    q.add(new int[]{num, steps + 1});
                }
            }
        }
        return -1;
    }
}
```

#### Edge Cases & Pitfalls
- **`start == end`** gives 0.
- **Overflow.** Multiply in 64 bits before taking the modulus.

#### Key Takeaways
- Problems with a small finite state space become shortest-path problems on an **implicit graph**.

[↑ Contents](#contents) · [← Previous](#p367) · [Next →](#p369)

---

<a id="p369"></a>

### 29. Number of ways to arrive at destination

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Shortest Path Algorithms | Pro | No | [LeetCode](https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/number-of-ways-to-arrive-at-destination) | [Watch](https://youtu.be/_-0mx0SmYxA) |

#### Problem Statement
In a weighted undirected graph with `n` intersections, count the number of **distinct shortest paths** from `0` to `n−1`, modulo 10⁹ + 7.

```text
n = 7, roads = [[0,6,7],[0,1,2],[1,2,3],[1,3,3],[6,3,3],[3,5,1],[6,5,1],[2,5,1],[0,4,5],[4,6,2]]   ->  4
```

#### Approach: Dijkstra + a `ways[]` array (as in the video, G-40)
When relaxing the edge `u → v` with weight `w`:
- **`d + w < dist[v]`:** a strictly shorter path. Set `dist[v] = d + w`, **`ways[v] = ways[u]`**, and push.
- **`d + w == dist[v]`:** another shortest path. **`ways[v] += ways[u]`**, modulo.

Start with `ways[0] = 1`.

**Complexity:** O(E log V) time, O(V + E) space.

**C++**
```cpp
int countPaths(int n, vector<vector<int>>& roads) {
    const long long MOD = 1e9 + 7;
    vector<vector<pair<int, int>>> adj(n);
    for (auto& r : roads) { adj[r[0]].push_back({r[1], r[2]}); adj[r[1]].push_back({r[0], r[2]}); }
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    vector<long long> dist(n, LLONG_MAX), ways(n, 0);
    dist[0] = 0; ways[0] = 1;
    pq.push({0, 0});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto& [v, w] : adj[u]) {
            if (d + w < dist[v]) {                       // strictly shorter
                dist[v] = d + w;
                ways[v] = ways[u];
                pq.push({dist[v], v});
            } else if (d + w == dist[v]) {               // another shortest way
                ways[v] = (ways[v] + ways[u]) % MOD;
            }
        }
    }
    return (int)(ways[n - 1] % MOD);
}
```

**Java**
```java
class Solution {
    static int countPaths(int n, int[][] roads) {
        final long MOD = 1_000_000_007L;
        List<List<int[]>> adj = new ArrayList<>();
        for (int i = 0; i < n; i++) adj.add(new ArrayList<>());
        for (int[] r : roads) { adj.get(r[0]).add(new int[]{r[1], r[2]}); adj.get(r[1]).add(new int[]{r[0], r[2]}); }
        PriorityQueue<long[]> pq = new PriorityQueue<>((a, b) -> Long.compare(a[0], b[0]));
        long[] dist = new long[n], ways = new long[n];
        Arrays.fill(dist, Long.MAX_VALUE);
        dist[0] = 0; ways[0] = 1;
        pq.add(new long[]{0, 0});
        while (!pq.isEmpty()) {
            long[] top = pq.poll();
            long d = top[0];
            int u = (int) top[1];
            if (d > dist[u]) continue;
            for (int[] e : adj.get(u)) {
                int v = e[0];
                long nd = d + e[1];
                if (nd < dist[v]) { dist[v] = nd; ways[v] = ways[u]; pq.add(new long[]{nd, v}); }
                else if (nd == dist[v]) ways[v] = (ways[v] + ways[u]) % MOD;
            }
        }
        return (int) (ways[n - 1] % MOD);
    }
}
```

#### Edge Cases & Pitfalls
- **Distances can exceed 32 bits.** Use `long long` for `dist`.
- **Skip stale heap entries.** Otherwise `ways` from outdated distances get added again.

#### Key Takeaways
- Counting shortest paths: Dijkstra plus "copy on strictly better, add on equal".

[↑ Contents](#contents) · [← Previous](#p368) · [Next →](#p370)

---

<a id="p370"></a>

### 30. Bellman ford algorithm

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Shortest Path Algorithms | Pro | Yes | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/bellman-ford-algorithm) | [Watch](https://youtu.be/0vVofAhAYjc) |

#### Problem Statement
Given a directed weighted graph that may have **negative** edge weights, return shortest distances from source `S`. If a **negative cycle** is reachable, return `[-1]`. GfG uses `1e8` for unreachable vertices.

```text
V = 3, edges = [[0,1,5],[1,0,3],[1,2,-1],[2,0,1]], S = 2   ->  [1, 6, 0]
V = 2, edges = [[0,1,-1],[1,0,-2]] -> [-1]   (negative cycle)
```

#### Approach: Relax every edge V − 1 times, then check once more (as in the video)
- **Why V − 1 rounds.** A shortest path uses at most V − 1 edges, so V − 1 rounds of relaxing **all** edges are enough to settle every distance.
- **Detecting a negative cycle.** If the **V-th** round can still relax any edge, distances keep decreasing forever, which means a negative cycle is reachable.

**Complexity:** O(V · E) time, O(V) space.

**C++**
```cpp
vector<int> bellmanFord(int V, vector<vector<int>>& edges, int S) {
    const int INF = 1e8;
    vector<int> dist(V, INF);
    dist[S] = 0;
    for (int i = 0; i < V - 1; i++)
        for (auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            if (dist[u] != INF && dist[u] + w < dist[v]) dist[v] = dist[u] + w;
        }
    for (auto& e : edges) {                              // V-th round: still relaxing?
        int u = e[0], v = e[1], w = e[2];
        if (dist[u] != INF && dist[u] + w < dist[v]) return {-1};
    }
    return dist;
}
```

**Java**
```java
class Solution {
    static int[] bellmanFord(int V, int[][] edges, int S) {
        final int INF = (int) 1e8;
        int[] dist = new int[V];
        Arrays.fill(dist, INF);
        dist[S] = 0;
        for (int i = 0; i < V - 1; i++)
            for (int[] e : edges)
                if (dist[e[0]] != INF && dist[e[0]] + e[2] < dist[e[1]]) dist[e[1]] = dist[e[0]] + e[2];
        for (int[] e : edges)
            if (dist[e[0]] != INF && dist[e[0]] + e[2] < dist[e[1]]) return new int[]{-1};
        return dist;
    }
}
```

#### Edge Cases & Pitfalls
- **Directed edges only.** Bellman-Ford works on directed graphs. An undirected negative edge is itself a negative cycle (u → v → u).
- **Guard the infinity sentinel.** Check `dist[u] != INF` before adding, so "infinity + negative" doesn't look like a real distance.

#### Key Takeaways
- Bellman-Ford handles negative weights and detects negative cycles, at O(VE). Use Dijkstra when all weights are non-negative.

[↑ Contents](#contents) · [← Previous](#p369) · [Next →](#p371)

---

<a id="p371"></a>

### 31. Floyd warshall algorithm

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Shortest Path Algorithms | Pro | Yes | — | [Watch](https://youtu.be/YbY8cVwWAvw) |

#### Problem Statement
Compute **all-pairs** shortest distances **in place** in an adjacency matrix where `−1` means "no edge". Keep −1 for unreachable pairs. Optionally, detect negative cycles.

```text
matrix = [[0,1,43],[1,0,6],[-1,-1,0]]   ->  [[0,1,7],[1,0,6],[-1,-1,0]]
```

#### Approach: Floyd–Warshall, trying every vertex as an intermediate (as in the video)
- **The idea.** For `via = 0 … V−1`, allow paths whose intermediate vertices come from `{0 … via}`:

  `d[i][j] = min(d[i][j], d[i][via] + d[via][j])`
- **Negative cycles.** After finishing, `d[i][i] < 0` for some `i` means a negative cycle.
- **When to use it.** Floyd–Warshall is simple and works with negative edges. Running Dijkstra from every source is faster on sparse graphs with non-negative weights, at O(V · E log V).

**Complexity:** O(V³) time, O(1) extra space (in place).

**C++**
```cpp
void shortestDistance(vector<vector<int>>& matrix) {
    int n = matrix.size();
    const int INF = 1e9;
    for (auto& row : matrix) for (int& x : row) if (x == -1) x = INF;
    for (int i = 0; i < n; i++) matrix[i][i] = min(matrix[i][i], 0);
    for (int via = 0; via < n; via++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (matrix[i][via] < INF && matrix[via][j] < INF)
                    matrix[i][j] = min(matrix[i][j], matrix[i][via] + matrix[via][j]);
    // negative cycle check (optional): any matrix[i][i] < 0
    for (auto& row : matrix) for (int& x : row) if (x >= INF) x = -1;
}
```

**Java**
```java
class Solution {
    static void shortestDistance(int[][] matrix) {
        int n = matrix.length;
        final int INF = (int) 1e9;
        for (int[] row : matrix) for (int j = 0; j < n; j++) if (row[j] == -1) row[j] = INF;
        for (int i = 0; i < n; i++) matrix[i][i] = Math.min(matrix[i][i], 0);
        for (int via = 0; via < n; via++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (matrix[i][via] < INF && matrix[via][j] < INF)
                        matrix[i][j] = Math.min(matrix[i][j], matrix[i][via] + matrix[via][j]);
        for (int[] row : matrix) for (int j = 0; j < n; j++) if (row[j] >= INF) row[j] = -1;
    }
}
```

#### Edge Cases & Pitfalls
- **The intermediate loop `via` must be outermost.** That ordering is what makes the dynamic programming correct.
- **Convert −1 to a large INF** before the loops and back afterwards. Never add to INF.
- **The −1 sentinel assumes non-negative weights**, as in the GfG version. With negative weights, a real distance of −1 would be confused with "unreachable". Use a separate INF there.

#### Key Takeaways
- All-pairs shortest paths in O(V³) by dynamic programming over the allowed intermediate vertices.

[↑ Contents](#contents) · [← Previous](#p370) · [Next →](#p372)

---

<a id="p372"></a>

### 32. Find the city with the smallest number of neighbors

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Shortest Path Algorithms | Pro | No | [LeetCode](https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/find-city-smallest-number-neighbors-threshold-distance) | [Watch](https://youtu.be/PwMVNSJ5SLI) |

#### Problem Statement
Given `n` cities, weighted undirected edges and a `distanceThreshold`, return the city with the **fewest** other cities reachable within the threshold. On a tie, return the city with the **largest** index.

```text
n = 4, edges = [[0,1,3],[1,2,1],[1,3,4],[2,3,1]], threshold = 4   ->  3
```

#### Approach 1: Floyd–Warshall, then count per city (as in the video, G-43)
- Compute all-pairs distances.
- For each city, count the other cities with `d ≤ threshold`.
- Pick the minimum count, scanning `i` upwards with `≤` so ties go to the larger index.

**Complexity:** O(n³) time, O(n²) space.

**C++**
```cpp
int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
    const int INF = 1e9;
    vector<vector<int>> d(n, vector<int>(n, INF));
    for (int i = 0; i < n; i++) d[i][i] = 0;
    for (auto& e : edges) { d[e[0]][e[1]] = min(d[e[0]][e[1]], e[2]); d[e[1]][e[0]] = min(d[e[1]][e[0]], e[2]); }
    for (int via = 0; via < n; via++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (d[i][via] < INF && d[via][j] < INF) d[i][j] = min(d[i][j], d[i][via] + d[via][j]);
    int best = -1, minCnt = n + 1;
    for (int i = 0; i < n; i++) {
        int cnt = 0;
        for (int j = 0; j < n; j++) if (i != j && d[i][j] <= distanceThreshold) cnt++;
        if (cnt <= minCnt) { minCnt = cnt; best = i; }      // <= : ties -> larger index
    }
    return best;
}
```

**Java**
```java
class Solution {
    static int findTheCity(int n, int[][] edges, int distanceThreshold) {
        final int INF = (int) 1e9;
        int[][] d = new int[n][n];
        for (int[] row : d) Arrays.fill(row, INF);
        for (int i = 0; i < n; i++) d[i][i] = 0;
        for (int[] e : edges) { d[e[0]][e[1]] = Math.min(d[e[0]][e[1]], e[2]); d[e[1]][e[0]] = Math.min(d[e[1]][e[0]], e[2]); }
        for (int via = 0; via < n; via++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (d[i][via] < INF && d[via][j] < INF) d[i][j] = Math.min(d[i][j], d[i][via] + d[via][j]);
        int best = -1, minCnt = n + 1;
        for (int i = 0; i < n; i++) {
            int cnt = 0;
            for (int j = 0; j < n; j++) if (i != j && d[i][j] <= distanceThreshold) cnt++;
            if (cnt <= minCnt) { minCnt = cnt; best = i; }
        }
        return best;
    }
}
```

#### Approach 2: Dijkstra from every city *(alternative)*
Run Dijkstra from each city and count its reachable cities in the same way.

**Complexity:** O(n · E log n), which is better on sparse graphs.

**C++**
```cpp
int findTheCityDijkstra(int n, vector<vector<int>>& edges, int distanceThreshold) {
    vector<vector<pair<int, int>>> adj(n);
    for (auto& e : edges) { adj[e[0]].push_back({e[1], e[2]}); adj[e[1]].push_back({e[0], e[2]}); }
    int best = -1, minCnt = n + 1;
    for (int s = 0; s < n; s++) {
        vector<int> dist(n, INT_MAX);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        dist[s] = 0; pq.push({0, s});
        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d > dist[u]) continue;
            for (auto& [v, w] : adj[u]) if (d + w < dist[v]) { dist[v] = d + w; pq.push({dist[v], v}); }
        }
        int cnt = 0;
        for (int j = 0; j < n; j++) if (j != s && dist[j] <= distanceThreshold) cnt++;
        if (cnt <= minCnt) { minCnt = cnt; best = s; }
    }
    return best;
}
```

**Java**
```java
class Solution {
    static int findTheCityDijkstra(int n, int[][] edges, int distanceThreshold) {
        List<List<int[]>> adj = new ArrayList<>();
        for (int i = 0; i < n; i++) adj.add(new ArrayList<>());
        for (int[] e : edges) { adj.get(e[0]).add(new int[]{e[1], e[2]}); adj.get(e[1]).add(new int[]{e[0], e[2]}); }
        int best = -1, minCnt = n + 1;
        for (int s = 0; s < n; s++) {
            int[] dist = new int[n];
            Arrays.fill(dist, Integer.MAX_VALUE);
            PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> Integer.compare(a[0], b[0]));
            dist[s] = 0; pq.add(new int[]{0, s});
            while (!pq.isEmpty()) {
                int[] top = pq.poll();
                if (top[0] > dist[top[1]]) continue;
                for (int[] e : adj.get(top[1]))
                    if (top[0] + e[1] < dist[e[0]]) { dist[e[0]] = top[0] + e[1]; pq.add(new int[]{dist[e[0]], e[0]}); }
            }
            int cnt = 0;
            for (int j = 0; j < n; j++) if (j != s && dist[j] <= distanceThreshold) cnt++;
            if (cnt <= minCnt) { minCnt = cnt; best = s; }
        }
        return best;
    }
}
```

#### Key Takeaways
- Once all-pairs distances are known, the rest is counting. Remember the tie-break towards the larger index.

[↑ Contents](#contents) · [← Previous](#p371) · [Next →](#p373)

---

<a id="p373"></a>

### 33. Network Delay Time

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Shortest Path Algorithms | Core | No | [LeetCode](https://leetcode.com/problems/network-delay-time/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/network-delay-time) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
`times[i] = (u, v, w)` is a directed edge with travel time `w`. A signal is sent from node `k`; nodes are `1 … n`. Return the time until **all** nodes have received it, or −1 if some node never does.

```text
times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2   ->  2
times = [[1,2,1]], n = 2, k = 2                   ->  -1
```

#### Approach 1: Bellman-Ford *(brute-ish)*
Relax all edges `n − 1` times. The answer is the maximum distance, or −1 if any node is unreachable.

**Complexity:** O(n · E) time, O(n) space.

**C++**
```cpp
int networkDelayBF(vector<vector<int>>& times, int n, int k) {
    const int INF = 1e9;
    vector<int> dist(n + 1, INF);
    dist[k] = 0;
    for (int i = 0; i < n - 1; i++)
        for (auto& t : times)
            if (dist[t[0]] != INF && dist[t[0]] + t[2] < dist[t[1]]) dist[t[1]] = dist[t[0]] + t[2];
    int ans = 0;
    for (int i = 1; i <= n; i++) ans = max(ans, dist[i]);
    return ans == INF ? -1 : ans;
}
```

**Java**
```java
class Solution {
    static int networkDelayBF(int[][] times, int n, int k) {
        final int INF = (int) 1e9;
        int[] dist = new int[n + 1];
        Arrays.fill(dist, INF);
        dist[k] = 0;
        for (int i = 0; i < n - 1; i++)
            for (int[] t : times)
                if (dist[t[0]] != INF && dist[t[0]] + t[2] < dist[t[1]]) dist[t[1]] = dist[t[0]] + t[2];
        int ans = 0;
        for (int i = 1; i <= n; i++) ans = Math.max(ans, dist[i]);
        return ans == INF ? -1 : ans;
    }
}
```

#### Approach 2: Optimal — Dijkstra from `k`, then take the maximum distance
The signal reaches every node along its shortest path, so the last node to receive it determines the answer: `max(dist)`.

**Complexity:** O(E log n) time, O(n + E) space.

**C++**
```cpp
int networkDelayTime(vector<vector<int>>& times, int n, int k) {
    vector<vector<pair<int, int>>> adj(n + 1);
    for (auto& t : times) adj[t[0]].push_back({t[1], t[2]});
    vector<int> dist(n + 1, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    dist[k] = 0;
    pq.push({0, k});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto& [v, w] : adj[u]) if (d + w < dist[v]) { dist[v] = d + w; pq.push({dist[v], v}); }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (dist[i] == INT_MAX) return -1;
        ans = max(ans, dist[i]);
    }
    return ans;
}
```

**Java**
```java
class Solution {
    static int networkDelayTime(int[][] times, int n, int k) {
        List<List<int[]>> adj = new ArrayList<>();
        for (int i = 0; i <= n; i++) adj.add(new ArrayList<>());
        for (int[] t : times) adj.get(t[0]).add(new int[]{t[1], t[2]});
        int[] dist = new int[n + 1];
        Arrays.fill(dist, Integer.MAX_VALUE);
        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> Integer.compare(a[0], b[0]));
        dist[k] = 0;
        pq.add(new int[]{0, k});
        while (!pq.isEmpty()) {
            int[] top = pq.poll();
            if (top[0] > dist[top[1]]) continue;
            for (int[] e : adj.get(top[1]))
                if (top[0] + e[1] < dist[e[0]]) { dist[e[0]] = top[0] + e[1]; pq.add(new int[]{dist[e[0]], e[0]}); }
        }
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            if (dist[i] == Integer.MAX_VALUE) return -1;
            ans = Math.max(ans, dist[i]);
        }
        return ans;
    }
}
```

#### Key Takeaways
- "Time for a broadcast to reach everyone" is the maximum single-source shortest distance.

[↑ Contents](#contents) · [← Previous](#p372) · [Next →](#p374)

---

<a id="p374"></a>

### 34. Swim in Rising Water

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Shortest Path Algorithms | Pro | No | [LeetCode](https://leetcode.com/problems/swim-in-rising-water/) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
`grid[i][j]` is the elevation of a cell in an `n × n` grid. At time `t`, the water level is `t`, and you can move between adjacent cells if **both** have elevation ≤ `t`. Starting at `(0,0)`, return the minimum time to reach `(n−1, n−1)`.

```text
grid = [[0,2],[1,3]]   ->  3
grid = [[0,1,2,3,4],[24,23,22,21,5],[12,13,14,15,16],[11,17,18,19,20],[10,9,8,7,6]]   ->  16
```

#### Intuition
The time a path needs is the **maximum elevation along it**, starting cell included. Minimise that maximum over all paths. This is the same bottleneck shortest path as Path With Minimum Effort.

#### Approach 1: Binary search on t + BFS
- **Feasibility check.** For a candidate `t`, the target is reachable iff a BFS that only uses cells with elevation `≤ t` reaches it.
- **Search for the smallest feasible `t`.** Feasibility is monotone in `t`, so binary search over `t` in `[grid[0][0], n² − 1]`.

**Complexity:** O(n² log n²) time, O(n²) space.

**C++**
```cpp
bool canReach(vector<vector<int>>& g, int t) {
    int n = g.size();
    if (g[0][0] > t) return false;
    vector<vector<int>> vis(n, vector<int>(n, 0));
    queue<pair<int, int>> q;
    q.push({0, 0}); vis[0][0] = 1;
    int dr[] = {-1, 0, 1, 0}, dc[] = {0, 1, 0, -1};
    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        if (r == n - 1 && c == n - 1) return true;
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k], nc = c + dc[k];
            if (nr >= 0 && nr < n && nc >= 0 && nc < n && !vis[nr][nc] && g[nr][nc] <= t) {
                vis[nr][nc] = 1; q.push({nr, nc});
            }
        }
    }
    return false;
}
int swimInWaterBS(vector<vector<int>>& grid) {
    int n = grid.size(), lo = grid[0][0], hi = n * n - 1;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (canReach(grid, mid)) hi = mid; else lo = mid + 1;
    }
    return lo;
}
```

**Java**
```java
class Solution {
    static boolean canReach(int[][] g, int t) {
        int n = g.length;
        if (g[0][0] > t) return false;
        int[][] vis = new int[n][n];
        Queue<int[]> q = new LinkedList<>();
        q.add(new int[]{0, 0}); vis[0][0] = 1;
        int[] dr = {-1, 0, 1, 0}, dc = {0, 1, 0, -1};
        while (!q.isEmpty()) {
            int[] cur = q.remove();
            if (cur[0] == n - 1 && cur[1] == n - 1) return true;
            for (int k = 0; k < 4; k++) {
                int nr = cur[0] + dr[k], nc = cur[1] + dc[k];
                if (nr >= 0 && nr < n && nc >= 0 && nc < n && vis[nr][nc] == 0 && g[nr][nc] <= t) {
                    vis[nr][nc] = 1; q.add(new int[]{nr, nc});
                }
            }
        }
        return false;
    }
    static int swimInWaterBS(int[][] grid) {
        int n = grid.length, lo = grid[0][0], hi = n * n - 1;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (canReach(grid, mid)) hi = mid; else lo = mid + 1;
        }
        return lo;
    }
}
```

#### Approach 2: Optimal — Dijkstra minimising the path maximum
- `dist[cell]` is the smallest possible maximum elevation on a path to that cell.
- Relax with `max(dist[u], grid[v])`.
- Pop cells in order from a min-heap. The target's value at pop time is the answer.

**Complexity:** O(n² log n) time, O(n²) space.

**C++**
```cpp
int swimInWater(vector<vector<int>>& grid) {
    int n = grid.size();
    vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
    dist[0][0] = grid[0][0];
    pq.push({grid[0][0], 0, 0});
    int dr[] = {-1, 0, 1, 0}, dc[] = {0, 1, 0, -1};
    while (!pq.empty()) {
        auto [t, r, c] = pq.top(); pq.pop();
        if (r == n - 1 && c == n - 1) return t;
        if (t > dist[r][c]) continue;
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k], nc = c + dc[k];
            if (nr >= 0 && nr < n && nc >= 0 && nc < n) {
                int nt = max(t, grid[nr][nc]);
                if (nt < dist[nr][nc]) { dist[nr][nc] = nt; pq.push({nt, nr, nc}); }
            }
        }
    }
    return -1;
}
```

**Java**
```java
class Solution {
    static int swimInWater(int[][] grid) {
        int n = grid.length;
        int[][] dist = new int[n][n];
        for (int[] row : dist) Arrays.fill(row, Integer.MAX_VALUE);
        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> Integer.compare(a[0], b[0]));
        dist[0][0] = grid[0][0];
        pq.add(new int[]{grid[0][0], 0, 0});
        int[] dr = {-1, 0, 1, 0}, dc = {0, 1, 0, -1};
        while (!pq.isEmpty()) {
            int[] top = pq.poll();
            int t = top[0], r = top[1], c = top[2];
            if (r == n - 1 && c == n - 1) return t;
            if (t > dist[r][c]) continue;
            for (int k = 0; k < 4; k++) {
                int nr = r + dr[k], nc = c + dc[k];
                if (nr >= 0 && nr < n && nc >= 0 && nc < n) {
                    int nt = Math.max(t, grid[nr][nc]);
                    if (nt < dist[nr][nc]) { dist[nr][nc] = nt; pq.add(new int[]{nt, nr, nc}); }
                }
            }
        }
        return -1;
    }
}
```

#### Key Takeaways
- "Minimise the maximum along a path" can be solved with Dijkstra using `max` instead of `+`, or with binary search on the answer plus a BFS feasibility check. A DSU that adds cells in increasing elevation works too.

[↑ Contents](#contents) · [← Previous](#p373) · [Next →](#p375)

---

## Minimum Spanning Tree

<a id="p375"></a>

### 35. Disjoint Set

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Minimum Spanning Tree | Core | Yes | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/disjoint-set-union) | [Watch](https://youtu.be/aBxjDBC4M1U) |

#### Problem Statement
Implement a **Disjoint Set Union (DSU / Union-Find)** over elements `0 … n−1`:
- `findUPar(x)` returns the ultimate parent (representative) of x's set;
- `union(u, v)` merges the two sets;
- answering "are u and v in the same set?" is a comparison of their representatives.

```text
union(1,2), union(2,3), union(4,5), union(6,7), union(5,6)
same(3,7)? -> false;   union(3,7);   same(3,7)? -> true
```

#### Why not BFS or DFS?
To answer connectivity queries on a graph that **keeps changing** (edges being added), BFS or DFS costs O(V + E) **per query**. DSU answers each one in near-constant time.

#### Approach 1: Naive DSU — parent array only
- `find` follows parent pointers up to the root.
- `union` attaches one root under the other.

The tree can degenerate into a chain, so a single `find` can cost O(n).

**C++**
```cpp
class DSUNaive {
    vector<int> parent;
public:
    DSUNaive(int n) : parent(n) { iota(parent.begin(), parent.end(), 0); }
    int findUPar(int x) { while (parent[x] != x) x = parent[x]; return x; }
    void unite(int u, int v) {
        int pu = findUPar(u), pv = findUPar(v);
        if (pu != pv) parent[pu] = pv;
    }
};
```

**Java**
```java
class DSUNaive {
    private final int[] parent;
    DSUNaive(int n) { parent = new int[n]; for (int i = 0; i < n; i++) parent[i] = i; }
    int findUPar(int x) { while (parent[x] != x) x = parent[x]; return x; }
    void unite(int u, int v) {
        int pu = findUPar(u), pv = findUPar(v);
        if (pu != pv) parent[pu] = pv;
    }
}
```

#### Approach 2: Optimal — path compression + union by rank / by size (as in the video)
- **Path compression.** During `find`, point every node on the path **directly at the root**: `parent[x] = find(parent[x])`.
- **Union by rank.** `rank` is an upper bound on the tree height. Attach the **smaller-rank** root under the larger one. If the ranks are equal, pick either and increment the new root's rank.
- **Union by size.** Attach the root of the **smaller set** under the larger one and add the sizes. It's equivalent in practice and more intuitive, and the size is also useful directly.

Together these give **amortised O(α(n))** per operation, where α is the inverse Ackermann function, at most 4 for any practical n. In other words, effectively constant time.

**C++**
```cpp
class DisjointSet {
    vector<int> rank, parent, size;
public:
    DisjointSet(int n) : rank(n + 1, 0), parent(n + 1), size(n + 1, 1) {
        iota(parent.begin(), parent.end(), 0);
    }
    int findUPar(int node) {
        if (node == parent[node]) return node;
        return parent[node] = findUPar(parent[node]);          // path compression
    }
    void unionByRank(int u, int v) {
        int pu = findUPar(u), pv = findUPar(v);
        if (pu == pv) return;
        if (rank[pu] < rank[pv]) parent[pu] = pv;
        else if (rank[pv] < rank[pu]) parent[pv] = pu;
        else { parent[pv] = pu; rank[pu]++; }
    }
    void unionBySize(int u, int v) {
        int pu = findUPar(u), pv = findUPar(v);
        if (pu == pv) return;
        if (size[pu] < size[pv]) { parent[pu] = pv; size[pv] += size[pu]; }
        else { parent[pv] = pu; size[pu] += size[pv]; }
    }
    bool same(int u, int v) { return findUPar(u) == findUPar(v); }
    int sizeOf(int u) { return size[findUPar(u)]; }
};
```

**Java**
```java
class DisjointSet {
    private final int[] rank, parent, size;
    DisjointSet(int n) {
        rank = new int[n + 1]; parent = new int[n + 1]; size = new int[n + 1];
        for (int i = 0; i <= n; i++) { parent[i] = i; size[i] = 1; }
    }
    int findUPar(int node) {
        if (node == parent[node]) return node;
        return parent[node] = findUPar(parent[node]);
    }
    void unionByRank(int u, int v) {
        int pu = findUPar(u), pv = findUPar(v);
        if (pu == pv) return;
        if (rank[pu] < rank[pv]) parent[pu] = pv;
        else if (rank[pv] < rank[pu]) parent[pv] = pu;
        else { parent[pv] = pu; rank[pu]++; }
    }
    void unionBySize(int u, int v) {
        int pu = findUPar(u), pv = findUPar(v);
        if (pu == pv) return;
        if (size[pu] < size[pv]) { parent[pu] = pv; size[pv] += size[pu]; }
        else { parent[pv] = pu; size[pu] += size[pv]; }
    }
    boolean same(int u, int v) { return findUPar(u) == findUPar(v); }
    int sizeOf(int u) { return size[findUPar(u)]; }
}
```

#### Edge Cases & Pitfalls
- **Always union the ultimate parents**, never the raw nodes.
- **Sizing for 1-indexed problems.** The constructor allocates `n + 1` entries so that both 0- and 1-indexed problems work.

#### Key Takeaways
- DSU is the tool for dynamic connectivity: Kruskal's MST, counting components, accounts merge, and islands II.

[↑ Contents](#contents) · [← Previous](#p374) · [Next →](#p376)

---

<a id="p376"></a>

### 36. Find the MST weight

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Minimum Spanning Tree | Core | Yes | [LeetCode](https://leetcode.com/problems/connecting-cities-with-minimum-cost/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/find-the-mst-weight) | [Watch](https://youtu.be/mJcZjjKzeqk) |

#### Problem Statement
Given a connected, weighted, undirected graph, return the total weight of a **minimum spanning tree (MST)**: a subset of `V − 1` edges connecting all vertices with the minimum total weight.

```text
V = 5, edges = [[0,1,2],[0,2,1],[1,2,1],[2,3,2],[3,4,1],[4,2,2]]   ->  5
```

#### Approach 1: Prim's algorithm — grow one tree with a min-heap (as in the video)
- **Start from any vertex.** Push `{0, startVertex}` into a min-heap of `{weight, node}`.
- **Repeatedly add the cheapest new vertex:**
  - pop the cheapest `{w, node}`;
  - if `node` is already in the MST, skip it;
  - otherwise mark it, add `w` to the sum, and push `{edgeWeight, neighbour}` for every unvisited neighbour.

This is greedy: the cheapest edge leaving the current tree is always safe to add (the **cut property**).

**Complexity:** O(E log E) time, O(E) space.

**C++**
```cpp
int spanningTreePrim(int V, vector<vector<pair<int, int>>>& adj) {    // adj[u] = {v, w}
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;   // {w, node}
    vector<int> vis(V, 0);
    pq.push({0, 0});
    int sum = 0;
    while (!pq.empty()) {
        auto [w, node] = pq.top(); pq.pop();
        if (vis[node]) continue;
        vis[node] = 1;
        sum += w;
        for (auto& [v, ew] : adj[node]) if (!vis[v]) pq.push({ew, v});
    }
    return sum;
}
```

**Java**
```java
class Solution {
    static int spanningTreePrim(int V, List<List<int[]>> adj) {          // adj[u] = {v, w}
        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> Integer.compare(a[0], b[0]));
        int[] vis = new int[V];
        pq.add(new int[]{0, 0});
        int sum = 0;
        while (!pq.isEmpty()) {
            int[] top = pq.poll();
            int w = top[0], node = top[1];
            if (vis[node] == 1) continue;
            vis[node] = 1;
            sum += w;
            for (int[] e : adj.get(node)) if (vis[e[0]] == 0) pq.add(new int[]{e[1], e[0]});
        }
        return sum;
    }
}
```

#### Approach 2: Kruskal's algorithm — sort the edges + DSU (Striver's G-47)
- Sort all edges by weight.
- Scan them in increasing order, taking an edge iff its endpoints are in **different** DSU sets. Taking such an edge never creates a cycle. Union the sets.

**Complexity:** O(E log E) for the sort, plus O(E·α(V)). O(V + E) space.

**C++**
```cpp
int findK(vector<int>& par, int x) { return par[x] == x ? x : par[x] = findK(par, par[x]); }
int spanningTreeKruskal(int V, vector<vector<int>>& edges) {          // {u, v, w}
    vector<vector<int>> e = edges;
    sort(e.begin(), e.end(), [](const vector<int>& a, const vector<int>& b) { return a[2] < b[2]; });
    vector<int> par(V), rnk(V, 0);
    iota(par.begin(), par.end(), 0);
    int sum = 0;
    for (auto& ed : e) {
        int a = findK(par, ed[0]), b = findK(par, ed[1]);
        if (a == b) continue;                            // would form a cycle
        if (rnk[a] < rnk[b]) swap(a, b);
        par[b] = a;
        if (rnk[a] == rnk[b]) rnk[a]++;
        sum += ed[2];
    }
    return sum;
}
```

**Java**
```java
class Solution {
    static int findK(int[] par, int x) { return par[x] == x ? x : (par[x] = findK(par, par[x])); }
    static int spanningTreeKruskal(int V, int[][] edges) {
        int[][] e = edges.clone();
        Arrays.sort(e, (a, b) -> Integer.compare(a[2], b[2]));
        int[] par = new int[V], rnk = new int[V];
        for (int i = 0; i < V; i++) par[i] = i;
        int sum = 0;
        for (int[] ed : e) {
            int a = findK(par, ed[0]), b = findK(par, ed[1]);
            if (a == b) continue;
            if (rnk[a] < rnk[b]) { int t = a; a = b; b = t; }
            par[b] = a;
            if (rnk[a] == rnk[b]) rnk[a]++;
            sum += ed[2];
        }
        return sum;
    }
}
```

#### Edge Cases & Pitfalls
- **Disconnected graphs have no spanning tree.** Kruskal then produces a spanning forest. LeetCode 1135 expects −1, so check that exactly `V − 1` edges were taken.
- **To return the MST edges**, record each edge as it's taken: the parent in Prim's, or the edge itself in Kruskal's.

#### Key Takeaways
- Prim's grows one tree from a vertex with a heap. Kruskal's merges forests in edge order with a DSU. Both rely on the cut property and both run in O(E log E).

[↑ Contents](#contents) · [← Previous](#p375) · [Next →](#p377)

---

## Hard Problems II

<a id="p377"></a>

### 37. Number of operations to make network connected

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Hard Problems II | Core | No | [LeetCode](https://leetcode.com/problems/number-of-operations-to-make-network-connected/) | [Watch](https://youtu.be/FYrl7iz9_ZU) |

#### Problem Statement
`n` computers are linked by cables `connections[i] = [a, b]`. You may **move** a cable from one place to another. Return the minimum number of moves needed to connect all the computers, or −1 if that's impossible.

```text
n = 4, connections = [[0,1],[0,2],[1,2]]                ->  1   (cable 1-2 is redundant; use it for 3)
n = 6, connections = [[0,1],[0,2],[0,3],[1,2],[1,3]]    ->  2
n = 6, connections = [[0,1],[0,2],[0,3],[1,2]]          ->  -1
```

#### Intuition (as in the video)
- **How many cables are needed.** With `c` connected components, you need **`c − 1`** cables to join them.
- **Where they come from.** Spare cables are the **redundant** edges: those joining two computers already in the same component.
- **The rule.** If `extra ≥ c − 1`, the answer is `c − 1`; otherwise it's −1. Equivalently, it's −1 whenever there are fewer than `n − 1` cables in total.

#### Approach: DSU — count the extra edges and the components
**Complexity:** O(E·α(n) + n) time, O(n) space.

**C++**
```cpp
int findN(vector<int>& par, int x) { return par[x] == x ? x : par[x] = findN(par, par[x]); }
int makeConnected(int n, vector<vector<int>>& connections) {
    vector<int> par(n), sz(n, 1);
    iota(par.begin(), par.end(), 0);
    int extra = 0;
    for (auto& c : connections) {
        int a = findN(par, c[0]), b = findN(par, c[1]);
        if (a == b) { extra++; continue; }           // redundant cable
        if (sz[a] < sz[b]) swap(a, b);
        par[b] = a; sz[a] += sz[b];
    }
    int comps = 0;
    for (int i = 0; i < n; i++) if (findN(par, i) == i) comps++;
    return extra >= comps - 1 ? comps - 1 : -1;
}
```

**Java**
```java
class Solution {
    static int findN(int[] par, int x) { return par[x] == x ? x : (par[x] = findN(par, par[x])); }
    static int makeConnected(int n, int[][] connections) {
        int[] par = new int[n], sz = new int[n];
        for (int i = 0; i < n; i++) { par[i] = i; sz[i] = 1; }
        int extra = 0;
        for (int[] c : connections) {
            int a = findN(par, c[0]), b = findN(par, c[1]);
            if (a == b) { extra++; continue; }
            if (sz[a] < sz[b]) { int t = a; a = b; b = t; }
            par[b] = a; sz[a] += sz[b];
        }
        int comps = 0;
        for (int i = 0; i < n; i++) if (findN(par, i) == i) comps++;
        return extra >= comps - 1 ? comps - 1 : -1;
    }
}
```

#### Key Takeaways
- Connecting c components needs c − 1 edges. Redundant edges, found as unions within the same set, are the supply.

[↑ Contents](#contents) · [← Previous](#p376) · [Next →](#p378)

---

<a id="p378"></a>

### 38. Accounts merge

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Hard Problems II | Core | No | [LeetCode](https://leetcode.com/problems/accounts-merge/) | [Watch](https://youtu.be/FMwpt_aQOGw) |

#### Problem Statement
Each account is `[name, email1, email2, …]`. Two accounts belong to the same person if they share **any** email; names alone don't decide it. Merge them and return each person as `[name, sorted emails…]`.

```text
accounts = [["John","j1@m.co","j2@m.co"],["John","j3@m.co"],["John","j1@m.co","j4@m.co"],["Mary","m@m.co"]]
-> [["John","j1@m.co","j2@m.co","j4@m.co"],["John","j3@m.co"],["Mary","m@m.co"]]
```

#### Approach: DSU over account indices (as in the video)
1. **Link accounts that share an email.** Map each email to the **first account index** where it appears. When an email shows up again in account `i`, union `i` with that first index.
2. **Group the emails.** Put each email under `findUPar(owner index)`.
3. **Build the output.** For each group, sort its emails and prepend the account's name.

**Complexity:**
- Time: O(N·K·α) for N accounts with K emails each, plus O(N·K log(N·K)) for sorting.
- Space: O(N·K).

**C++**
```cpp
int findA(vector<int>& par, int x) { return par[x] == x ? x : par[x] = findA(par, par[x]); }
vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
    int n = accounts.size();
    vector<int> par(n);
    iota(par.begin(), par.end(), 0);
    unordered_map<string, int> mailNode;                       // email -> first account index
    for (int i = 0; i < n; i++)
        for (size_t j = 1; j < accounts[i].size(); j++) {
            const string& mail = accounts[i][j];
            if (!mailNode.count(mail)) mailNode[mail] = i;
            else { int a = findA(par, i), b = findA(par, mailNode[mail]); if (a != b) par[a] = b; }
        }
    vector<vector<string>> merged(n);
    for (auto& [mail, idx] : mailNode) merged[findA(par, idx)].push_back(mail);
    vector<vector<string>> ans;
    for (int i = 0; i < n; i++) {
        if (merged[i].empty()) continue;
        sort(merged[i].begin(), merged[i].end());
        vector<string> row = {accounts[i][0]};
        row.insert(row.end(), merged[i].begin(), merged[i].end());
        ans.push_back(row);
    }
    return ans;
}
```

**Java**
```java
class Solution {
    static int findA(int[] par, int x) { return par[x] == x ? x : (par[x] = findA(par, par[x])); }
    static List<List<String>> accountsMerge(List<List<String>> accounts) {
        int n = accounts.size();
        int[] par = new int[n];
        for (int i = 0; i < n; i++) par[i] = i;
        Map<String, Integer> mailNode = new HashMap<>();
        for (int i = 0; i < n; i++)
            for (int j = 1; j < accounts.get(i).size(); j++) {
                String mail = accounts.get(i).get(j);
                if (!mailNode.containsKey(mail)) mailNode.put(mail, i);
                else { int a = findA(par, i), b = findA(par, mailNode.get(mail)); if (a != b) par[a] = b; }
            }
        List<List<String>> merged = new ArrayList<>();
        for (int i = 0; i < n; i++) merged.add(new ArrayList<>());
        for (Map.Entry<String, Integer> e : mailNode.entrySet()) merged.get(findA(par, e.getValue())).add(e.getKey());
        List<List<String>> ans = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            if (merged.get(i).isEmpty()) continue;
            Collections.sort(merged.get(i));
            List<String> row = new ArrayList<>();
            row.add(accounts.get(i).get(0));
            row.addAll(merged.get(i));
            ans.add(row);
        }
        return ans;
    }
}
```

#### Key Takeaways
- To merge entities that share any attribute, use DSU over the entities, with a hash map from attribute to its first owner.

[↑ Contents](#contents) · [← Previous](#p377) · [Next →](#p379)

---

<a id="p379"></a>

### 39. Number of islands II

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Hard Problems II | Pro | Yes | [LeetCode](https://leetcode.com/problems/number-of-islands-ii/) | [Watch](https://youtu.be/Rn6B-Q4SNyA) |

#### Problem Statement
An `n × m` grid starts as all water. `operators[i] = [r, c]` turns that cell into land. After **each** operation, report the number of islands (4-directional).

```text
n = 3, m = 3, ops = [[0,0],[0,1],[1,2],[2,1]]   ->  [1, 1, 2, 3]
```

#### Approach: Online DSU on cell ids `r·m + c` (as in the video)
- **Rerunning BFS after every operation** would cost O(k·n·m). DSU makes each operation near-constant.
- **When a cell becomes land:**
  - if it's already land, just repeat the current count;
  - otherwise mark it and do `count++`, since it's a new island on its own;
  - for each **land** neighbour in a **different** set, union them and `count−−`.

**Complexity:** O(k · 4 · α(n·m)) time, O(n·m) space.

**C++**
```cpp
int findI(vector<int>& par, int x) { return par[x] == x ? x : par[x] = findI(par, par[x]); }
vector<int> numOfIslands(int n, int m, vector<vector<int>>& operators) {
    vector<int> par(n * m), sz(n * m, 1), ans;
    iota(par.begin(), par.end(), 0);
    vector<vector<int>> land(n, vector<int>(m, 0));
    int cnt = 0;
    int dr[] = {-1, 0, 1, 0}, dc[] = {0, 1, 0, -1};
    for (auto& op : operators) {
        int r = op[0], c = op[1];
        if (land[r][c]) { ans.push_back(cnt); continue; }
        land[r][c] = 1;
        cnt++;
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k], nc = c + dc[k];
            if (nr >= 0 && nr < n && nc >= 0 && nc < m && land[nr][nc]) {
                int a = findI(par, r * m + c), b = findI(par, nr * m + nc);
                if (a != b) {
                    if (sz[a] < sz[b]) swap(a, b);
                    par[b] = a; sz[a] += sz[b];
                    cnt--;                                   // two islands merged
                }
            }
        }
        ans.push_back(cnt);
    }
    return ans;
}
```

**Java**
```java
class Solution {
    static int findI(int[] par, int x) { return par[x] == x ? x : (par[x] = findI(par, par[x])); }
    static List<Integer> numOfIslands(int n, int m, int[][] operators) {
        int[] par = new int[n * m], sz = new int[n * m];
        for (int i = 0; i < n * m; i++) { par[i] = i; sz[i] = 1; }
        int[][] land = new int[n][m];
        int cnt = 0;
        int[] dr = {-1, 0, 1, 0}, dc = {0, 1, 0, -1};
        List<Integer> ans = new ArrayList<>();
        for (int[] op : operators) {
            int r = op[0], c = op[1];
            if (land[r][c] == 1) { ans.add(cnt); continue; }
            land[r][c] = 1;
            cnt++;
            for (int k = 0; k < 4; k++) {
                int nr = r + dr[k], nc = c + dc[k];
                if (nr >= 0 && nr < n && nc >= 0 && nc < m && land[nr][nc] == 1) {
                    int a = findI(par, r * m + c), b = findI(par, nr * m + nc);
                    if (a != b) {
                        if (sz[a] < sz[b]) { int t = a; a = b; b = t; }
                        par[b] = a; sz[a] += sz[b];
                        cnt--;
                    }
                }
            }
            ans.add(cnt);
        }
        return ans;
    }
}
```

#### Edge Cases & Pitfalls
- **Repeated operations** on the same cell don't change the count.

#### Key Takeaways
- Dynamic connectivity with only insertions is exactly what DSU does best. Map 2-D cells to 1-D ids with `r·m + c`.

[↑ Contents](#contents) · [← Previous](#p378) · [Next →](#p380)

---

<a id="p380"></a>

### 40. Making a large island

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Hard Problems II | Pro | No | [LeetCode](https://leetcode.com/problems/making-a-large-island/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/making-a-large-island) | [Watch](https://youtu.be/lgiz0Oup6gM) |

#### Problem Statement
In a binary grid you may change **at most one** `0` into `1`. Return the size of the largest island possible afterwards (4-directional).

```text
grid = [[1,0],[0,1]]   ->  3
grid = [[1,1],[1,0]]   ->  4
grid = [[1,1],[1,1]]   ->  4
```

#### Approach: DSU of islands with sizes, then try each 0 (as in the video)
1. **Union all existing land cells** with their land neighbours, tracking component **sizes**.
2. **Try every `0` cell.** Collect the **distinct** roots of its land neighbours in a set, so the same island isn't counted twice. The candidate is `1 + sum(size[root])`.
3. **The answer** is the maximum candidate, and also at least the largest existing island. That covers an all-1 grid, which has no zero to flip.

**Complexity:** O(n² · 4 · α) time, O(n²) space.

**C++**
```cpp
int findL(vector<int>& par, int x) { return par[x] == x ? x : par[x] = findL(par, par[x]); }
int largestIsland(vector<vector<int>>& grid) {
    int n = grid.size();
    vector<int> par(n * n), sz(n * n, 1);
    iota(par.begin(), par.end(), 0);
    int dr[] = {-1, 0, 1, 0}, dc[] = {0, 1, 0, -1};
    auto unite = [&](int a, int b) {
        a = findL(par, a); b = findL(par, b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);
        par[b] = a; sz[a] += sz[b];
    };
    for (int r = 0; r < n; r++)                              // step 1: islands
        for (int c = 0; c < n; c++) if (grid[r][c])
            for (int k = 0; k < 4; k++) {
                int nr = r + dr[k], nc = c + dc[k];
                if (nr >= 0 && nr < n && nc >= 0 && nc < n && grid[nr][nc]) unite(r * n + c, nr * n + nc);
            }
    int best = 0;
    for (int r = 0; r < n; r++)                              // step 2: flip each 0
        for (int c = 0; c < n; c++) {
            if (grid[r][c]) continue;
            set<int> roots;
            for (int k = 0; k < 4; k++) {
                int nr = r + dr[k], nc = c + dc[k];
                if (nr >= 0 && nr < n && nc >= 0 && nc < n && grid[nr][nc]) roots.insert(findL(par, nr * n + nc));
            }
            int total = 1;
            for (int root : roots) total += sz[root];
            best = max(best, total);
        }
    for (int i = 0; i < n * n; i++)                          // all-1 grid case
        if (grid[i / n][i % n]) best = max(best, sz[findL(par, i)]);
    return best;
}
```

**Java**
```java
class Solution {
    static int[] par, sz;
    static int findL(int x) { return par[x] == x ? x : (par[x] = findL(par[x])); }
    static void unite(int a, int b) {
        a = findL(a); b = findL(b);
        if (a == b) return;
        if (sz[a] < sz[b]) { int t = a; a = b; b = t; }
        par[b] = a; sz[a] += sz[b];
    }
    static int largestIsland(int[][] grid) {
        int n = grid.length;
        par = new int[n * n]; sz = new int[n * n];
        for (int i = 0; i < n * n; i++) { par[i] = i; sz[i] = 1; }
        int[] dr = {-1, 0, 1, 0}, dc = {0, 1, 0, -1};
        for (int r = 0; r < n; r++)
            for (int c = 0; c < n; c++) if (grid[r][c] == 1)
                for (int k = 0; k < 4; k++) {
                    int nr = r + dr[k], nc = c + dc[k];
                    if (nr >= 0 && nr < n && nc >= 0 && nc < n && grid[nr][nc] == 1) unite(r * n + c, nr * n + nc);
                }
        int best = 0;
        for (int r = 0; r < n; r++)
            for (int c = 0; c < n; c++) {
                if (grid[r][c] == 1) continue;
                Set<Integer> roots = new HashSet<>();
                for (int k = 0; k < 4; k++) {
                    int nr = r + dr[k], nc = c + dc[k];
                    if (nr >= 0 && nr < n && nc >= 0 && nc < n && grid[nr][nc] == 1) roots.add(findL(nr * n + nc));
                }
                int total = 1;
                for (int root : roots) total += sz[root];
                best = Math.max(best, total);
            }
        for (int i = 0; i < n * n; i++)
            if (grid[i / n][i % n] == 1) best = Math.max(best, sz[findL(i)]);
        return best;
    }
}
```

#### Key Takeaways
- Precompute the components once, then evaluate each candidate flip in O(1), de-duplicating neighbouring components with a set.

[↑ Contents](#contents) · [← Previous](#p379) · [Next →](#p381)

---

<a id="p381"></a>

### 41. Most stones removed with same row or column

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Hard Problems II | Pro | No | [LeetCode](https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/most-stones-removed-same-row-column) | [Watch](https://youtu.be/OwMNX8SPavM) |

#### Problem Statement
Stones sit at integer points `stones[i] = [x, y]`. A stone can be removed if another remaining stone shares its **row or column**. Return the maximum number of stones that can be removed.

```text
stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]   ->  5
stones = [[0,0],[0,2],[1,1],[2,0],[2,2]]         ->  3
```

#### Intuition (as in the video)
- **Components.** Stones connected through shared rows and columns form a component.
- **Each component can shrink to one stone.** Removing stones in a suitable order, e.g. reverse DFS order, leaves exactly one per component.
- **So the answer is `n − (number of components)`.**

#### Approach: DSU over rows and columns as nodes
- **Union the row with the column.** Treat row `x` as node `x` and column `y` as node `maxRow + 1 + y`. Each stone unions its row with its column.
- **Count components among the used nodes only.** These are the rows and columns that actually contain a stone.

**Complexity:** O(n·α) time, O(maxRow + maxCol) space.

**C++**
```cpp
int findS(vector<int>& par, int x) { return par[x] == x ? x : par[x] = findS(par, par[x]); }
int removeStones(vector<vector<int>>& stones) {
    int maxRow = 0, maxCol = 0;
    for (auto& s : stones) { maxRow = max(maxRow, s[0]); maxCol = max(maxCol, s[1]); }
    int total = maxRow + maxCol + 2;
    vector<int> par(total);
    iota(par.begin(), par.end(), 0);
    unordered_set<int> used;
    for (auto& s : stones) {
        int r = s[0], c = maxRow + 1 + s[1];
        int a = findS(par, r), b = findS(par, c);
        if (a != b) par[a] = b;
        used.insert(r); used.insert(c);
    }
    int comps = 0;
    for (int node : used) if (findS(par, node) == node) comps++;
    return (int)stones.size() - comps;
}
```

**Java**
```java
class Solution {
    static int findS(int[] par, int x) { return par[x] == x ? x : (par[x] = findS(par, par[x])); }
    static int removeStones(int[][] stones) {
        int maxRow = 0, maxCol = 0;
        for (int[] s : stones) { maxRow = Math.max(maxRow, s[0]); maxCol = Math.max(maxCol, s[1]); }
        int total = maxRow + maxCol + 2;
        int[] par = new int[total];
        for (int i = 0; i < total; i++) par[i] = i;
        Set<Integer> used = new HashSet<>();
        for (int[] s : stones) {
            int r = s[0], c = maxRow + 1 + s[1];
            int a = findS(par, r), b = findS(par, c);
            if (a != b) par[a] = b;
            used.add(r); used.add(c);
        }
        int comps = 0;
        for (int node : used) if (findS(par, node) == node) comps++;
        return stones.length - comps;
    }
}
```

#### Key Takeaways
- Make rows and columns the nodes and stones the edges. The answer is `stones − components`, a neat DSU modelling trick.

[↑ Contents](#contents) · [← Previous](#p380) · [Next →](#p382)

---

## Additional Algorithms

<a id="p382"></a>

### 42. Kosaraju's algorithm

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Additional Algorithms | Pro | Yes | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/kosarajus-algorithm) | [Watch](https://youtu.be/V8qIqJxCioo) |

#### Problem Statement
Find the number of **strongly connected components (SCCs)** of a directed graph. An SCC is a maximal set of vertices in which every vertex can reach every other.

```text
V = 5, edges: 1->0, 0->2, 2->1, 0->3, 3->4   ->  3   ({0,1,2}, {3}, {4})
```

#### Approach: Kosaraju's algorithm (as in the video)
1. **Order by finish time.** DFS the whole graph and push vertices onto a stack when they **finish**. The vertex on top belongs to a "source" SCC.
2. **Reverse every edge.** This keeps the SCCs intact but turns the edges **between** SCCs around, so a DFS can no longer leak from one SCC into another.
3. **Count the trees.** Pop vertices in stack order. Each unvisited one starts a DFS on the reversed graph, and that DFS visits exactly one SCC.

**Complexity:** O(V + E) time, O(V + E) space.

**C++**
```cpp
void dfsOrder(int node, vector<vector<int>>& adj, vector<int>& vis, stack<int>& st) {
    vis[node] = 1;
    for (int it : adj[node]) if (!vis[it]) dfsOrder(it, adj, vis, st);
    st.push(node);                                     // push on finish
}
void dfsRev(int node, vector<vector<int>>& radj, vector<int>& vis) {
    vis[node] = 1;
    for (int it : radj[node]) if (!vis[it]) dfsRev(it, radj, vis);
}
int kosaraju(int V, vector<vector<int>>& adj) {
    vector<int> vis(V, 0);
    stack<int> st;
    for (int i = 0; i < V; i++) if (!vis[i]) dfsOrder(i, adj, vis, st);
    vector<vector<int>> radj(V);
    for (int u = 0; u < V; u++) for (int v : adj[u]) radj[v].push_back(u);   // reverse edges
    fill(vis.begin(), vis.end(), 0);
    int scc = 0;
    while (!st.empty()) {
        int node = st.top(); st.pop();
        if (!vis[node]) { scc++; dfsRev(node, radj, vis); }
    }
    return scc;
}
```

**Java**
```java
class Solution {
    static void dfsOrder(int node, List<List<Integer>> adj, int[] vis, Deque<Integer> st) {
        vis[node] = 1;
        for (int it : adj.get(node)) if (vis[it] == 0) dfsOrder(it, adj, vis, st);
        st.push(node);
    }
    static void dfsRev(int node, List<List<Integer>> radj, int[] vis) {
        vis[node] = 1;
        for (int it : radj.get(node)) if (vis[it] == 0) dfsRev(it, radj, vis);
    }
    static int kosaraju(int V, List<List<Integer>> adj) {
        int[] vis = new int[V];
        Deque<Integer> st = new ArrayDeque<>();
        for (int i = 0; i < V; i++) if (vis[i] == 0) dfsOrder(i, adj, vis, st);
        List<List<Integer>> radj = new ArrayList<>();
        for (int i = 0; i < V; i++) radj.add(new ArrayList<>());
        for (int u = 0; u < V; u++) for (int v : adj.get(u)) radj.get(v).add(u);
        Arrays.fill(vis, 0);
        int scc = 0;
        while (!st.isEmpty()) {
            int node = st.pop();
            if (vis[node] == 0) { scc++; dfsRev(node, radj, vis); }
        }
        return scc;
    }
}
```

#### Key Takeaways
- Kosaraju: finish-time order, then the reversed graph, then one DFS per SCC. Tarjan's algorithm finds SCCs in a single pass using low-links.

[↑ Contents](#contents) · [← Previous](#p381) · [Next →](#p383)

---

<a id="p383"></a>

### 43. Bridges in graph

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Additional Algorithms | Pro | No | [LeetCode](https://leetcode.com/problems/critical-connections-in-a-network/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/bridges-in-graph-tarjan-algorithm) | [Watch](https://youtu.be/qrAub5z8FeA) |

#### Problem Statement
A **bridge** (critical connection) is an edge whose removal **disconnects** the graph. Return all bridges of an undirected graph.

```text
n = 4, connections = [[0,1],[1,2],[2,0],[1,3]]   ->  [[1,3]]
```

#### Approach: DFS with insertion time `tin` and lowest reachable time `low` (as in the video, Tarjan)
- **`tin[u]`** is the DFS discovery time of `u`.
- **`low[u]`** is the minimum `tin` reachable from `u`'s subtree using **at most one back edge**, excluding the edge to its parent.
- **Updating `low`:**
  - after visiting a child `v`: `low[u] = min(low[u], low[v])`;
  - for a visited neighbour other than the parent: `low[u] = min(low[u], low[v])`.
- **The bridge test.** Edge `u–v`, with `v` a child, is a **bridge** iff `low[v] > tin[u]`. Nothing in `v`'s subtree can reach `u` or above without using that edge.

**Complexity:** O(V + 2E) time, O(V + E) space.

**C++**
```cpp
void dfsBridge(int node, int parent, vector<vector<int>>& adj, vector<int>& vis, vector<int>& tin,
               vector<int>& low, int& timer, vector<vector<int>>& bridges) {
    vis[node] = 1;
    tin[node] = low[node] = timer++;
    for (int it : adj[node]) {
        if (it == parent) continue;
        if (!vis[it]) {
            dfsBridge(it, node, adj, vis, tin, low, timer, bridges);
            low[node] = min(low[node], low[it]);
            if (low[it] > tin[node]) bridges.push_back({node, it});   // no way back around
        } else {
            low[node] = min(low[node], low[it]);
        }
    }
}
vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
    vector<vector<int>> adj(n);
    for (auto& c : connections) { adj[c[0]].push_back(c[1]); adj[c[1]].push_back(c[0]); }
    vector<int> vis(n, 0), tin(n), low(n);
    vector<vector<int>> bridges;
    int timer = 1;
    for (int i = 0; i < n; i++) if (!vis[i]) dfsBridge(i, -1, adj, vis, tin, low, timer, bridges);
    return bridges;
}
```

**Java**
```java
class Solution {
    static int timer;
    static void dfsBridge(int node, int parent, List<List<Integer>> adj, int[] vis, int[] tin, int[] low,
                          List<List<Integer>> bridges) {
        vis[node] = 1;
        tin[node] = low[node] = timer++;
        for (int it : adj.get(node)) {
            if (it == parent) continue;
            if (vis[it] == 0) {
                dfsBridge(it, node, adj, vis, tin, low, bridges);
                low[node] = Math.min(low[node], low[it]);
                if (low[it] > tin[node]) bridges.add(Arrays.asList(node, it));
            } else {
                low[node] = Math.min(low[node], low[it]);
            }
        }
    }
    static List<List<Integer>> criticalConnections(int n, List<List<Integer>> connections) {
        List<List<Integer>> adj = new ArrayList<>();
        for (int i = 0; i < n; i++) adj.add(new ArrayList<>());
        for (List<Integer> c : connections) { adj.get(c.get(0)).add(c.get(1)); adj.get(c.get(1)).add(c.get(0)); }
        int[] vis = new int[n], tin = new int[n], low = new int[n];
        List<List<Integer>> bridges = new ArrayList<>();
        timer = 1;
        for (int i = 0; i < n; i++) if (vis[i] == 0) dfsBridge(i, -1, adj, vis, tin, low, bridges);
        return bridges;
    }
}
```

#### Edge Cases & Pitfalls
- **Skip only the parent.** If the graph can have parallel edges, skip only the specific parent **edge**, not every edge to the parent vertex.

#### Key Takeaways
- Bridge ⇔ `low[child] > tin[parent]`: the child's subtree has no back edge reaching above the parent.

[↑ Contents](#contents) · [← Previous](#p382) · [Next →](#p384)

---

<a id="p384"></a>

### 44. Articulation point in graph

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Graphs › Additional Algorithms | Pro | Yes | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/articulation-points-in-graph) | [Watch](https://youtu.be/j1QDfU21iZk) |

#### Problem Statement
An **articulation point** is a vertex whose removal (with its edges) increases the number of connected components. Return all of them in sorted order, or `[-1]` if there are none.

```text
V = 5, edges: 0-1, 1-4, 4-2, 2-3, 3-4   ->  [1, 4]
```

#### Approach: Tarjan's `tin` / `low`, with a vertex condition (as in the video)
- **The low-link update differs from bridges.** For a visited non-parent neighbour, use `low[u] = min(low[u], tin[v])`, i.e. `tin`, not `low`.
- **A non-root `u` is an articulation point** if some child `v` has `low[v] ≥ tin[u]`. Then `v`'s subtree can't reach above `u` without going through `u`.
- **The DFS root is an articulation point** iff it has **more than one** DFS child.
- **Collect them in a mark array**, because a vertex can satisfy the condition for several children.

**Complexity:** O(V + 2E) time, O(V) space.

**C++**
```cpp
void dfsAP(int node, int parent, vector<vector<int>>& adj, vector<int>& vis, vector<int>& tin,
           vector<int>& low, vector<int>& mark, int& timer) {
    vis[node] = 1;
    tin[node] = low[node] = timer++;
    int child = 0;
    for (int it : adj[node]) {
        if (it == parent) continue;
        if (!vis[it]) {
            dfsAP(it, node, adj, vis, tin, low, mark, timer);
            low[node] = min(low[node], low[it]);
            if (low[it] >= tin[node] && parent != -1) mark[node] = 1;
            child++;
        } else {
            low[node] = min(low[node], tin[it]);            // tin, not low
        }
    }
    if (parent == -1 && child > 1) mark[node] = 1;          // root rule
}
vector<int> articulationPoints(int V, vector<vector<int>>& adj) {
    vector<int> vis(V, 0), tin(V), low(V), mark(V, 0), ans;
    int timer = 0;
    for (int i = 0; i < V; i++) if (!vis[i]) dfsAP(i, -1, adj, vis, tin, low, mark, timer);
    for (int i = 0; i < V; i++) if (mark[i]) ans.push_back(i);
    if (ans.empty()) return {-1};
    return ans;
}
```

**Java**
```java
class Solution {
    static int timerAP;
    static void dfsAP(int node, int parent, List<List<Integer>> adj, int[] vis, int[] tin, int[] low, int[] mark) {
        vis[node] = 1;
        tin[node] = low[node] = timerAP++;
        int child = 0;
        for (int it : adj.get(node)) {
            if (it == parent) continue;
            if (vis[it] == 0) {
                dfsAP(it, node, adj, vis, tin, low, mark);
                low[node] = Math.min(low[node], low[it]);
                if (low[it] >= tin[node] && parent != -1) mark[node] = 1;
                child++;
            } else {
                low[node] = Math.min(low[node], tin[it]);
            }
        }
        if (parent == -1 && child > 1) mark[node] = 1;
    }
    static List<Integer> articulationPoints(int V, List<List<Integer>> adj) {
        int[] vis = new int[V], tin = new int[V], low = new int[V], mark = new int[V];
        timerAP = 0;
        for (int i = 0; i < V; i++) if (vis[i] == 0) dfsAP(i, -1, adj, vis, tin, low, mark);
        List<Integer> ans = new ArrayList<>();
        for (int i = 0; i < V; i++) if (mark[i] == 1) ans.add(i);
        if (ans.isEmpty()) ans.add(-1);
        return ans;
    }
}
```

#### Edge Cases & Pitfalls
- **Bridges versus articulation points.** Bridges use `>` and `low[v]`. Articulation points use `≥` and `tin[v]` for back edges, plus the special rule for the root.

#### Key Takeaways
- Articulation point: some child's subtree can't climb above `u` (`low[child] ≥ tin[u]`). The root qualifies only with two or more DFS children.

[↑ Contents](#contents) · [← Previous](#p383)

---
