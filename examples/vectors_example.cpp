#include "cookbook/vectors.hpp"

#include <iostream>
#include <optional>
#include <vector>

void printVector(const std::vector<int>& values) {
    std::cout << "{ ";

    for (int value : values) {
        std::cout << value << " ";
    }

    std::cout << "}";
}

void printOptionalInt(const std::optional<int>& value) {
    if (value.has_value()) {
        std::cout << value.value();
    } else {
        std::cout << "none";
    }
}

void printOptionalSize(const std::optional<std::size_t>& value) {
    if (value.has_value()) {
        std::cout << value.value();
    } else {
        std::cout << "none";
    }
}

void printOptionalDouble(const std::optional<double>& value) {
    if (value.has_value()) {
        std::cout << value.value();
    } else {
        std::cout << "none";
    }
}

int main() {
    namespace vec = cookbook::vectors;

    const std::vector<int> values = {1, 2, 3, 2, 4, 5, 3};

    std::cout << "Input: ";
    printVector(values);
    std::cout << "\n\n";

    std::cout << "contains(values, 3): ";
    std::cout << std::boolalpha << vec::contains(values, 3) << "\n";
    // Expected: true

    std::cout << "indexOf(values, 4): ";
    printOptionalSize(vec::indexOf(values, 4));
    std::cout << "\n";
    // Expected: 4

    std::cout << "removeValue(values, 2): ";
    printVector(vec::removeValue(values, 2));
    std::cout << "\n";
    // Expected: { 1 3 4 5 3 }

    std::cout << "removeDuplicates(values): ";
    printVector(vec::removeDuplicates(values));
    std::cout << "\n";
    // Expected: { 1 2 3 4 5 }

    std::cout << "filter even values: ";
    printVector(vec::filter(values, [](int x) {
        return x % 2 == 0;
    }));
    std::cout << "\n";
    // Expected: { 2 2 4 }

    std::cout << "transform values * 10: ";
    printVector(vec::transform(values, [](int x) {
        return x * 10;
    }));
    std::cout << "\n";
    // Expected: { 10 20 30 20 40 50 30 }

    std::cout << "sum(values): " << vec::sum(values) << "\n";
    // Expected: 20

    std::cout << "average(values): ";
    printOptionalDouble(vec::average(values));
    std::cout << "\n";
    // Expected: approximately 2.85714

    std::cout << "minElement(values): ";
    printOptionalInt(vec::minElement(values));
    std::cout << "\n";
    // Expected: 1

    std::cout << "maxElement(values): ";
    printOptionalInt(vec::maxElement(values));
    std::cout << "\n";
    // Expected: 5

    std::cout << "reverseCopy(values): ";
    printVector(vec::reverseCopy(values));
    std::cout << "\n";
    // Expected: { 3 5 4 2 3 2 1 }

    std::cout << "slice(values, 2, 5): ";
    printVector(vec::slice(values, 2, 5));
    std::cout << "\n";
    // Expected: { 3 2 4 }

    return 0;
}