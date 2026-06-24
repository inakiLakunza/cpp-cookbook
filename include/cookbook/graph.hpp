#pragma once

#include <unordered_map>
#include <vector>

namespace cookbook::graph {

using AdjacencyList = std::unordered_map<int, std::vector<int>>;

// Returns the BFS traversal order starting from start.
std::vector<int> bfs(const AdjacencyList& graph, int start);

// Returns the recursive DFS traversal order starting from start.
std::vector<int> dfsRecursive(const AdjacencyList& graph, int start);

// Returns the iterative DFS traversal order starting from start.
std::vector<int> dfsIterative(const AdjacencyList& graph, int start);

// Returns true if there is a path from source to target.
bool hasPath(const AdjacencyList& graph, int source, int target);

// Returns the shortest path from source to target in an unweighted graph, or an empty vector if no path exists.
std::vector<int> shortestPathUnweighted(
    const AdjacencyList& graph,
    int source,
    int target
);

// Returns all connected components of an undirected graph.
std::vector<std::vector<int>> connectedComponents(const AdjacencyList& graph);

}  // namespace cookbook::graph