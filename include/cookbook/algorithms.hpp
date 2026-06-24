#pragma once

#include <cstddef>
#include <functional>
#include <optional>
#include <utility>
#include <vector>

namespace cookbook::algorithms {

// Returns the first index where target appears, or std::nullopt if it is absent.
std::optional<std::size_t> findFirstIndex(const std::vector<int>& values, int target);

// Returns the last index where target appears, or std::nullopt if it is absent.
std::optional<std::size_t> findLastIndex(const std::vector<int>& values, int target);

// Returns all indices where target appears.
std::vector<std::size_t> findAllIndices(const std::vector<int>& values, int target);

// Returns true if target appears at least once.
bool containsValue(const std::vector<int>& values, int target);

// Counts how many times target appears.
std::size_t countOccurrences(const std::vector<int>& values, int target);

// Returns true if all values satisfy predicate; true for empty input.
bool allMatch(const std::vector<int>& values, const std::function<bool(int)>& predicate);

// Returns true if at least one value satisfies predicate; false for empty input.
bool anyMatch(const std::vector<int>& values, const std::function<bool(int)>& predicate);

// Returns true if no values satisfy predicate; true for empty input.
bool noneMatch(const std::vector<int>& values, const std::function<bool(int)>& predicate);

// Returns a sorted copy of values in ascending order.
std::vector<int> sortAscending(const std::vector<int>& values);

// Returns a sorted copy of values in descending order.
std::vector<int> sortDescending(const std::vector<int>& values);

// Returns a stably sorted copy of values in ascending order.
std::vector<int> stableSortAscending(const std::vector<int>& values);

// Returns true if target exists in an already sorted ascending vector.
bool binarySearchSorted(const std::vector<int>& sortedValues, int target);

// Returns the first index where target could be inserted without breaking sorted order.
std::size_t lowerBoundIndex(const std::vector<int>& sortedValues, int target);

// Returns the first index after all existing values equal to target.
std::size_t upperBoundIndex(const std::vector<int>& sortedValues, int target);

// Returns a copy of values with all elements matching predicate removed.
std::vector<int> removeIfCopy(const std::vector<int>& values, const std::function<bool(int)>& predicate);

// Removes duplicate values from an already sorted vector.
std::vector<int> uniqueSorted(const std::vector<int>& sortedValues);

// Splits values into {matching, nonMatching} while preserving original order.
std::pair<std::vector<int>, std::vector<int>> partitionByPredicate(
    const std::vector<int>& values,
    const std::function<bool(int)>& predicate
);

// Returns a copy of values rotated left by steps positions.
std::vector<int> rotateLeft(const std::vector<int>& values, std::size_t steps);

// Returns a copy of values rotated right by steps positions.
std::vector<int> rotateRight(const std::vector<int>& values, std::size_t steps);

}  // namespace cookbook::algorithms