#include "cookbook/iteration.hpp"

#include <algorithm>
#include <iterator>

namespace cookbook::iteration {

std::vector<int> rangeForByValue(const std::vector<int>& values) {
    std::vector<int> result;
    result.reserve(values.size());

    for (int value : values) {
        result.push_back(value);
    }

    return result;
}

std::vector<int> rangeForByReference(std::vector<int> values, int delta) {
    for (int& value : values) {
        value += delta;
    }

    return values;
}

std::vector<std::size_t> rangeForByConstReference(
    const std::vector<std::string>& values
) {
    std::vector<std::size_t> lengths;
    lengths.reserve(values.size());

    for (const std::string& value : values) {
        lengths.push_back(value.size());
    }

    return lengths;
}

std::vector<int> indexLoopForward(const std::vector<int>& values) {
    std::vector<int> result;
    result.reserve(values.size());

    for (std::size_t i = 0; i < values.size(); ++i) {
        result.push_back(values[i]);
    }

    return result;
}

std::vector<int> indexLoopBackward(const std::vector<int>& values) {
    std::vector<int> result;
    result.reserve(values.size());

    for (std::size_t i = values.size(); i > 0; --i) {
        result.push_back(values[i - 1]);
    }

    return result;
}

std::vector<int> iteratorLoopForward(const std::vector<int>& values) {
    std::vector<int> result;
    result.reserve(values.size());

    for (auto it = values.begin(); it != values.end(); ++it) {
        result.push_back(*it);
    }

    return result;
}

int constIteratorLoop(const std::vector<int>& values) {
    int total = 0;

    for (auto it = values.cbegin(); it != values.cend(); ++it) {
        total += *it;
    }

    return total;
}

std::vector<int> eraseWhileIteratingVector(std::vector<int> values, int target) {
    for (auto it = values.begin(); it != values.end();) {
        if (*it == target) {
            it = values.erase(it);
        } else {
            ++it;
        }
    }

    return values;
}

std::map<std::string, int> eraseWhileIteratingMap(
    std::map<std::string, int> values,
    int min_value
) {
    for (auto it = values.begin(); it != values.end();) {
        if (it->second < min_value) {
            it = values.erase(it);
        } else {
            ++it;
        }
    }

    return values;
}

std::set<int> eraseWhileIteratingSet(std::set<int> values, int max_allowed) {
    for (auto it = values.begin(); it != values.end();) {
        if (*it > max_allowed) {
            it = values.erase(it);
        } else {
            ++it;
        }
    }

    return values;
}

std::vector<std::string> iterateMapKeys(
    const std::map<std::string, int>& values
) {
    std::vector<std::string> keys;
    keys.reserve(values.size());

    for (const auto& pair : values) {
        keys.push_back(pair.first);
    }

    return keys;
}

std::vector<int> iterateMapValues(const std::map<std::string, int>& values) {
    std::vector<int> result;
    result.reserve(values.size());

    for (const auto& pair : values) {
        result.push_back(pair.second);
    }

    return result;
}

std::vector<std::pair<std::string, int>> iterateMapPairs(
    const std::map<std::string, int>& values
) {
    std::vector<std::pair<std::string, int>> result;
    result.reserve(values.size());

    for (const auto& pair : values) {
        result.push_back(pair);
    }

    return result;
}

std::vector<std::pair<std::size_t, std::string>> enumerateVector(
    const std::vector<std::string>& values
) {
    std::vector<std::pair<std::size_t, std::string>> result;
    result.reserve(values.size());

    for (std::size_t i = 0; i < values.size(); ++i) {
        result.emplace_back(i, values[i]);
    }

    return result;
}

std::optional<std::size_t> findWithIterator(
    const std::vector<int>& values,
    int target
) {
    std::size_t index = 0;

    for (auto it = values.cbegin(); it != values.cend(); ++it) {
        if (*it == target) {
            return index;
        }

        ++index;
    }

    return std::nullopt;
}

void transformInPlace(std::vector<int>& values, int multiplier) {
    for (int& value : values) {
        value *= multiplier;
    }
}

std::vector<int> copyWithBackInserter(const std::vector<int>& values) {
    std::vector<int> result;
    result.reserve(values.size());

    std::copy(
        values.cbegin(),
        values.cend(),
        std::back_inserter(result)
    );

    return result;
}

std::vector<int> filterWithIterator(
    const std::vector<int>& values,
    int min_value
) {
    std::vector<int> result;

    for (auto it = values.cbegin(); it != values.cend(); ++it) {
        if (*it >= min_value) {
            result.push_back(*it);
        }
    }

    return result;
}

}  // namespace cookbook::iteration