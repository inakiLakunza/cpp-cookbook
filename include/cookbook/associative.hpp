#pragma once

#include <cstddef>
#include <optional>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace cookbook::associative {

// Returns true if the map contains the given key.
bool containsKey(
    const std::unordered_map<std::string, int>& values,
    const std::string& key
);

// Returns true if the map contains the given value.
bool containsValue(
    const std::unordered_map<std::string, int>& values,
    int target
);

// Returns the value for a key, or a default value if the key does not exist.
int getValueOrDefault(
    const std::unordered_map<std::string, int>& values,
    const std::string& key,
    int default_value
);

// Counts how many times each string appears in the input vector.
std::unordered_map<std::string, int> countFrequencies(
    const std::vector<std::string>& values
);

// Merges two frequency maps by adding values for matching keys.
std::unordered_map<std::string, int> mergeFrequencyMaps(
    const std::unordered_map<std::string, int>& first,
    const std::unordered_map<std::string, int>& second
);

// Returns all map keys sorted alphabetically.
std::vector<std::string> getSortedKeys(
    const std::unordered_map<std::string, int>& values
);

// Returns all map values sorted increasingly.
std::vector<int> getSortedValues(
    const std::unordered_map<std::string, int>& values
);

// Inverts a string-to-int map into an int-to-list-of-strings map.
std::unordered_map<int, std::vector<std::string>> invertMap(
    const std::unordered_map<std::string, int>& values
);

// Groups values by key while preserving the input order inside each group.
std::unordered_map<std::string, std::vector<std::string>> groupByKey(
    const std::vector<std::pair<std::string, std::string>>& pairs
);

// Builds a map from value to its first index in the vector.
std::unordered_map<std::string, std::size_t> buildIndexMap(
    const std::vector<std::string>& values
);

// Removes a key from the map if it exists and returns whether anything was removed.
bool removeKeyIfExists(
    std::unordered_map<std::string, int>& values,
    const std::string& key
);

// Finds the key-value pair with the highest frequency.
std::optional<std::pair<std::string, int>> findMostFrequent(
    const std::unordered_map<std::string, int>& frequencies
);

// Finds the key-value pair with the lowest frequency.
std::optional<std::pair<std::string, int>> findLeastFrequent(
    const std::unordered_map<std::string, int>& frequencies
);

// Returns the top k most frequent pairs, sorted by frequency descending and key ascending.
std::vector<std::pair<std::string, int>> topKFrequent(
    const std::unordered_map<std::string, int>& frequencies,
    std::size_t k
);

// Converts a map into a vector of pairs sorted by key.
std::vector<std::pair<std::string, int>> mapToVectorPairs(
    const std::unordered_map<std::string, int>& values
);

// Converts a vector of pairs into a map, summing duplicate keys.
std::unordered_map<std::string, int> vectorPairsToMap(
    const std::vector<std::pair<std::string, int>>& pairs
);

// Returns the intersection of two sets.
std::set<int> setIntersection(
    const std::set<int>& first,
    const std::set<int>& second
);

// Returns the union of two sets.
std::set<int> setUnionValues(
    const std::set<int>& first,
    const std::set<int>& second
);

// Returns the values that exist in the first set but not in the second set.
std::set<int> setDifferenceValues(
    const std::set<int>& first,
    const std::set<int>& second
);

} // namespace cookbook::associative