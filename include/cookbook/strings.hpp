#pragma once

#include <string>
#include <vector>

namespace cookbook::strings {

// Removes whitespace from the beginning of a string.
std::string ltrim(const std::string& text);

// Removes whitespace from the end of a string.
std::string rtrim(const std::string& text);

// Removes whitespace from both the beginning and end of a string.
std::string trim(const std::string& text);

// Returns a lowercase copy of the input string.
std::string toLower(const std::string& text);

// Returns an uppercase copy of the input string.
std::string toUpper(const std::string& text);

// Splits a string by a single-character delimiter, preserving empty fields.
std::vector<std::string> split(const std::string& text, char delimiter);

// Joins multiple strings using the given delimiter.
std::string join(const std::vector<std::string>& parts, const std::string& delimiter);

// Returns true if text starts with the given prefix.
bool startsWith(const std::string& text, const std::string& prefix);

// Returns true if text ends with the given suffix.
bool endsWith(const std::string& text, const std::string& suffix);

// Returns true if text contains the given substring.
bool contains(const std::string& text, const std::string& substring);

// Replaces all non-overlapping occurrences of from with to.
std::string replaceAll(
    const std::string& text,
    const std::string& from,
    const std::string& to
);

// Removes leading/trailing whitespace and collapses internal whitespace to single spaces.
std::string removeExtraSpaces(const std::string& text);

} // namespace cookbook::strings