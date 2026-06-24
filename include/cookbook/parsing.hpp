#pragma once

#include <cstddef>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace cookbook::parsing {

struct LogLine {
    std::string time;
    std::string service;
    std::string severity;
    std::string owner;
    std::string message;
};

// Removes leading and trailing whitespace before parsing text.
std::string trimBeforeParsing(const std::string& text);

// Splits text into tokens separated by any whitespace.
std::vector<std::string> splitByWhitespace(const std::string& text);

// Splits text by one delimiter character, preserving empty tokens.
std::vector<std::string> splitByDelimiter(const std::string& text, char delimiter);

// Converts a full string into an int or throws if the whole string is not valid.
int parseInt(const std::string& text);

// Converts a full string into a double or throws if the whole string is not valid.
double parseDouble(const std::string& text);

// Converts a full string into an int, returning std::nullopt on failure.
std::optional<int> safeParseInt(const std::string& text);

// Converts a full string into a double, returning std::nullopt on failure.
std::optional<double> safeParseDouble(const std::string& text);

// Parses one CSV line, supporting quoted fields and escaped quotes.
std::vector<std::string> parseCsvLine(const std::string& line);

// Parses one key-value pair such as "name=ana", returning std::nullopt if invalid.
std::optional<std::pair<std::string, std::string>> parseKeyValuePair(
    const std::string& text,
    char delimiter = '='
);

// Parses a delimiter-separated key-value string into a map.
std::unordered_map<std::string, std::string> parseKeyValueMap(
    const std::string& text,
    char pairDelimiter = ';',
    char keyValueDelimiter = '='
);

// Parses a simple log line with format: time service severity owner message.
LogLine parseLogLine(const std::string& line);

// Extracts alphanumeric words from text, ignoring punctuation.
std::vector<std::string> parseWords(const std::string& text);

// Extracts all numbers found inside a line as doubles.
std::vector<double> parseNumbersFromLine(const std::string& line);

// Returns true if the number of tokens matches the expected count.
bool validateTokenCount(
    const std::vector<std::string>& tokens,
    std::size_t expectedCount
);

// Removes empty string tokens from a vector.
std::vector<std::string> removeEmptyTokens(
    const std::vector<std::string>& tokens
);

} // namespace cookbook::parsing