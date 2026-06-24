#include "cookbook/comparisons.hpp"

#include <iostream>
#include <string>
#include <utility>
#include <vector>

namespace comparisons = cookbook::comparisons;

void printJobs(const std::vector<comparisons::Job>& jobs) {
    for (const comparisons::Job& job : jobs) {
        std::cout << job.title << " | priority=" << job.priority
                  << " | duration=" << job.durationMinutes << "\n";
    }
}

void printValues(const std::vector<int>& values) {
    for (int value : values) {
        std::cout << value << " ";
    }
    std::cout << "\n";
}

void printPairs(const std::vector<std::pair<std::string, int>>& pairs) {
    for (const std::pair<std::string, int>& pair : pairs) {
        std::cout << pair.first << ": " << pair.second << "\n";
    }
}

int main() {
    const std::vector<comparisons::Job> jobs = {
        {"write docs", 2, 30},
        {"fix outage", 5, 60},
        {"small refactor", 5, 20},
        {"add tests", 5, 20}
    };

    std::cout << "Sort by single field: priority descending\n";
    printJobs(comparisons::sortBySingleField(jobs));
    // Expected first job: fix outage, because it has the highest priority.

    std::cout << "\nSort by multiple fields: priority desc, duration asc, title asc\n";
    printJobs(comparisons::sortByMultipleFields(jobs));
    // Expected order: add tests, small refactor, fix outage, write docs.

    const std::vector<int> values = {3, 1, 4, 1, 5};

    std::cout << "\nMax heap pop order\n";
    printValues(comparisons::priorityQueueMaxHeap(values));
    // Expected: 5 4 3 1 1

    std::cout << "\nMin heap pop order\n";
    printValues(comparisons::priorityQueueMinHeap(values));
    // Expected: 1 1 3 4 5

    const std::vector<std::pair<std::string, int>> scores = {
        {"ana", 3},
        {"mark", 5},
        {"sara", 5},
        {"bob", 3}
    };

    std::cout << "\nPairs by second desc, then first asc\n";
    printPairs(comparisons::comparePairsBySecondThenFirst(scores));
    // Expected: mark: 5, sara: 5, ana: 3, bob: 3

    std::cout << "\nNamed custom struct comparator\n";
    printJobs(comparisons::customStructComparator(jobs));
    // Expected same ordering as sortByMultipleFields.

    return 0;
}