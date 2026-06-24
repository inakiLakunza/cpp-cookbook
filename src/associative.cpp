#include "cookbook/associative.hpp"

#include <algorithm>
#include <iterator>

namespace cookbook::associative {

bool containsKey(
    const std::unordered_map<std::string, int>& values,
    const std::string& key
) {
    return values.find(key) != values.end();
}

bool containsValue(
    const std::unordered_map<std::string, int>& values,
    int target
) {
    return std::any_of(
        values.begin(),
        values.end(),
        [target](const std::pair<const std::string, int>& entry) {
            return entry.second == target;
        }
    );
}

int getValueOrDefault(
    const std::unordered_map<std::string, int>& values,
    const std::string& key,
    int default_value
) {
    const auto it = values.find(key);

    if (it == values.end()) {
        return default_value;
    }

    return it->second;
}

std::unordered_map<std::string, int> countFrequencies(
    const std::vector<std::string>& values
) {
    std::unordered_map<std::string, int> frequencies;

    for (const std::string& value : values) {
        ++frequencies[value];
    }

    return frequencies;
}

std::unordered_map<std::string, int> mergeFrequencyMaps(
    const std::unordered_map<std::string, int>& first,
    const std::unordered_map<std::string, int>& second
) {
    std::unordered_map<std::string, int> result = first;

    for (const auto& entry : second) {
        result[entry.first] += entry.second;
    }

    return result;
}

std::vector<std::string> getSortedKeys(
    const std::unordered_map<std::string, int>& values
) {
    std::vector<std::string> keys;
    keys.reserve(values.size());

    for (const auto& entry : values) {
        keys.push_back(entry.first);
    }

    std::sort(keys.begin(), keys.end());
    return keys;
}

std::vector<int> getSortedValues(
    const std::unordered_map<std::string, int>& values
) {
    std::vector<int> result;
    result.reserve(values.size());

    for (const auto& entry : values) {
        result.push_back(entry.second);
    }

    std::sort(result.begin(), result.end());
    return result;
}

std::unordered_map<int, std::vector<std::string>> invertMap(
    const std::unordered_map<std::string, int>& values
) {
    std::unordered_map<int, std::vector<std::string>> result;

    for (const auto& entry : values) {
        result[entry.second].push_back(entry.first);
    }

    // Sorting makes the output deterministic and easier to test.
    for (auto& entry : result) {
        std::sort(entry.second.begin(), entry.second.end());
    }

    return result;
}

std::unordered_map<std::string, std::vector<std::string>> groupByKey(
    const std::vector<std::pair<std::string, std::string>>& pairs
) {
    std::unordered_map<std::string, std::vector<std::string>> groups;

    for (const auto& pair : pairs) {
        groups[pair.first].push_back(pair.second);
    }

    return groups;
}

std::unordered_map<std::string, std::size_t> buildIndexMap(
    const std::vector<std::string>& values
) {
    std::unordered_map<std::string, std::size_t> result;

    for (std::size_t i = 0; i < values.size(); ++i) {
        const std::string& value = values[i];

        if (result.find(value) == result.end()) {
            result[value] = i;
        }
    }

    return result;
}

bool removeKeyIfExists(
    std::unordered_map<std::string, int>& values,
    const std::string& key
) {
    return values.erase(key) > 0;
}

std::optional<std::pair<std::string, int>> findMostFrequent(
    const std::unordered_map<std::string, int>& frequencies
) {
    if (frequencies.empty()) {
        return std::nullopt;
    }

    auto best = frequencies.begin();

    for (auto it = frequencies.begin(); it != frequencies.end(); ++it) {
        const bool higher_count = it->second > best->second;
        const bool same_count_smaller_key =
            it->second == best->second && it->first < best->first;

        if (higher_count || same_count_smaller_key) {
            best = it;
        }
    }

    return std::make_pair(best->first, best->second);
}

std::optional<std::pair<std::string, int>> findLeastFrequent(
    const std::unordered_map<std::string, int>& frequencies
) {
    if (frequencies.empty()) {
        return std::nullopt;
    }

    auto best = frequencies.begin();

    for (auto it = frequencies.begin(); it != frequencies.end(); ++it) {
        const bool lower_count = it->second < best->second;
        const bool same_count_smaller_key =
            it->second == best->second && it->first < best->first;

        if (lower_count || same_count_smaller_key) {
            best = it;
        }
    }

    return std::make_pair(best->first, best->second);
}

std::vector<std::pair<std::string, int>> topKFrequent(
    const std::unordered_map<std::string, int>& frequencies,
    std::size_t k
) {
    std::vector<std::pair<std::string, int>> pairs = mapToVectorPairs(frequencies);

    std::sort(
        pairs.begin(),
        pairs.end(),
        [](const auto& left, const auto& right) {
            if (left.second != right.second) {
                return left.second > right.second;
            }

            return left.first < right.first;
        }
    );

    if (k < pairs.size()) {
        pairs.resize(k);
    }

    return pairs;
}

std::vector<std::pair<std::string, int>> mapToVectorPairs(
    const std::unordered_map<std::string, int>& values
) {
    std::vector<std::pair<std::string, int>> result;
    result.reserve(values.size());

    for (const auto& entry : values) {
        result.emplace_back(entry.first, entry.second);
    }

    std::sort(
        result.begin(),
        result.end(),
        [](const auto& left, const auto& right) {
            return left.first < right.first;
        }
    );

    return result;
}

std::unordered_map<std::string, int> vectorPairsToMap(
    const std::vector<std::pair<std::string, int>>& pairs
) {
    std::unordered_map<std::string, int> result;

    for (const auto& pair : pairs) {
        result[pair.first] += pair.second;
    }

    return result;
}

std::set<int> setIntersection(
    const std::set<int>& first,
    const std::set<int>& second
) {
    std::set<int> result;

    std::set_intersection(
        first.begin(),
        first.end(),
        second.begin(),
        second.end(),
        std::inserter(result, result.begin())
    );

    return result;
}

std::set<int> setUnionValues(
    const std::set<int>& first,
    const std::set<int>& second
) {
    std::set<int> result;

    std::set_union(
        first.begin(),
        first.end(),
        second.begin(),
        second.end(),
        std::inserter(result, result.begin())
    );

    return result;
}

std::set<int> setDifferenceValues(
    const std::set<int>& first,
    const std::set<int>& second
) {
    std::set<int> result;

    std::set_difference(
        first.begin(),
        first.end(),
        second.begin(),
        second.end(),
        std::inserter(result, result.begin())
    );

    return result;
}

} // namespace cookbook::associative