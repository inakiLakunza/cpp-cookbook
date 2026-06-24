#include "cookbook/associative.hpp"

#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

int main() {
    const std::vector<std::string> words = {
        "apple",
        "banana",
        "apple",
        "orange",
        "banana",
        "apple"
    };

    const std::unordered_map<std::string, int> frequencies =
        cookbook::associative::countFrequencies(words);

    std::cout << "apple count: "
              << cookbook::associative::getValueOrDefault(frequencies, "apple", 0)
              << '\n';

    std::cout << "grape count: "
              << cookbook::associative::getValueOrDefault(frequencies, "grape", 0)
              << '\n';

    const auto most_frequent = cookbook::associative::findMostFrequent(frequencies);

    if (most_frequent.has_value()) {
        std::cout << "most frequent: "
                  << most_frequent->first
                  << " = "
                  << most_frequent->second
                  << '\n';
    }

    const std::vector<std::pair<std::string, int>> top_two =
        cookbook::associative::topKFrequent(frequencies, 2);

    std::cout << "top 2 frequent values:\n";
    for (const auto& pair : top_two) {
        std::cout << pair.first << " -> " << pair.second << '\n';
    }

    const std::vector<std::pair<std::string, std::string>> users_by_team = {
        {"backend", "Ana"},
        {"frontend", "Mark"},
        {"backend", "Sara"},
        {"frontend", "John"}
    };

    const auto grouped = cookbook::associative::groupByKey(users_by_team);

    std::cout << "backend users:\n";
    for (const std::string& user : grouped.at("backend")) {
        std::cout << user << '\n';
    }

    const std::set<int> first = {1, 2, 3, 4};
    const std::set<int> second = {3, 4, 5, 6};

    const std::set<int> intersection =
        cookbook::associative::setIntersection(first, second);

    std::cout << "set intersection:\n";
    for (int value : intersection) {
        std::cout << value << '\n';
    }

    return 0;
}

/*
Expected output:

apple count: 3
grape count: 0
most frequent: apple = 3
top 2 frequent values:
apple -> 3
banana -> 2
backend users:
Ana
Sara
set intersection:
3
4
*/