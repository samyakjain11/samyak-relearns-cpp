# Graph cheat sheet (C++): topo sort, cycles, connectivity

Algorithms are written as steps, not code, so you still get to write them yourself.

## Building the graph
```cpp
vector<vector<int>> adj(n);                  // adjacency list, the default
for (auto& e : edges) {                      // e = {u, v}
    adj[e[0]].push_back(e[1]);               // directed u -> v
    // adj[e[1]].push_back(e[0]);            // add this too if undirected
}
vector<int> indeg(n);                        // for Kahn's: ++indeg[v] per edge
```
- Read the edge direction carefully. In Course Schedule, `[a, b]` means b must come **before** a, so the edge is b -> a.
- Grid problems: the cells are the nodes. Use `int dr[] = {-1,1,0,0}, dc[] = {0,0,-1,1};` and check bounds before you index.
- Recursive DFS on 10^5 nodes can overflow the stack. Say this out loud in an interview, and switch to an explicit stack if needed.

## BFS vs DFS
- **BFS** (queue): shortest path in an **unweighted** graph, and level-by-level work. Mark a node visited when you **push** it, not when you pop it, or it gets pushed twice.
- **DFS** (recursion or a stack): reachability, components, cycles, topo order and anything about the "finish time".
- Both are O(V + E).

## Topological sort (DAG only)
**Kahn's algorithm (BFS on in-degrees)**
1. Compute the in-degree of every node.
2. Push every node with in-degree 0 into a queue.
3. Pop a node, append it to the order, and decrement each neighbour's in-degree. If a neighbour drops to 0, push it.
4. If the order has fewer than V nodes, there is a **cycle**. The nodes that never got to 0 are on or behind a cycle.

**DFS post-order**
- Add a node to the list **after** all its descendants finish. Reversing that list gives a topological order.
- You need cycle detection (below) alongside it, or it will quietly return garbage when there is a cycle.

Kahn's is usually easier to get right under pressure, and the cycle check comes free.

## Cycle detection
| Graph | Method | Idea |
|---|---|---|
| Directed | DFS with 3 colors | white = unvisited, gray = on the current path, black = done. An edge to a **gray** node is a cycle. |
| Directed | Kahn's | processed count < V means there is a cycle |
| Undirected | DFS + parent | a visited neighbour that **isn't your parent** means a cycle |
| Undirected | Union-find | an edge whose two ends already have the same root means a cycle |

- Why two colors aren't enough for directed graphs: a black node you reach again through a different path isn't a cycle. Only "still on my current path" (gray) counts.
- Black nodes are proven to have no cycle reachable from them. That's the whole idea behind "eventual safe states".

## Connectivity
- **Connected components (undirected)**: loop over all nodes, and start a DFS or BFS from each unvisited one. The number of starts is the number of components.
- **Union-find (DSU)**: an array `parent[i]`. `find` walks up to the root, and `unite` links one root under another.
  - Path compression in `find` (point nodes straight at the root), plus union by size or rank, gives near-O(1) per operation (inverse Ackermann).
  - It's best when edges arrive one at a time, or you only care about "same group?", not paths.
- **Strongly connected components (directed)**: u and v are in the same SCC if each can reach the other.
  - *Kosaraju*: run DFS and record nodes by finish time. Then reverse every edge and run DFS in decreasing finish time. Each tree in the second pass is one SCC.
  - *Tarjan*: one DFS with `disc[u]` (discovery time) and `low[u]` (the earliest discovery time reachable from u's subtree using one back edge). u is the root of an SCC when `low[u] == disc[u]`.
- **Bridges / critical edges (undirected)**: the same disc/low idea. The tree edge u -> v is a bridge if `low[v] > disc[u]`, which means v's subtree can't get back above u without that edge.

## Complexity to say out loud
- Adjacency list: O(V + E) space. Matrix: O(V^2), and it's only worth it for dense graphs.
- BFS, DFS, topo sort, SCC and bridges: O(V + E).
- Union-find over E edges: O(E α(V)), which is effectively O(E).

## Problems → tool
- 207 / 210 Course Schedule I, II → topo sort, and cycle = impossible
- 547 Number of Provinces → components (DFS or DSU, so try both)
- 802 Find Eventual Safe States → 3-color DFS (or Kahn's on the reversed graph)
- 1192 Critical Connections → bridges with disc/low

## Reading
- cp-algorithms: [Topological sort](https://cp-algorithms.com/graph/topological-sort.html), [Finding cycles](https://cp-algorithms.com/graph/finding-cycle.html), [DSU](https://cp-algorithms.com/data_structures/disjoint_set_union.html), [SCC](https://cp-algorithms.com/graph/strongly-connected-components.html), [Bridges](https://cp-algorithms.com/graph/bridge-searching.html)
- Tech Interview Handbook: [Graph cheatsheet](https://www.techinterviewhandbook.org/algorithms/graph/)
