#pragma once

#include <cstddef>
#include <map>
#include <optional>
#include <set>
#include <string>
#include <utility>
#include <vector>

namespace cookbook::iteration {

// Copies all integers by iterating with range-for by value.
std::vector<int> rangeForByValue(const std::vector<int>& values);

// Adds delta to each integer by iterating over a local copy with non-const references.
std::vector<int> rangeForByReference(std::vector<int> values, int delta);

// Returns the length of each string by iterating with const references.
std::vector<std::size_t> rangeForByConstReference(const std::vector<std::string>& values);

// Copies all integers using a forward index-based loop.
std::vector<int> indexLoopForward(const std::vector<int>& values);

// Copies all integers in reverse order using a backward index-based loop.
std::vector<int> indexLoopBackward(const std::vector<int>& values);

// Copies all integers using an explicit forward iterator loop.
std::vector<int> iteratorLoopForward(const std::vector<int>& values);

// Returns the sum of all integers using const iterators.
int constIteratorLoop(const std::vector<int>& values);

// Removes all occurrences of target from a vector while iterating safely.
std::vector<int> eraseWhileIteratingVector(std::vector<int> values, int target);

// Removes map entries whose value is smaller than min_value while iterating safely.
std::map<std::string, int> eraseWhileIteratingMap(
    std::map<std::string, int> values,
    int min_value
);

// Removes set values greater than max_allowed while iterating safely.
std::set<int> eraseWhileIteratingSet(std::set<int> values, int max_allowed);

// Returns all keys from a map in sorted key order.
std::vector<std::string> iterateMapKeys(const std::map<std::string, int>& values);

// Returns all values from a map in sorted key order.
std::vector<int> iterateMapValues(const std::map<std::string, int>& values);

// Returns all key-value pairs from a map in sorted key order.
std::vector<std::pair<std::string, int>> iterateMapPairs(
    const std::map<std::string, int>& values
);

// Returns index-value pairs for every string in a vector.
std::vector<std::pair<std::size_t, std::string>> enumerateVector(
    const std::vector<std::string>& values
);

// Returns the index of target if found, otherwise std::nullopt.
std::optional<std::size_t> findWithIterator(
    const std::vector<int>& values,
    int target
);

// Multiplies every integer in a vector in place.
void transformInPlace(std::vector<int>& values, int multiplier);

// Copies all integers into a new vector using std::back_inserter.
std::vector<int> copyWithBackInserter(const std::vector<int>& values);

// Returns all integers greater than or equal to min_value using iterators.
std::vector<int> filterWithIterator(const std::vector<int>& values, int min_value);

}  // namespace cookbook::iteration
