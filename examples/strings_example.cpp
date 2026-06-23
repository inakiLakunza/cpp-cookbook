#include "cookbook/strings.hpp"

#include <iostream>
#include <string>
#include <vector>

int main() {
    const std::string raw = "   Hello   C++   World   ";

    std::cout << "trim:\n";
    std::cout << "[" << cookbook::strings::trim(raw) << "]\n";
    // Expected: [Hello   C++   World]

    std::cout << "\nremoveExtraSpaces:\n";
    std::cout << "[" << cookbook::strings::removeExtraSpaces(raw) << "]\n";
    // Expected: [Hello C++ World]

    std::cout << "\ntoLower / toUpper:\n";
    std::cout << cookbook::strings::toLower("HeLLo") << "\n";
    // Expected: hello

    std::cout << cookbook::strings::toUpper("HeLLo") << "\n";
    // Expected: HELLO

    std::cout << "\nsplit:\n";
    std::vector<std::string> words = cookbook::strings::split("auth,error,ana", ',');

    for (const std::string& word : words) {
        std::cout << "[" << word << "]\n";
    }
    // Expected:
    // [auth]
    // [error]
    // [ana]

    std::cout << "\njoin:\n";
    std::cout << cookbook::strings::join(words, " | ") << "\n";
    // Expected: auth | error | ana

    std::cout << "\nstartsWith / endsWith / contains:\n";
    std::cout << std::boolalpha;
    std::cout << cookbook::strings::startsWith("error.log", "error") << "\n";
    // Expected: true

    std::cout << cookbook::strings::endsWith("error.log", ".log") << "\n";
    // Expected: true

    std::cout << cookbook::strings::contains("Production outage", "outage") << "\n";
    // Expected: true

    std::cout << "\nreplaceAll:\n";
    std::cout << cookbook::strings::replaceAll("one two one", "one", "1") << "\n";
    // Expected: 1 two 1

    return 0;
}