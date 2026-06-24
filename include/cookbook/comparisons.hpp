#pragma once

#include <string>
#include <utility>
#include <vector>

namespace cookbook::comparisons {

struct Job {
    std::string title;
    int priority;
    int durationMinutes;
};

struct JobPriorityComparator {
    // Returns true when left should appear before right in sorted job order.
    bool operator()(const Job& left, const Job& right) const;
};

// Sorts jobs by priority from highest to lowest.
std::vector<Job> sortBySingleField(const std::vector<Job>& jobs);

// Sorts jobs by priority descending, duration ascending, then title ascending.
std::vector<Job> sortByMultipleFields(const std::vector<Job>& jobs);

// Returns values popped from a max-heap priority queue from largest to smallest.
std::vector<int> priorityQueueMaxHeap(const std::vector<int>& values);

// Returns values popped from a min-heap priority queue from smallest to largest.
std::vector<int> priorityQueueMinHeap(const std::vector<int>& values);

// Sorts pairs by second descending, then first ascending.
std::vector<std::pair<std::string, int>> comparePairsBySecondThenFirst(
    const std::vector<std::pair<std::string, int>>& pairs
);

// Sorts jobs using a reusable named comparator struct.
std::vector<Job> customStructComparator(const std::vector<Job>& jobs);

}  // namespace cookbook::comparisons