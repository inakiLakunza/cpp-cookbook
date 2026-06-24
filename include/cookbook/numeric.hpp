#pragma once

#include <cstddef>
#include <vector>

namespace cookbook::numeric {

// Returns the sum of all values. Example: sum({1, 2, 3}) -> 6.
double sum(const std::vector<double>& values);

// Returns the arithmetic mean. Example: mean({2, 4, 6}) -> 4.
double mean(const std::vector<double>& values);

// Returns the median value. Example: median({3, 1, 2}) -> 2.
double median(const std::vector<double>& values);

// Returns the population variance. Example: variance({1, 2, 3}) -> 0.666...
double variance(const std::vector<double>& values);

// Returns the population standard deviation. Example: standardDeviation({1, 2, 3}) -> 0.816...
double standardDeviation(const std::vector<double>& values);

// Returns the smallest value. Example: minValue({3, 1, 2}) -> 1.
double minValue(const std::vector<double>& values);

// Returns the largest value. Example: maxValue({3, 1, 2}) -> 3.
double maxValue(const std::vector<double>& values);

// Returns the index of the smallest value. Example: argmin({3, 1, 2}) -> 1.
std::size_t argmin(const std::vector<double>& values);

// Returns the index of the largest value. Example: argmax({3, 1, 2}) -> 0.
std::size_t argmax(const std::vector<double>& values);

// Clamps a value between a lower and upper bound. Example: clampValue(12, 0, 10) -> 10.
double clampValue(double value, double lower, double upper);

// Normalizes values to the [0, 1] range using min-max normalization. Example: normalizeMinMax({10, 20, 30}) -> {0, 0.5, 1}.
std::vector<double> normalizeMinMax(const std::vector<double>& values);

// Returns the dot product of two vectors. Example: dotProduct({1, 2}, {3, 4}) -> 11.
double dotProduct(const std::vector<double>& a, const std::vector<double>& b);

// Returns the Euclidean distance between two vectors. Example: euclideanDistance({0, 0}, {3, 4}) -> 5.
double euclideanDistance(const std::vector<double>& a, const std::vector<double>& b);

// Returns the Manhattan distance between two vectors. Example: manhattanDistance({1, 2}, {4, 6}) -> 7.
double manhattanDistance(const std::vector<double>& a, const std::vector<double>& b);

// Returns the cosine similarity between two vectors. Example: cosineSimilarity({1, 0}, {0, 1}) -> 0.
double cosineSimilarity(const std::vector<double>& a, const std::vector<double>& b);

// Returns the cumulative sum of values. Example: cumulativeSum({1, 2, 3}) -> {1, 3, 6}.
std::vector<double> cumulativeSum(const std::vector<double>& values);

// Returns simple moving averages using a fixed window. Example: movingAverage({1, 2, 3, 4}, 2) -> {1.5, 2.5, 3.5}.
std::vector<double> movingAverage(const std::vector<double>& values, std::size_t windowSize);

// Compares two floating-point values with absolute/relative tolerance. Example: isApproximatelyEqual(0.1 + 0.2, 0.3) -> true.
bool isApproximatelyEqual(double a, double b, double epsilon = 1e-9);

} // namespace cookbook::numeric