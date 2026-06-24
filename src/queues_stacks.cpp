#include "cookbook/queues_stacks.hpp"

#include <algorithm>
#include <deque>
#include <functional>
#include <queue>
#include <stack>
#include <string>
#include <vector>

namespace cookbook::queues_stacks {
namespace {

bool isOpeningBracket(char c) {
    return c == '(' || c == '[' || c == '{';
}

bool isClosingBracket(char c) {
    return c == ')' || c == ']' || c == '}';
}

char matchingOpeningBracket(char closing) {
    if (closing == ')') {
        return '(';
    }

    if (closing == ']') {
        return '[';
    }

    if (closing == '}') {
        return '{';
    }

    return '\0';
}

struct QueuedTask {
    int priority;
    std::size_t inputOrder;
    std::string name;
};

struct CompareQueuedTask {
    bool operator()(const QueuedTask& a, const QueuedTask& b) const {
        if (a.priority == b.priority) {
            return a.inputOrder > b.inputOrder;
        }

        return a.priority < b.priority;
    }
};

}  // namespace

std::vector<int> processQueue(std::queue<int> values) {
    std::vector<int> processed;

    while (!values.empty()) {
        processed.push_back(values.front());
        values.pop();
    }

    return processed;
}

std::queue<int> reverseQueue(std::queue<int> values) {
    std::stack<int> temporary;

    while (!values.empty()) {
        temporary.push(values.front());
        values.pop();
    }

    std::queue<int> reversed;

    while (!temporary.empty()) {
        reversed.push(temporary.top());
        temporary.pop();
    }

    return reversed;
}

std::vector<int> queueToVector(std::queue<int> values) {
    std::vector<int> result;

    while (!values.empty()) {
        result.push_back(values.front());
        values.pop();
    }

    return result;
}

std::vector<int> stackToVector(std::stack<int> values) {
    std::vector<int> result;

    while (!values.empty()) {
        result.push_back(values.top());
        values.pop();
    }

    return result;
}

bool isBalancedParentheses(const std::string& text) {
    std::stack<char> openBrackets;

    for (char c : text) {
        if (isOpeningBracket(c)) {
            openBrackets.push(c);
        } else if (isClosingBracket(c)) {
            if (openBrackets.empty()) {
                return false;
            }

            if (openBrackets.top() != matchingOpeningBracket(c)) {
                return false;
            }

            openBrackets.pop();
        }
    }

    return openBrackets.empty();
}

std::vector<int> nextGreaterElements(const std::vector<int>& values) {
    std::vector<int> result(values.size(), -1);
    std::stack<std::size_t> indexes;

    for (std::size_t i = 0; i < values.size(); ++i) {
        while (!indexes.empty() && values[i] > values[indexes.top()]) {
            result[indexes.top()] = values[i];
            indexes.pop();
        }

        indexes.push(i);
    }

    return result;
}

std::vector<int> monotonicQueueMaximum(
    const std::vector<int>& values,
    std::size_t windowSize
) {
    if (values.empty() || windowSize == 0 || windowSize > values.size()) {
        return {};
    }

    std::vector<int> result;
    std::deque<std::size_t> candidates;

    for (std::size_t i = 0; i < values.size(); ++i) {
        while (!candidates.empty() && candidates.front() + windowSize <= i) {
            candidates.pop_front();
        }

        while (!candidates.empty() && values[candidates.back()] <= values[i]) {
            candidates.pop_back();
        }

        candidates.push_back(i);

        if (i + 1 >= windowSize) {
            result.push_back(values[candidates.front()]);
        }
    }

    return result;
}

std::vector<int> slidingWindowMaximum(
    const std::vector<int>& values,
    std::size_t windowSize
) {
    return monotonicQueueMaximum(values, windowSize);
}

std::vector<int> slidingWindowMinimum(
    const std::vector<int>& values,
    std::size_t windowSize
) {
    if (values.empty() || windowSize == 0 || windowSize > values.size()) {
        return {};
    }

    std::vector<int> result;
    std::deque<std::size_t> candidates;

    for (std::size_t i = 0; i < values.size(); ++i) {
        while (!candidates.empty() && candidates.front() + windowSize <= i) {
            candidates.pop_front();
        }

        while (!candidates.empty() && values[candidates.back()] >= values[i]) {
            candidates.pop_back();
        }

        candidates.push_back(i);

        if (i + 1 >= windowSize) {
            result.push_back(values[candidates.front()]);
        }
    }

    return result;
}

std::vector<int> priorityQueueMaxHeapExample(const std::vector<int>& values) {
    std::priority_queue<int> heap;

    for (int value : values) {
        heap.push(value);
    }

    std::vector<int> result;

    while (!heap.empty()) {
        result.push_back(heap.top());
        heap.pop();
    }

    return result;
}

std::vector<int> priorityQueueMinHeapExample(const std::vector<int>& values) {
    std::priority_queue<int, std::vector<int>, std::greater<int>> heap;

    for (int value : values) {
        heap.push(value);
    }

    std::vector<int> result;

    while (!heap.empty()) {
        result.push_back(heap.top());
        heap.pop();
    }

    return result;
}

std::vector<std::string> processTasksByPriority(const std::vector<Task>& tasks) {
    std::priority_queue<
        QueuedTask,
        std::vector<QueuedTask>,
        CompareQueuedTask
    > heap;

    for (std::size_t i = 0; i < tasks.size(); ++i) {
        heap.push(QueuedTask{tasks[i].priority, i, tasks[i].name});
    }

    std::vector<std::string> result;

    while (!heap.empty()) {
        result.push_back(heap.top().name);
        heap.pop();
    }

    return result;
}

std::vector<int> keepTopKSmallest(const std::vector<int>& values, std::size_t k) {
    if (values.empty() || k == 0) {
        return {};
    }

    std::priority_queue<int> heap;

    for (int value : values) {
        if (heap.size() < k) {
            heap.push(value);
        } else if (value < heap.top()) {
            heap.pop();
            heap.push(value);
        }
    }

    std::vector<int> result;

    while (!heap.empty()) {
        result.push_back(heap.top());
        heap.pop();
    }

    std::sort(result.begin(), result.end());
    return result;
}

std::vector<int> keepTopKLargest(const std::vector<int>& values, std::size_t k) {
    if (values.empty() || k == 0) {
        return {};
    }

    std::priority_queue<int, std::vector<int>, std::greater<int>> heap;

    for (int value : values) {
        if (heap.size() < k) {
            heap.push(value);
        } else if (value > heap.top()) {
            heap.pop();
            heap.push(value);
        }
    }

    std::vector<int> result;

    while (!heap.empty()) {
        result.push_back(heap.top());
        heap.pop();
    }

    std::sort(result.begin(), result.end(), std::greater<int>());
    return result;
}

}  // namespace cookbook::queues_stacks