#pragma once

#include <cstddef>
#include <queue>
#include <stack>
#include <string>
#include <vector>

namespace cookbook::queues_stacks {

struct Task {
    int priority;
    std::string name;
};

// Processes a queue in FIFO order and returns the values in the order they were processed.
std::vector<int> processQueue(std::queue<int> values);

// Reverses a queue using stack behavior.
std::queue<int> reverseQueue(std::queue<int> values);

// Converts a queue to a vector in FIFO order.
std::vector<int> queueToVector(std::queue<int> values);

// Converts a stack to a vector in top-to-bottom pop order.
std::vector<int> stackToVector(std::stack<int> values);

// Checks whether (), [], and {} are balanced and correctly nested.
bool isBalancedParentheses(const std::string& text);

// Returns the next greater value to the right for each value, or -1 if none exists.
std::vector<int> nextGreaterElements(const std::vector<int>& values);

// Returns the maximum value in every contiguous window of size windowSize.
std::vector<int> slidingWindowMaximum(
    const std::vector<int>& values,
    std::size_t windowSize
);

// Returns the minimum value in every contiguous window of size windowSize.
std::vector<int> slidingWindowMinimum(
    const std::vector<int>& values,
    std::size_t windowSize
);

// Demonstrates a max-heap priority queue by returning values from largest to smallest.
std::vector<int> priorityQueueMaxHeapExample(const std::vector<int>& values);

// Demonstrates a min-heap priority queue by returning values from smallest to largest.
std::vector<int> priorityQueueMinHeapExample(const std::vector<int>& values);

// Processes tasks by descending priority, preserving input order when priorities tie.
std::vector<std::string> processTasksByPriority(const std::vector<Task>& tasks);

// Keeps the k smallest values and returns them sorted from smallest to largest.
std::vector<int> keepTopKSmallest(const std::vector<int>& values, std::size_t k);

// Keeps the k largest values and returns them sorted from largest to smallest.
std::vector<int> keepTopKLargest(const std::vector<int>& values, std::size_t k);

// Returns the maximum value in every window using a monotonic queue.
std::vector<int> monotonicQueueMaximum(
    const std::vector<int>& values,
    std::size_t windowSize
);

}  // namespace cookbook::queues_stacks