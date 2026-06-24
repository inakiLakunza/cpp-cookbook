#include "cookbook/graph.hpp"

#include <iostream>
#include <vector>

namespace {

void printVector(const std::vector<int>& values) {
    std::cout << "{ ";

    for (int value : values) {
        std::cout << value << " ";
    }

    std::cout << "}";
}

void printComponents(const std::vector<std::vector<int>>& components) {
    std::cout << "{\n";

    for (const std::vector<int>& component : components) {
        std::cout << "  ";
        printVector(component);
        std::cout << "\n";
    }

    std::cout << "}";
}

}  // namespace

int main() {
    cookbook::graph::AdjacencyList graph = {
        {0, {1, 2}},
        {1, {0, 3}},
        {2, {0}},
        {3, {1}},
        {4, {5}},
        {5, {4}},
        {6, {}}
    };

    std::cout << "BFS from 0: ";
    printVector(cookbook::graph::bfs(graph, 0));
    std::cout << "\n";

    std::cout << "DFS recursive from 0: ";
    printVector(cookbook::graph::dfsRecursive(graph, 0));
    std::cout << "\n";

    std::cout << "DFS iterative from 0: ";
    printVector(cookbook::graph::dfsIterative(graph, 0));
    std::cout << "\n";

    std::cout << "Has path 0 -> 3: "
              << cookbook::graph::hasPath(graph, 0, 3)
              << "\n";

    std::cout << "Has path 0 -> 5: "
              << cookbook::graph::hasPath(graph, 0, 5)
              << "\n";

    std::cout << "Shortest path 0 -> 3: ";
    printVector(cookbook::graph::shortestPathUnweighted(graph, 0, 3));
    std::cout << "\n";

    std::cout << "Connected components:\n";
    printComponents(cookbook::graph::connectedComponents(graph));
    std::cout << "\n";

    return 0;
}