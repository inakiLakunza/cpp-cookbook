#include "cookbook/graph.hpp"

#include <algorithm>
#include <queue>
#include <unordered_set>

namespace cookbook::graph {

namespace {

bool nodeExists(const AdjacencyList& graph, int node) {
    if (graph.find(node) != graph.end()) {
        return true;
    }

    for (const auto& entry : graph) {
        const std::vector<int>& neighbors = entry.second;

        if (std::find(neighbors.begin(), neighbors.end(), node) != neighbors.end()) {
            return true;
        }
    }

    return false;
}

void dfsRecursiveHelper(
    const AdjacencyList& graph,
    int node,
    std::unordered_set<int>& visited,
    std::vector<int>& order
) {
    visited.insert(node);
    order.push_back(node);

    const auto it = graph.find(node);
    if (it == graph.end()) {
        return;
    }

    for (int neighbor : it->second) {
        if (visited.find(neighbor) == visited.end()) {
            dfsRecursiveHelper(graph, neighbor, visited, order);
        }
    }
}

std::vector<int> getAllNodesSorted(const AdjacencyList& graph) {
    std::unordered_set<int> seen;

    for (const auto& entry : graph) {
        seen.insert(entry.first);

        for (int neighbor : entry.second) {
            seen.insert(neighbor);
        }
    }

    std::vector<int> nodes(seen.begin(), seen.end());
    std::sort(nodes.begin(), nodes.end());

    return nodes;
}

}  // namespace

std::vector<int> bfs(const AdjacencyList& graph, int start) {
    std::vector<int> order;

    if (!nodeExists(graph, start)) {
        return order;
    }

    std::queue<int> queue;
    std::unordered_set<int> visited;

    queue.push(start);
    visited.insert(start);

    while (!queue.empty()) {
        int node = queue.front();
        queue.pop();

        order.push_back(node);

        const auto it = graph.find(node);
        if (it == graph.end()) {
            continue;
        }

        for (int neighbor : it->second) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                queue.push(neighbor);
            }
        }
    }

    return order;
}

std::vector<int> dfsRecursive(const AdjacencyList& graph, int start) {
    std::vector<int> order;

    if (!nodeExists(graph, start)) {
        return order;
    }

    std::unordered_set<int> visited;
    dfsRecursiveHelper(graph, start, visited, order);

    return order;
}

std::vector<int> dfsIterative(const AdjacencyList& graph, int start) {
    std::vector<int> order;

    if (!nodeExists(graph, start)) {
        return order;
    }

    std::vector<int> stack;
    std::unordered_set<int> visited;

    stack.push_back(start);

    while (!stack.empty()) {
        int node = stack.back();
        stack.pop_back();

        if (visited.find(node) != visited.end()) {
            continue;
        }

        visited.insert(node);
        order.push_back(node);

        const auto it = graph.find(node);
        if (it == graph.end()) {
            continue;
        }

        // Push in reverse order so the final traversal matches recursive DFS order.
        for (auto rit = it->second.rbegin(); rit != it->second.rend(); ++rit) {
            if (visited.find(*rit) == visited.end()) {
                stack.push_back(*rit);
            }
        }
    }

    return order;
}

bool hasPath(const AdjacencyList& graph, int source, int target) {
    if (!nodeExists(graph, source) || !nodeExists(graph, target)) {
        return false;
    }

    if (source == target) {
        return true;
    }

    std::queue<int> queue;
    std::unordered_set<int> visited;

    queue.push(source);
    visited.insert(source);

    while (!queue.empty()) {
        int node = queue.front();
        queue.pop();

        if (node == target) {
            return true;
        }

        const auto it = graph.find(node);
        if (it == graph.end()) {
            continue;
        }

        for (int neighbor : it->second) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                queue.push(neighbor);
            }
        }
    }

    return false;
}

std::vector<int> shortestPathUnweighted(
    const AdjacencyList& graph,
    int source,
    int target
) {
    std::vector<int> path;

    if (!nodeExists(graph, source) || !nodeExists(graph, target)) {
        return path;
    }

    if (source == target) {
        return {source};
    }

    std::queue<int> queue;
    std::unordered_set<int> visited;
    std::unordered_map<int, int> parent;

    queue.push(source);
    visited.insert(source);
    parent[source] = source;

    bool found = false;

    while (!queue.empty() && !found) {
        int node = queue.front();
        queue.pop();

        const auto it = graph.find(node);
        if (it == graph.end()) {
            continue;
        }

        for (int neighbor : it->second) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                parent[neighbor] = node;
                queue.push(neighbor);

                if (neighbor == target) {
                    found = true;
                    break;
                }
            }
        }
    }

    if (!found) {
        return {};
    }

    int current = target;

    while (current != source) {
        path.push_back(current);
        current = parent[current];
    }

    path.push_back(source);
    std::reverse(path.begin(), path.end());

    return path;
}

std::vector<std::vector<int>> connectedComponents(const AdjacencyList& graph) {
    std::vector<std::vector<int>> components;
    std::unordered_set<int> visited;

    const std::vector<int> nodes = getAllNodesSorted(graph);

    for (int start : nodes) {
        if (visited.find(start) != visited.end()) {
            continue;
        }

        std::vector<int> component;
        std::queue<int> queue;

        queue.push(start);
        visited.insert(start);

        while (!queue.empty()) {
            int node = queue.front();
            queue.pop();

            component.push_back(node);

            const auto it = graph.find(node);
            if (it == graph.end()) {
                continue;
            }

            for (int neighbor : it->second) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    queue.push(neighbor);
                }
            }
        }

        components.push_back(component);
    }

    return components;
}

}  // namespace cookbook::graph