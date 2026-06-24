#include "cookbook/parsing.hpp"

#include <iostream>
#include <string>
#include <vector>

namespace {

void printStrings(const std::vector<std::string>& values) {
    std::cout << "[";

    for (std::size_t i = 0; i < values.size(); ++i) {
        std::cout << '"' << values[i] << '"';

        if (i + 1 < values.size()) {
            std::cout << ", ";
        }
    }

    std::cout << "]\n";
}

void printNumbers(const std::vector<double>& values) {
    std::cout << "[";

    for (std::size_t i = 0; i < values.size(); ++i) {
        std::cout << values[i];

        if (i + 1 < values.size()) {
            std::cout << ", ";
        }
    }

    std::cout << "]\n";
}

} // namespace

int main() {
    const std::string raw = "   hello world   ";
    std::cout << cookbook::parsing::trimBeforeParsing(raw) << "\n";
    // Expected: hello world

    const std::vector<std::string> whitespaceTokens =
        cookbook::parsing::splitByWhitespace("  one   two three  ");
    printStrings(whitespaceTokens);
    // Expected: ["one", "two", "three"]

    const std::vector<std::string> delimiterTokens =
        cookbook::parsing::splitByDelimiter("a,,b,", ',');
    printStrings(delimiterTokens);
    // Expected: ["a", "", "b", ""]

    const int age = cookbook::parsing::parseInt(" 26 ");
    const double score = cookbook::parsing::parseDouble(" 8.85 ");
    std::cout << age << "\n";
    std::cout << score << "\n";
    // Expected:
    // 26
    // 8.85

    const std::optional<int> maybeNumber =
        cookbook::parsing::safeParseInt("abc");

    if (!maybeNumber.has_value()) {
        std::cout << "Invalid integer\n";
    }
    // Expected: Invalid integer

    const std::vector<std::string> csv =
        cookbook::parsing::parseCsvLine("ana,\"hello, world\",\"she said \"\"hi\"\"\"");
    printStrings(csv);
    // Expected: ["ana", "hello, world", "she said \"hi\""]

    const auto pair = cookbook::parsing::parseKeyValuePair(" name = ana ");

    if (pair.has_value()) {
        std::cout << pair->first << " -> " << pair->second << "\n";
    }
    // Expected: name -> ana

    const std::unordered_map<std::string, std::string> config =
        cookbook::parsing::parseKeyValueMap("host=localhost; port=8080; debug=true");

    std::cout << config.at("host") << "\n";
    std::cout << config.at("port") << "\n";
    std::cout << config.at("debug") << "\n";
    // Expected:
    // localhost
    // 8080
    // true

    const cookbook::parsing::LogLine log =
        cookbook::parsing::parseLogLine(
            "12:01 auth ERROR ana Login failed because password was wrong"
        );

    std::cout << log.time << "\n";
    std::cout << log.service << "\n";
    std::cout << log.severity << "\n";
    std::cout << log.owner << "\n";
    std::cout << log.message << "\n";
    // Expected:
    // 12:01
    // auth
    // ERROR
    // ana
    // Login failed because password was wrong

    const std::vector<std::string> words =
        cookbook::parsing::parseWords("Hello, C++17 parsing!");
    printStrings(words);
    // Expected: ["Hello", "C", "17", "parsing"]

    const std::vector<double> numbers =
        cookbook::parsing::parseNumbersFromLine("x=10 y=-2.5 z=.25 total=1e2");
    printNumbers(numbers);
    // Expected: [10, -2.5, 0.25, 100]

    return 0;
}