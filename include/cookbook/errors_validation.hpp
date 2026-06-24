#pragma once

#include <algorithm>
#include <cstddef>
#include <fstream>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

namespace cookbook::errors_validation {

// Returns true if the string is not empty.
bool isNonEmpty(const std::string& text);

// Returns true if index is valid for a container of the given size.
bool isIndexInRange(std::size_t index, std::size_t size);

// Throws std::invalid_argument if the string is empty.
void requireNonEmpty(const std::string& text, const std::string& value_name);

// Throws std::out_of_range if index is invalid for a container of the given size.
void requireIndexInRange(
    std::size_t index,
    std::size_t size,
    const std::string& container_name
);

// Throws std::invalid_argument if two sizes are different.
void requireSameSize(
    std::size_t left_size,
    std::size_t right_size,
    const std::string& left_name,
    const std::string& right_name
);

// Throws std::invalid_argument if value is not strictly positive.
void requirePositive(double value, const std::string& value_name);

// Throws std::invalid_argument if value is negative.
void requireNonNegative(double value, const std::string& value_name);

// Throws std::invalid_argument if the vector is not sorted in ascending order.
template <typename T>
void requireSorted(const std::vector<T>& values, const std::string& value_name) {
    if (!std::is_sorted(values.begin(), values.end())) {
        throw std::invalid_argument(value_name + " must be sorted in ascending order.");
    }
}

// Throws std::invalid_argument if the matrix is empty, has empty rows, or has uneven row sizes.
void requireRectangularMatrix(
    const std::vector<std::vector<double>>& matrix,
    const std::string& matrix_name
);

// Throws std::invalid_argument if two matrices cannot be multiplied.
void requireValidMatrixMultiplicationDimensions(
    const std::vector<std::vector<double>>& left,
    const std::vector<std::vector<double>>& right,
    const std::string& left_name,
    const std::string& right_name
);

// Returns a const reference to values[index], or throws std::out_of_range if index is invalid.
template <typename T>
const T& safeAt(
    const std::vector<T>& values,
    std::size_t index,
    const std::string& container_name
) {
    requireIndexInRange(index, values.size(), container_name);
    return values[index];
}

// Returns a mutable reference to values[index], or throws std::out_of_range if index is invalid.
template <typename T>
T& safeAt(
    std::vector<T>& values,
    std::size_t index,
    const std::string& container_name
) {
    requireIndexInRange(index, values.size(), container_name);
    return values[index];
}

// Returns numerator / denominator, or std::nullopt if denominator is zero.
std::optional<double> safeDivide(double numerator, double denominator);

// Returns value inside std::optional if predicate(value) is true, otherwise returns std::nullopt.
template <typename T, typename Predicate>
std::optional<T> returnOptionalIfValid(const T& value, Predicate predicate) {
    if (predicate(value)) {
        return value;
    }

    return std::nullopt;
}

// Returns true if the token vector has exactly the expected number of tokens.
bool validateTokenCount(
    const std::vector<std::string>& tokens,
    std::size_t expected_count
);

// Returns true if the input file stream is open and not in a failed state.
bool validateFileOpened(const std::ifstream& file);

}  // namespace cookbook::errors_validation