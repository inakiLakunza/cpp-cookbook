#include "cookbook/comparisons.hpp"

#include <algorithm>
#include <functional>
#include <queue>

namespace cookbook::comparisons {

bool JobPriorityComparator::operator()(const Job& left, const Job& right) const {
    if (left.priority != right.priority) {
        return left.priority > right.priority;
    }
    if (left.durationMinutes != right.durationMinutes) {
        return left.durationMinutes < right.durationMinutes;
    }
    return left.title < right.title;
}

std::vector<Job> sortBySingleField(const std::vector<Job>& jobs) {
    std::vector<Job> sorted = jobs;

    // stable_sort keeps the original relative order when priorities are equal.
    std::stable_sort(
        sorted.begin(),
        sorted.end(),
        [](const Job& left, const Job& right) {
            return left.priority > right.priority;
        }
    );

    return sorted;
}

std::vector<Job> sortByMultipleFields(const std::vector<Job>& jobs) {
    std::vector<Job> sorted = jobs;

    std::sort(
        sorted.begin(),
        sorted.end(),
        [](const Job& left, const Job& right) {
            if (left.priority != right.priority) {
                return left.priority > right.priority;
            }
            if (left.durationMinutes != right.durationMinutes) {
                return left.durationMinutes < right.durationMinutes;
            }
            return left.title < right.title;
        }
    );

    return sorted;
}

std::vector<int> priorityQueueMaxHeap(const std::vector<int>& values) {
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

std::vector<int> priorityQueueMinHeap(const std::vector<int>& values) {
    // std::greater<int> reverses the default priority_queue order into a min-heap.
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

std::vector<std::pair<std::string, int>> comparePairsBySecondThenFirst(
    const std::vector<std::pair<std::string, int>>& pairs
) {
    std::vector<std::pair<std::string, int>> sorted = pairs;

    std::sort(
        sorted.begin(),
        sorted.end(),
        [](const std::pair<std::string, int>& left,
           const std::pair<std::string, int>& right) {
            if (left.second != right.second) {
                return left.second > right.second;
            }
            return left.first < right.first;
        }
    );

    return sorted;
}

std::vector<Job> customStructComparator(const std::vector<Job>& jobs) {
    std::vector<Job> sorted = jobs;
    std::sort(sorted.begin(), sorted.end(), JobPriorityComparator{});
    return sorted;
}

}  // namespace cookbook::comparisons