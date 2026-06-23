#include "cookbook/vectors.hpp"

#include <algorithm>
#include <iterator>
#include <numeric>
#include <unordered_set>

namespace cookbook::vectors {

bool contains(const std::vector<int>& values, int target) {
    return std::find(values.begin(), values.end(), target) != values.end();
}

std::optional<std::size_t> indexOf(const std::vector<int>& values, int target) {
    auto it = std::find(values.begin(), values.end(), target);

    if (it == values.end()) {
        return std::nullopt;
    }

    return static_cast<std::size_t>(std::distance(values.begin(), it));
}

std::vector<int> removeValue(const std::vector<int>& values, int target) {
    std::vector<int> result = values;

    result.erase(
        std::remove(result.begin(), result.end(), target),
        result.end()
    );

    return result;
}

std::vector<int> removeDuplicates(const std::vector<int>& values) {
    std::vector<int> result;
    std::unordered_set<int> seen;

    result.reserve(values.size());

    for (int value : values) {
        // insert returns {iterator, true} only when the value was not already present.
        if (seen.insert(value).second) {
            result.push_back(value);
        }
    }

    return result;
}

std::vector<int> filter(
    const std::vector<int>& values,
    const std::function<bool(int)>& predicate
) {
    std::vector<int> result;
    result.reserve(values.size());

    std::copy_if(
        values.begin(),
        values.end(),
        std::back_inserter(result),
        predicate
    );

    return result;
}

std::vector<int> transform(
    const std::vector<int>& values,
    const std::function<int(int)>& mapper
) {
    std::vector<int> result;
    result.reserve(values.size());

    std::transform(
        values.begin(),
        values.end(),
        std::back_inserter(result),
        mapper
    );

    return result;
}

int sum(const std::vector<int>& values) {
    return std::accumulate(values.begin(), values.end(), 0);
}

std::optional<double> average(const std::vector<int>& values) {
    if (values.empty()) {
        return std::nullopt;
    }

    return static_cast<double>(sum(values)) / static_cast<double>(values.size());
}

std::optional<int> minElement(const std::vector<int>& values) {
    if (values.empty()) {
        return std::nullopt;
    }

    return *std::min_element(values.begin(), values.end());
}

std::optional<int> maxElement(const std::vector<int>& values) {
    if (values.empty()) {
        return std::nullopt;
    }

    return *std::max_element(values.begin(), values.end());
}

std::vector<int> reverseCopy(const std::vector<int>& values) {
    std::vector<int> result = values;

    std::reverse(result.begin(), result.end());

    return result;
}

std::vector<int> slice(
    const std::vector<int>& values,
    std::size_t start,
    std::size_t end
) {
    if (start >= values.size() || start >= end) {
        return {};
    }

    const std::size_t safeEnd = std::min(end, values.size());

    return std::vector<int>(
        values.begin() + static_cast<std::ptrdiff_t>(start),
        values.begin() + static_cast<std::ptrdiff_t>(safeEnd)
    );
}

} // namespace cookbook::vectors