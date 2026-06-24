#include "cookbook/algorithms.hpp"

#include <iostream>
#include <optional>
#include <vector>

namespace {

void printVector(const std::vector<int>& values) {
    std::cout << "{ ";

    for (int value : values) {
        std::cout << value << " ";
    }

    std::cout << "}";
}

void printOptionalIndex(const std::optional<std::size_t>& index) {
    if (index.has_value()) {
        std::cout << *index;
    } else {
        std::cout << "not found";
    }
}

}  // namespace

int main() {
    const std::vector<int> values = {4, 2, 7, 2, 9, 2};

    std::cout << "Values: ";
    printVector(values);
    std::cout << "\n\n";

    std::cout << "findFirstIndex(values, 2): ";
    printOptionalIndex(cookbook::algorithms::findFirstIndex(values, 2));
    std::cout << "\n";
    // Expected: 1

    std::cout << "findLastIndex(values, 2): ";
    printOptionalIndex(cookbook::algorithms::findLastIndex(values, 2));
    std::cout << "\n";
    // Expected: 5

    std::cout << "containsValue(values, 7): "
              << cookbook::algorithms::containsValue(values, 7)
              << "\n";
    // Expected: 1

    std::cout << "countOccurrences(values, 2): "
              << cookbook::algorithms::countOccurrences(values, 2)
              << "\n";
    // Expected: 3

    const bool allPositive = cookbook::algorithms::allMatch(
        values,
        [](int value) {
            return value > 0;
        }
    );

    std::cout << "allMatch(values, value > 0): "
              << allPositive
              << "\n";
    // Expected: 1

    const std::vector<int> ascending =
        cookbook::algorithms::sortAscending(values);

    std::cout << "sortAscending(values): ";
    printVector(ascending);
    std::cout << "\n";
    // Expected: { 2 2 2 4 7 9 }

    const std::vector<int> descending =
        cookbook::algorithms::sortDescending(values);

    std::cout << "sortDescending(values): ";
    printVector(descending);
    std::cout << "\n";
    // Expected: { 9 7 4 2 2 2 }

    std::cout << "binarySearchSorted(ascending, 7): "
              << cookbook::algorithms::binarySearchSorted(ascending, 7)
              << "\n";
    // Expected: 1

    std::cout << "lowerBoundIndex(ascending, 4): "
              << cookbook::algorithms::lowerBoundIndex(ascending, 4)
              << "\n";
    // Expected: 3

    std::cout << "upperBoundIndex(ascending, 2): "
              << cookbook::algorithms::upperBoundIndex(ascending, 2)
              << "\n";
    // Expected: 3

    const std::vector<int> withoutTwos =
        cookbook::algorithms::removeIfCopy(
            values,
            [](int value) {
                return value == 2;
            }
        );

    std::cout << "removeIfCopy(values, value == 2): ";
    printVector(withoutTwos);
    std::cout << "\n";
    // Expected: { 4 7 9 }

    const std::vector<int> unique =
        cookbook::algorithms::uniqueSorted(ascending);

    std::cout << "uniqueSorted(ascending): ";
    printVector(unique);
    std::cout << "\n";
    // Expected: { 2 4 7 9 }

    const auto partitioned =
        cookbook::algorithms::partitionByPredicate(
            values,
            [](int value) {
                return value % 2 == 0;
            }
        );

    std::cout << "partitionByPredicate(values, even).first: ";
    printVector(partitioned.first);
    std::cout << "\n";
    // Expected: { 4 2 2 2 }

    std::cout << "partitionByPredicate(values, even).second: ";
    printVector(partitioned.second);
    std::cout << "\n";
    // Expected: { 7 9 }

    const std::vector<int> rotatedLeft =
        cookbook::algorithms::rotateLeft(values, 2);

    std::cout << "rotateLeft(values, 2): ";
    printVector(rotatedLeft);
    std::cout << "\n";
    // Expected: { 7 2 9 2 4 2 }

    const std::vector<int> rotatedRight =
        cookbook::algorithms::rotateRight(values, 2);

    std::cout << "rotateRight(values, 2): ";
    printVector(rotatedRight);
    std::cout << "\n";
    // Expected: { 9 2 4 2 7 2 }

    return 0;
}