#include "cookbook/numeric.hpp"

#include <iostream>
#include <vector>

namespace {

void printVector(const std::vector<double>& values) {
    std::cout << "{";

    for (std::size_t i = 0; i < values.size(); ++i) {
        std::cout << values[i];

        if (i + 1 < values.size()) {
            std::cout << ", ";
        }
    }

    std::cout << "}";
}

} // namespace

int main() {
    const std::vector<double> values = {1.0, 2.0, 3.0, 4.0};
    const std::vector<double> other = {2.0, 0.0, 1.0, 3.0};

    std::cout << "sum: " << cookbook::numeric::sum(values) << "\n";
    std::cout << "mean: " << cookbook::numeric::mean(values) << "\n";
    std::cout << "median: " << cookbook::numeric::median(values) << "\n";
    std::cout << "variance: " << cookbook::numeric::variance(values) << "\n";
    std::cout << "standard deviation: " << cookbook::numeric::standardDeviation(values) << "\n";

    std::cout << "min value: " << cookbook::numeric::minValue(values) << "\n";
    std::cout << "max value: " << cookbook::numeric::maxValue(values) << "\n";
    std::cout << "argmin: " << cookbook::numeric::argmin(values) << "\n";
    std::cout << "argmax: " << cookbook::numeric::argmax(values) << "\n";

    std::cout << "clamp 12 to [0, 10]: "
              << cookbook::numeric::clampValue(12.0, 0.0, 10.0)
              << "\n";

    std::cout << "normalized: ";
    printVector(cookbook::numeric::normalizeMinMax(values));
    std::cout << "\n";

    std::cout << "dot product: " << cookbook::numeric::dotProduct(values, other) << "\n";
    std::cout << "euclidean distance: " << cookbook::numeric::euclideanDistance(values, other) << "\n";
    std::cout << "manhattan distance: " << cookbook::numeric::manhattanDistance(values, other) << "\n";
    std::cout << "cosine similarity: " << cookbook::numeric::cosineSimilarity(values, other) << "\n";

    std::cout << "cumulative sum: ";
    printVector(cookbook::numeric::cumulativeSum(values));
    std::cout << "\n";

    std::cout << "moving average window 2: ";
    printVector(cookbook::numeric::movingAverage(values, 2));
    std::cout << "\n";

    std::cout << "0.1 + 0.2 approximately equals 0.3: "
              << cookbook::numeric::isApproximatelyEqual(0.1 + 0.2, 0.3)
              << "\n";

    return 0;
}