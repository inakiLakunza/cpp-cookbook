#include "cookbook/iteration.hpp"

#include <iostream>
#include <map>
#include <optional>
#include <set>
#include <string>
#include <utility>
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

    std::cout << "]";
}

void printStringVector(const std::vector<std::string>& values) {
    std::cout << "[";

    for (std::size_t i = 0; i < values.size(); ++i) {
        std::cout << values[i];

        if (i + 1 < values.size()) {
            std::cout << ", ";
        }
    }

    std::cout << "]";
}

void printSizeVector(const std::vector<std::size_t>& values) {
    std::cout << "[";

    for (std::size_t i = 0; i < values.size(); ++i) {
        std::cout << values[i];

        if (i + 1 < values.size()) {
            std::cout << ", ";
        }
    }

    std::cout << "]";
}

void printMap(const std::map<std::string, int>& values) {
    std::cout << "{";

    std::size_t count = 0;

    for (const auto& pair : values) {
        std::cout << pair.first << ": " << pair.second;

        if (count + 1 < values.size()) {
            std::cout << ", ";
        }

        ++count;
    }

    std::cout << "}";
}

void printSet(const std::set<int>& values) {
    std::cout << "{";

    std::size_t count = 0;

    for (int value : values) {
        std::cout << value;

        if (count + 1 < values.size()) {
            std::cout << ", ";
        }

        ++count;
    }

    std::cout << "}";
}

void printEnumerated(
    const std::vector<std::pair<std::size_t, std::string>>& values
) {
    std::cout << "[";

    for (std::size_t i = 0; i < values.size(); ++i) {
        std::cout << "(" << values[i].first << ", " << values[i].second << ")";

        if (i + 1 < values.size()) {
            std::cout << ", ";
        }
    }

    std::cout << "]";
}

}  // namespace

int main() {
    const std::vector<int> numbers{1, 2, 3, 2, 4};
    const std::vector<std::string> names{"ana", "mark", "sara"};

    std::cout << "rangeForByValue({1, 2, 3, 2, 4}) -> ";
    printVector(cookbook::iteration::rangeForByValue(numbers));
    std::cout << "\n";
    // Expected: [1, 2, 3, 2, 4]

    std::cout << "rangeForByReference({1, 2, 3, 2, 4}, 10) -> ";
    printVector(cookbook::iteration::rangeForByReference(numbers, 10));
    std::cout << "\n";
    // Expected: [11, 12, 13, 12, 14]

    std::cout << "rangeForByConstReference({ana, mark, sara}) -> ";
    printSizeVector(cookbook::iteration::rangeForByConstReference(names));
    std::cout << "\n";
    // Expected: [3, 4, 4]

    std::cout << "indexLoopForward({1, 2, 3, 2, 4}) -> ";
    printVector(cookbook::iteration::indexLoopForward(numbers));
    std::cout << "\n";
    // Expected: [1, 2, 3, 2, 4]

    std::cout << "indexLoopBackward({1, 2, 3, 2, 4}) -> ";
    printVector(cookbook::iteration::indexLoopBackward(numbers));
    std::cout << "\n";
    // Expected: [4, 2, 3, 2, 1]

    std::cout << "iteratorLoopForward({1, 2, 3, 2, 4}) -> ";
    printVector(cookbook::iteration::iteratorLoopForward(numbers));
    std::cout << "\n";
    // Expected: [1, 2, 3, 2, 4]

    std::cout << "constIteratorLoop({1, 2, 3, 2, 4}) -> ";
    std::cout << cookbook::iteration::constIteratorLoop(numbers) << "\n";
    // Expected: 12

    std::cout << "eraseWhileIteratingVector({1, 2, 3, 2, 4}, 2) -> ";
    printVector(cookbook::iteration::eraseWhileIteratingVector(numbers, 2));
    std::cout << "\n";
    // Expected: [1, 3, 4]

    const std::map<std::string, int> scores{
        {"ana", 10},
        {"mark", 5},
        {"sara", 8}
    };

    std::cout << "eraseWhileIteratingMap(scores, 8) -> ";
    printMap(cookbook::iteration::eraseWhileIteratingMap(scores, 8));
    std::cout << "\n";
    // Expected: {ana: 10, sara: 8}

    const std::set<int> unique_values{1, 2, 3, 4, 5};

    std::cout << "eraseWhileIteratingSet({1, 2, 3, 4, 5}, 3) -> ";
    printSet(cookbook::iteration::eraseWhileIteratingSet(unique_values, 3));
    std::cout << "\n";
    // Expected: {1, 2, 3}

    std::cout << "iterateMapKeys(scores) -> ";
    printStringVector(cookbook::iteration::iterateMapKeys(scores));
    std::cout << "\n";
    // Expected: [ana, mark, sara]

    std::cout << "iterateMapValues(scores) -> ";
    printVector(cookbook::iteration::iterateMapValues(scores));
    std::cout << "\n";
    // Expected: [10, 5, 8]

    std::cout << "enumerateVector({ana, mark, sara}) -> ";
    printEnumerated(cookbook::iteration::enumerateVector(names));
    std::cout << "\n";
    // Expected: [(0, ana), (1, mark), (2, sara)]

    const std::optional<std::size_t> found_index =
        cookbook::iteration::findWithIterator(numbers, 3);

    std::cout << "findWithIterator({1, 2, 3, 2, 4}, 3) -> ";

    if (found_index.has_value()) {
        std::cout << found_index.value() << "\n";
    } else {
        std::cout << "not found\n";
    }
    // Expected: 2

    std::vector<int> mutable_numbers{1, 2, 3};
    cookbook::iteration::transformInPlace(mutable_numbers, 10);

    std::cout << "transformInPlace({1, 2, 3}, 10) -> ";
    printVector(mutable_numbers);
    std::cout << "\n";
    // Expected: [10, 20, 30]

    std::cout << "copyWithBackInserter({1, 2, 3, 2, 4}) -> ";
    printVector(cookbook::iteration::copyWithBackInserter(numbers));
    std::cout << "\n";
    // Expected: [1, 2, 3, 2, 4]

    std::cout << "filterWithIterator({1, 2, 3, 2, 4}, 3) -> ";
    printVector(cookbook::iteration::filterWithIterator(numbers, 3));
    std::cout << "\n";
    // Expected: [3, 4]

    return 0;
}