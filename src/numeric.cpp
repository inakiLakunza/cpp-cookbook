#include "cookbook/numeric.hpp"

#include <algorithm>
#include <cmath>
#include <iterator>
#include <numeric>
#include <stdexcept>

namespace cookbook::numeric {
namespace {

void validateNotEmpty(const std::vector<double>& values, const std::string& functionName) {
    if (values.empty()) {
        throw std::invalid_argument(functionName + " requires at least one value");
    }
}

void validateSameSize(
    const std::vector<double>& a,
    const std::vector<double>& b,
    const std::string& functionName
) {
    if (a.size() != b.size()) {
        throw std::invalid_argument(functionName + " requires vectors with the same size");
    }
}

} // namespace

double sum(const std::vector<double>& values) {
    return std::accumulate(values.begin(), values.end(), 0.0);
}

double mean(const std::vector<double>& values) {
    validateNotEmpty(values, "mean");

    return sum(values) / static_cast<double>(values.size());
}

double median(const std::vector<double>& values) {
    validateNotEmpty(values, "median");

    std::vector<double> sorted = values;
    std::sort(sorted.begin(), sorted.end());

    const std::size_t middle = sorted.size() / 2;

    if (sorted.size() % 2 == 1) {
        return sorted[middle];
    }

    return (sorted[middle - 1] + sorted[middle]) / 2.0;
}

double variance(const std::vector<double>& values) {
    validateNotEmpty(values, "variance");

    const double avg = mean(values);

    double squaredDifferenceSum = 0.0;
    for (double value : values) {
        const double diff = value - avg;
        squaredDifferenceSum += diff * diff;
    }

    return squaredDifferenceSum / static_cast<double>(values.size());
}

double standardDeviation(const std::vector<double>& values) {
    return std::sqrt(variance(values));
}

double minValue(const std::vector<double>& values) {
    validateNotEmpty(values, "minValue");

    return *std::min_element(values.begin(), values.end());
}

double maxValue(const std::vector<double>& values) {
    validateNotEmpty(values, "maxValue");

    return *std::max_element(values.begin(), values.end());
}

std::size_t argmin(const std::vector<double>& values) {
    validateNotEmpty(values, "argmin");

    const auto it = std::min_element(values.begin(), values.end());
    return static_cast<std::size_t>(std::distance(values.begin(), it));
}

std::size_t argmax(const std::vector<double>& values) {
    validateNotEmpty(values, "argmax");

    const auto it = std::max_element(values.begin(), values.end());
    return static_cast<std::size_t>(std::distance(values.begin(), it));
}

double clampValue(double value, double lower, double upper) {
    if (lower > upper) {
        throw std::invalid_argument("clampValue requires lower <= upper");
    }

    return std::clamp(value, lower, upper);
}

std::vector<double> normalizeMinMax(const std::vector<double>& values) {
    if (values.empty()) {
        return {};
    }

    const double minVal = minValue(values);
    const double maxVal = maxValue(values);

    if (minVal == maxVal) {
        return std::vector<double>(values.size(), 0.0);
    }

    std::vector<double> result;
    result.reserve(values.size());

    for (double value : values) {
        result.push_back((value - minVal) / (maxVal - minVal));
    }

    return result;
}

double dotProduct(const std::vector<double>& a, const std::vector<double>& b) {
    validateSameSize(a, b, "dotProduct");

    return std::inner_product(a.begin(), a.end(), b.begin(), 0.0);
}

double euclideanDistance(const std::vector<double>& a, const std::vector<double>& b) {
    validateSameSize(a, b, "euclideanDistance");

    double squaredDifferenceSum = 0.0;

    for (std::size_t i = 0; i < a.size(); ++i) {
        const double diff = a[i] - b[i];
        squaredDifferenceSum += diff * diff;
    }

    return std::sqrt(squaredDifferenceSum);
}

double manhattanDistance(const std::vector<double>& a, const std::vector<double>& b) {
    validateSameSize(a, b, "manhattanDistance");

    double total = 0.0;

    for (std::size_t i = 0; i < a.size(); ++i) {
        total += std::abs(a[i] - b[i]);
    }

    return total;
}

double cosineSimilarity(const std::vector<double>& a, const std::vector<double>& b) {
    validateSameSize(a, b, "cosineSimilarity");

    const double magnitudeA = std::sqrt(dotProduct(a, a));
    const double magnitudeB = std::sqrt(dotProduct(b, b));

    if (magnitudeA == 0.0 || magnitudeB == 0.0) {
        throw std::invalid_argument("cosineSimilarity is undefined for zero vectors");
    }

    return dotProduct(a, b) / (magnitudeA * magnitudeB);
}

std::vector<double> cumulativeSum(const std::vector<double>& values) {
    std::vector<double> result;
    result.reserve(values.size());

    double runningTotal = 0.0;

    for (double value : values) {
        runningTotal += value;
        result.push_back(runningTotal);
    }

    return result;
}

std::vector<double> movingAverage(const std::vector<double>& values, std::size_t windowSize) {
    if (windowSize == 0) {
        throw std::invalid_argument("movingAverage requires windowSize > 0");
    }

    if (values.empty() || windowSize > values.size()) {
        return {};
    }

    std::vector<double> result;
    result.reserve(values.size() - windowSize + 1);

    double windowSum = 0.0;

    for (std::size_t i = 0; i < values.size(); ++i) {
        windowSum += values[i];

        if (i >= windowSize) {
            windowSum -= values[i - windowSize];
        }

        if (i + 1 >= windowSize) {
            result.push_back(windowSum / static_cast<double>(windowSize));
        }
    }

    return result;
}

bool isApproximatelyEqual(double a, double b, double epsilon) {
    if (epsilon < 0.0) {
        throw std::invalid_argument("isApproximatelyEqual requires epsilon >= 0");
    }

    const double difference = std::abs(a - b);
    const double scale = std::max({1.0, std::abs(a), std::abs(b)});

    return difference <= epsilon * scale;
}

} // namespace cookbook::numeric