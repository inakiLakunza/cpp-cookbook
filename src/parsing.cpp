#include "cookbook/parsing.hpp"

#include <cctype>
#include <cstdlib>
#include <sstream>
#include <stdexcept>

namespace cookbook::parsing {
namespace {

bool isWhitespace(char c) {
    return std::isspace(static_cast<unsigned char>(c)) != 0;
}

bool isWordCharacter(char c) {
    return std::isalnum(static_cast<unsigned char>(c)) != 0;
}

bool canStartNumber(const std::string& text, std::size_t index) {
    const char current = text[index];

    if (std::isdigit(static_cast<unsigned char>(current)) != 0) {
        return true;
    }

    if (current == '.') {
        return index + 1 < text.size()
            && std::isdigit(static_cast<unsigned char>(text[index + 1])) != 0;
    }

    if (current == '+' || current == '-') {
        if (index + 1 >= text.size()) {
            return false;
        }

        const char next = text[index + 1];

        if (std::isdigit(static_cast<unsigned char>(next)) != 0) {
            return true;
        }

        return next == '.'
            && index + 2 < text.size()
            && std::isdigit(static_cast<unsigned char>(text[index + 2])) != 0;
    }

    return false;
}

} // namespace

std::string trimBeforeParsing(const std::string& text) {
    std::size_t start = 0;

    while (start < text.size() && isWhitespace(text[start])) {
        ++start;
    }

    if (start == text.size()) {
        return "";
    }

    std::size_t end = text.size() - 1;

    while (end > start && isWhitespace(text[end])) {
        --end;
    }

    return text.substr(start, end - start + 1);
}

std::vector<std::string> splitByWhitespace(const std::string& text) {
    std::vector<std::string> tokens;
    std::istringstream stream(text);

    std::string token;
    while (stream >> token) {
        tokens.push_back(token);
    }

    return tokens;
}

std::vector<std::string> splitByDelimiter(
    const std::string& text,
    char delimiter
) {
    std::vector<std::string> tokens;
    std::size_t start = 0;

    for (std::size_t i = 0; i <= text.size(); ++i) {
        if (i == text.size() || text[i] == delimiter) {
            tokens.push_back(text.substr(start, i - start));
            start = i + 1;
        }
    }

    return tokens;
}

int parseInt(const std::string& text) {
    const std::string trimmed = trimBeforeParsing(text);

    if (trimmed.empty()) {
        throw std::invalid_argument("Cannot parse empty string as int");
    }

    std::size_t parsedCharacters = 0;
    const int value = std::stoi(trimmed, &parsedCharacters);

    if (parsedCharacters != trimmed.size()) {
        throw std::invalid_argument("String contains extra characters after int");
    }

    return value;
}

double parseDouble(const std::string& text) {
    const std::string trimmed = trimBeforeParsing(text);

    if (trimmed.empty()) {
        throw std::invalid_argument("Cannot parse empty string as double");
    }

    std::size_t parsedCharacters = 0;
    const double value = std::stod(trimmed, &parsedCharacters);

    if (parsedCharacters != trimmed.size()) {
        throw std::invalid_argument("String contains extra characters after double");
    }

    return value;
}

std::optional<int> safeParseInt(const std::string& text) {
    try {
        return parseInt(text);
    } catch (const std::exception&) {
        return std::nullopt;
    }
}

std::optional<double> safeParseDouble(const std::string& text) {
    try {
        return parseDouble(text);
    } catch (const std::exception&) {
        return std::nullopt;
    }
}

std::vector<std::string> parseCsvLine(const std::string& line) {
    std::vector<std::string> fields;
    std::string currentField;
    bool insideQuotes = false;

    for (std::size_t i = 0; i < line.size(); ++i) {
        const char current = line[i];

        if (insideQuotes) {
            if (current == '"') {
                const bool escapedQuote = i + 1 < line.size() && line[i + 1] == '"';

                if (escapedQuote) {
                    currentField.push_back('"');
                    ++i;
                } else {
                    insideQuotes = false;
                }
            } else {
                currentField.push_back(current);
            }
        } else {
            if (current == '"') {
                if (currentField.empty()) {
                    insideQuotes = true;
                } else {
                    currentField.push_back(current);
                }
            } else if (current == ',') {
                fields.push_back(currentField);
                currentField.clear();
            } else {
                currentField.push_back(current);
            }
        }
    }

    if (insideQuotes) {
        throw std::invalid_argument("CSV line has an unclosed quoted field");
    }

    fields.push_back(currentField);
    return fields;
}

std::optional<std::pair<std::string, std::string>> parseKeyValuePair(
    const std::string& text,
    char delimiter
) {
    const std::size_t delimiterPosition = text.find(delimiter);

    if (delimiterPosition == std::string::npos) {
        return std::nullopt;
    }

    const std::string key = trimBeforeParsing(text.substr(0, delimiterPosition));
    const std::string value = trimBeforeParsing(text.substr(delimiterPosition + 1));

    if (key.empty()) {
        return std::nullopt;
    }

    return std::make_pair(key, value);
}

std::unordered_map<std::string, std::string> parseKeyValueMap(
    const std::string& text,
    char pairDelimiter,
    char keyValueDelimiter
) {
    std::unordered_map<std::string, std::string> result;
    const std::vector<std::string> pairs = splitByDelimiter(text, pairDelimiter);

    for (const std::string& rawPair : pairs) {
        const std::string trimmedPair = trimBeforeParsing(rawPair);

        if (trimmedPair.empty()) {
            continue;
        }

        const std::optional<std::pair<std::string, std::string>> parsedPair =
            parseKeyValuePair(trimmedPair, keyValueDelimiter);

        if (!parsedPair.has_value()) {
            throw std::invalid_argument("Invalid key-value pair: " + trimmedPair);
        }

        // If a key appears multiple times, the last value wins.
        result[parsedPair->first] = parsedPair->second;
    }

    return result;
}

LogLine parseLogLine(const std::string& line) {
    std::istringstream stream(trimBeforeParsing(line));

    LogLine log;
    if (!(stream >> log.time >> log.service >> log.severity >> log.owner)) {
        throw std::invalid_argument(
            "Log line must contain at least time, service, severity, and owner"
        );
    }

    std::string restOfLine;
    std::getline(stream, restOfLine);
    log.message = trimBeforeParsing(restOfLine);

    return log;
}

std::vector<std::string> parseWords(const std::string& text) {
    std::vector<std::string> words;
    std::string currentWord;

    for (char c : text) {
        if (isWordCharacter(c)) {
            currentWord.push_back(c);
        } else if (!currentWord.empty()) {
            words.push_back(currentWord);
            currentWord.clear();
        }
    }

    if (!currentWord.empty()) {
        words.push_back(currentWord);
    }

    return words;
}

std::vector<double> parseNumbersFromLine(const std::string& line) {
    std::vector<double> numbers;
    std::size_t index = 0;

    while (index < line.size()) {
        if (!canStartNumber(line, index)) {
            ++index;
            continue;
        }

        const char* start = line.c_str() + index;
        char* end = nullptr;

        const double value = std::strtod(start, &end);

        if (end != start) {
            numbers.push_back(value);
            index = static_cast<std::size_t>(end - line.c_str());
        } else {
            ++index;
        }
    }

    return numbers;
}

bool validateTokenCount(
    const std::vector<std::string>& tokens,
    std::size_t expectedCount
) {
    return tokens.size() == expectedCount;
}

std::vector<std::string> removeEmptyTokens(
    const std::vector<std::string>& tokens
) {
    std::vector<std::string> result;

    for (const std::string& token : tokens) {
        if (!token.empty()) {
            result.push_back(token);
        }
    }

    return result;
}

} // namespace cookbook::parsing