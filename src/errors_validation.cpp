#include "cookbook/errors_validation.hpp"

#include <string>

namespace cookbook::errors_validation {

bool isNonEmpty(const std::string& text) {
    return !text.empty();
}

bool isIndexInRange(std::size_t index, std::size_t size) {
    return index < size;
}

void requireNonEmpty(const std::string& text, const std::string& value_name) {
    if (!isNonEmpty(text)) {
        throw std::invalid_argument(value_name + " must not be empty.");
    }
}

void requireIndexInRange(
    std::size_t index,
    std::size_t size,
    const std::string& container_name
) {
    if (!isIndexInRange(index, size)) {
        throw std::out_of_range(
            container_name + " index " + std::to_string(index)
            + " is out of range for size " + std::to_string(size) + "."
        );
    }
}

void requireSameSize(
    std::size_t left_size,
    std::size_t right_size,
    const std::string& left_name,
    const std::string& right_name
) {
    if (left_size != right_size) {
        throw std::invalid_argument(
            left_name + " size " + std::to_string(left_size)
            + " does not match " + right_name + " size "
            + std::to_string(right_size) + "."
        );
    }
}

void requirePositive(double value, const std::string& value_name) {
    if (!(value > 0.0)) {
        throw std::invalid_argument(value_name + " must be positive.");
    }
}

void requireNonNegative(double value, const std::string& value_name) {
    if (!(value >= 0.0)) {
        throw std::invalid_argument(value_name + " must be non-negative.");
    }
}

void requireRectangularMatrix(
    const std::vector<std::vector<double>>& matrix,
    const std::string& matrix_name
) {
    if (matrix.empty()) {
        throw std::invalid_argument(matrix_name + " must not be empty.");
    }

    const std::size_t column_count = matrix.front().size();

    if (column_count == 0) {
        throw std::invalid_argument(matrix_name + " must not contain empty rows.");
    }

    for (std::size_t row = 0; row < matrix.size(); ++row) {
        if (matrix[row].size() != column_count) {
            throw std::invalid_argument(
                matrix_name + " must be rectangular. Row "
                + std::to_string(row)
                + " has size "
                + std::to_string(matrix[row].size())
                + ", expected "
                + std::to_string(column_count)
                + "."
            );
        }
    }
}

void requireValidMatrixMultiplicationDimensions(
    const std::vector<std::vector<double>>& left,
    const std::vector<std::vector<double>>& right,
    const std::string& left_name,
    const std::string& right_name
) {
    requireRectangularMatrix(left, left_name);
    requireRectangularMatrix(right, right_name);

    const std::size_t left_columns = left.front().size();
    const std::size_t right_rows = right.size();

    if (left_columns != right_rows) {
        throw std::invalid_argument(
            left_name + " columns (" + std::to_string(left_columns)
            + ") must match " + right_name + " rows ("
            + std::to_string(right_rows) + ") for matrix multiplication."
        );
    }
}

std::optional<double> safeDivide(double numerator, double denominator) {
    if (denominator == 0.0) {
        return std::nullopt;
    }

    return numerator / denominator;
}

bool validateTokenCount(
    const std::vector<std::string>& tokens,
    std::size_t expected_count
) {
    return tokens.size() == expected_count;
}

bool validateFileOpened(const std::ifstream& file) {
    return file.is_open() && !file.fail();
}

}  // namespace cookbook::errors_validation