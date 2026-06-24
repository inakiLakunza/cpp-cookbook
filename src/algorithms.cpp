#include "cookbook/algorithms.hpp"

#include <algorithm>
#include <iterator>
#include <stdexcept>

namespace cookbook::algorithms {
namespace {

void requirePredicate(const std::function<bool(int)>& predicate) {
    if (!predicate) {
        throw std::invalid_argument("Predicate must be valid");
    }
}

}  // namespace

std::optional<std::size_t> findFirstIndex(
    const std::vector<int>& values,
    int target
) {
    const auto it = std::find(values.begin(), values.end(), target);

    if (it == values.end()) {
        return std::nullopt;
    }

    return static_cast<std::size_t>(std::distance(values.begin(), it));
}

std::optional<std::size_t> findLastIndex(
    const std::vector<int>& values,
    int target
) {
    const auto it = std::find(values.rbegin(), values.rend(), target);

    if (it == values.rend()) {
        return std::nullopt;
    }

    return static_cast<std::size_t>(
        std::distance(it, values.rend()) - 1
    );
}

std::vector<std::size_t> findAllIndices(
    const std::vector<int>& values,
    int target
) {
    std::vector<std::size_t> indices;

    for (std::size_t i = 0; i < values.size(); ++i) {
        if (values[i] == target) {
            indices.push_back(i);
        }
    }

    return indices;
}

bool containsValue(const std::vector<int>& values, int target) {
    return std::find(values.begin(), values.end(), target) != values.end();
}

std::size_t countOccurrences(const std::vector<int>& values, int target) {
    return static_cast<std::size_t>(
        std::count(values.begin(), values.end(), target)
    );
}

bool allMatch(
    const std::vector<int>& values,
    const std::function<bool(int)>& predicate
) {
    requirePredicate(predicate);

    return std::all_of(values.begin(), values.end(), predicate);
}

bool anyMatch(
    const std::vector<int>& values,
    const std::function<bool(int)>& predicate
) {
    requirePredicate(predicate);

    return std::any_of(values.begin(), values.end(), predicate);
}

bool noneMatch(
    const std::vector<int>& values,
    const std::function<bool(int)>& predicate
) {
    requirePredicate(predicate);

    return std::none_of(values.begin(), values.end(), predicate);
}

std::vector<int> sortAscending(const std::vector<int>& values) {
    std::vector<int> result = values;
    std::sort(result.begin(), result.end());
    return result;
}

std::vector<int> sortDescending(const std::vector<int>& values) {
    std::vector<int> result = values;

    std::sort(result.begin(), result.end(), std::greater<int>{});

    return result;
}

std::vector<int> stableSortAscending(const std::vector<int>& values) {
    std::vector<int> result = values;
    std::stable_sort(result.begin(), result.end());
    return result;
}

bool binarySearchSorted(
    const std::vector<int>& sortedValues,
    int target
) {
    return std::binary_search(
        sortedValues.begin(),
        sortedValues.end(),
        target
    );
}

std::size_t lowerBoundIndex(
    const std::vector<int>& sortedValues,
    int target
) {
    const auto it = std::lower_bound(
        sortedValues.begin(),
        sortedValues.end(),
        target
    );

    return static_cast<std::size_t>(
        std::distance(sortedValues.begin(), it)
    );
}

std::size_t upperBoundIndex(
    const std::vector<int>& sortedValues,
    int target
) {
    const auto it = std::upper_bound(
        sortedValues.begin(),
        sortedValues.end(),
        target
    );

    return static_cast<std::size_t>(
        std::distance(sortedValues.begin(), it)
    );
}

std::vector<int> removeIfCopy(
    const std::vector<int>& values,
    const std::function<bool(int)>& predicate
) {
    requirePredicate(predicate);

    std::vector<int> result;

    std::copy_if(
        values.begin(),
        values.end(),
        std::back_inserter(result),
        [&predicate](int value) {
            return !predicate(value);
        }
    );

    return result;
}

std::vector<int> uniqueSorted(const std::vector<int>& sortedValues) {
    std::vector<int> result = sortedValues;

    const auto newEnd = std::unique(result.begin(), result.end());
    result.erase(newEnd, result.end());

    return result;
}

std::pair<std::vector<int>, std::vector<int>> partitionByPredicate(
    const std::vector<int>& values,
    const std::function<bool(int)>& predicate
) {
    requirePredicate(predicate);

    std::vector<int> matching;
    std::vector<int> nonMatching;

    for (int value : values) {
        if (predicate(value)) {
            matching.push_back(value);
        } else {
            nonMatching.push_back(value);
        }
    }

    return {matching, nonMatching};
}

std::vector<int> rotateLeft(
    const std::vector<int>& values,
    std::size_t steps
) {
    if (values.empty()) {
        return {};
    }

    std::vector<int> result = values;
    steps %= result.size();

    std::rotate(
        result.begin(),
        result.begin() + static_cast<std::ptrdiff_t>(steps),
        result.end()
    );

    return result;
}

std::vector<int> rotateRight(
    const std::vector<int>& values,
    std::size_t steps
) {
    if (values.empty()) {
        return {};
    }

    const std::size_t normalizedSteps = steps % values.size();

    if (normalizedSteps == 0) {
        return values;
    }

    return rotateLeft(values, values.size() - normalizedSteps);
}

}  // namespace cookbook::algorithms