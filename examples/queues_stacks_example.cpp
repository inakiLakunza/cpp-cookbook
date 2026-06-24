#include "cookbook/queues_stacks.hpp"

#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>

namespace {

void printVector(const std::vector<int>& values) {
    std::cout << "[";

    for (std::size_t i = 0; i < values.size(); ++i) {
        std::cout << values[i];

        if (i + 1 < values.size()) {
            std::cout << ", ";
        }
    }

    std::cout << "]\n";
}

void printStrings(const std::vector<std::string>& values) {
    std::cout << "[";

    for (std::size_t i = 0; i < values.size(); ++i) {
        std::cout << values[i];

        if (i + 1 < values.size()) {
            std::cout << ", ";
        }
    }

    std::cout << "]\n";
}

}  // namespace

int main() {
    namespace qs = cookbook::queues_stacks;

    std::queue<int> queueValues;
    queueValues.push(1);
    queueValues.push(2);
    queueValues.push(3);

    std::cout << "Process queue FIFO: ";
    printVector(qs::processQueue(queueValues));
    // Expected: [1, 2, 3]

    std::queue<int> reversedQueue = qs::reverseQueue(queueValues);

    std::cout << "Reversed queue: ";
    printVector(qs::queueToVector(reversedQueue));
    // Expected: [3, 2, 1]

    std::stack<int> stackValues;
    stackValues.push(10);
    stackValues.push(20);
    stackValues.push(30);

    std::cout << "Stack to vector top-to-bottom: ";
    printVector(qs::stackToVector(stackValues));
    // Expected: [30, 20, 10]

    std::cout << "Balanced parentheses: "
              << qs::isBalancedParentheses("{[()]}") << "\n";
    // Expected: 1

    std::vector<int> values{2, 1, 5, 3, 4};

    std::cout << "Next greater elements: ";
    printVector(qs::nextGreaterElements(values));
    // Expected: [5, 5, -1, 4, -1]

    std::vector<int> windowValues{1, 3, -1, -3, 5, 3, 6, 7};

    std::cout << "Sliding window maximum, k=3: ";
    printVector(qs::slidingWindowMaximum(windowValues, 3));
    // Expected: [3, 3, 5, 5, 6, 7]

    std::cout << "Sliding window minimum, k=3: ";
    printVector(qs::slidingWindowMinimum(windowValues, 3));
    // Expected: [-1, -3, -3, -3, 3, 3]

    std::vector<int> heapValues{4, 1, 9, 2, 7};

    std::cout << "Max heap pop order: ";
    printVector(qs::priorityQueueMaxHeapExample(heapValues));
    // Expected: [9, 7, 4, 2, 1]

    std::cout << "Min heap pop order: ";
    printVector(qs::priorityQueueMinHeapExample(heapValues));
    // Expected: [1, 2, 4, 7, 9]

    std::vector<qs::Task> tasks{
        {2, "write docs"},
        {9, "fix production bug"},
        {5, "review PR"},
        {9, "investigate outage"}
    };

    std::cout << "Tasks by priority: ";
    printStrings(qs::processTasksByPriority(tasks));
    // Expected: [fix production bug, investigate outage, review PR, write docs]

    std::cout << "Top 3 smallest: ";
    printVector(qs::keepTopKSmallest(heapValues, 3));
    // Expected: [1, 2, 4]

    std::cout << "Top 3 largest: ";
    printVector(qs::keepTopKLargest(heapValues, 3));
    // Expected: [9, 7, 4]

    return 0;
}