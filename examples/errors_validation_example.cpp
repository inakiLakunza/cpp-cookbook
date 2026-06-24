#include "cookbook/errors_validation.hpp"

#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

int main() {
    namespace ev = cookbook::errors_validation;

    // Expected input: "hello"
    // Expected output: Text is valid.
    const std::string text = "hello";

    if (ev::isNonEmpty(text)) {
        std::cout << "Text is valid.\n";
    }

    // Expected input: {"12:01", "auth", "ERROR", "Login failed"}, expected count 4
    // Expected output: Token count is valid.
    const std::vector<std::string> tokens = {
        "12:01",
        "auth",
        "ERROR",
        "Login failed"
    };

    if (ev::validateTokenCount(tokens, 4)) {
        std::cout << "Token count is valid.\n";
    }

    // Expected input: values = {10, 20, 30}, index = 1
    // Expected output: Value at index 1: 20
    const std::vector<int> values = {10, 20, 30};
    std::cout << "Value at index 1: " << ev::safeAt(values, 1, "values") << "\n";

    // Expected input: 10 / 2
    // Expected output: Division result: 5
    const std::optional<double> result = ev::safeDivide(10.0, 2.0);

    if (result.has_value()) {
        std::cout << "Division result: " << result.value() << "\n";
    }

    // Expected input: 10 / 0
    // Expected output: Cannot divide by zero.
    const std::optional<double> invalid_result = ev::safeDivide(10.0, 0.0);

    if (!invalid_result.has_value()) {
        std::cout << "Cannot divide by zero.\n";
    }

    // Expected input: sorted vector {1, 2, 3}
    // Expected output: Sorted check passed.
    const std::vector<int> sorted_values = {1, 2, 3};
    ev::requireSorted(sorted_values, "sorted_values");
    std::cout << "Sorted check passed.\n";

    // Expected input: matrix A is 2x3, matrix B is 3x2
    // Expected output: Matrix multiplication dimensions are valid.
    const std::vector<std::vector<double>> a = {
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0}
    };

    const std::vector<std::vector<double>> b = {
        {1.0, 2.0},
        {3.0, 4.0},
        {5.0, 6.0}
    };

    ev::requireValidMatrixMultiplicationDimensions(a, b, "a", "b");
    std::cout << "Matrix multiplication dimensions are valid.\n";

    // Expected input: 42, valid if positive
    // Expected output: Optional value: 42
    const std::optional<int> maybe_positive = ev::returnOptionalIfValid(
        42,
        [](int value) {
            return value > 0;
        }
    );

    if (maybe_positive.has_value()) {
        std::cout << "Optional value: " << maybe_positive.value() << "\n";
    }

    // Expected input: missing file
    // Expected output: File could not be opened.
    std::ifstream file("missing_file.txt");

    if (!ev::validateFileOpened(file)) {
        std::cout << "File could not be opened.\n";
    }

    return 0;
}