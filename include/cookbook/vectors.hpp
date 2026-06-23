#pragma once

#include <cstddef>
#include <functional>
#include <optional>
#include <vector>

namespace cookbook::vectors {

// Returns true if the vector contains the target value.
bool contains(const std::vector<int>& values, int target);

// Returns the index of the first occurrence of target, or std::nullopt if not found.
std::optional<std::size_t> indexOf(const std::vector<int>& values, int target);

// Returns a copy of the vector with all occurrences of target removed.
std::vector<int> removeValue(const std::vector<int>& values, int target);

// Returns a copy of the vector with duplicate values removed, preserving first occurrence order.
std::vector<int> removeDuplicates(const std::vector<int>& values);

// Returns a new vector containing only values that satisfy the predicate.
std::vector<int> filter(
    const std::vector<int>& values,
    const std::function<bool(int)>& predicate
);

// Returns a new vector where each value has been mapped using the given function.
std::vector<int> transform(
    const std::vector<int>& values,
    const std::function<int(int)>& mapper
);

// Returns the sum of all values in the vector.
int sum(const std::vector<int>& values);

// Returns the average of the values, or std::nullopt if the vector is empty.
std::optional<double> average(const std::vector<int>& values);

// Returns the smallest value, or std::nullopt if the vector is empty.
std::optional<int> minElement(const std::vector<int>& values);

// Returns the largest value, or std::nullopt if the vector is empty.
std::optional<int> maxElement(const std::vector<int>& values);

// Returns a reversed copy of the vector.
std::vector<int> reverseCopy(const std::vector<int>& values);

// Returns a copy of the range [start, end), or an empty vector if the range is invalid.
std::vector<int> slice(
    const std::vector<int>& values,
    std::size_t start,
    std::size_t end
);

} // namespace cookbook::vectors