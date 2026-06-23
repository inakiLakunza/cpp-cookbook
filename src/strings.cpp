#include "cookbook/strings.hpp"

#include <algorithm>
#include <cctype>

namespace cookbook::strings {

std::string ltrim(const std::string& text) {
    auto firstNonSpace = std::find_if(
        text.begin(),
        text.end(),
        [](unsigned char ch) {
            return !std::isspace(ch);
        }
    );

    return std::string(firstNonSpace, text.end());
}

std::string rtrim(const std::string& text) {
    auto firstNonSpaceFromRight = std::find_if(
        text.rbegin(),
        text.rend(),
        [](unsigned char ch) {
            return !std::isspace(ch);
        }
    );

    return std::string(text.begin(), firstNonSpaceFromRight.base());
}

std::string trim(const std::string& text) {
    return ltrim(rtrim(text));
}

std::string toLower(const std::string& text) {
    std::string result = text;

    std::transform(
        result.begin(),
        result.end(),
        result.begin(),
        [](unsigned char ch) {
            return static_cast<char>(std::tolower(ch));
        }
    );

    return result;
}

std::string toUpper(const std::string& text) {
    std::string result = text;

    std::transform(
        result.begin(),
        result.end(),
        result.begin(),
        [](unsigned char ch) {
            return static_cast<char>(std::toupper(ch));
        }
    );

    return result;
}

std::vector<std::string> split(const std::string& text, char delimiter) {
    std::vector<std::string> result;

    std::size_t start = 0;

    while (true) {
        std::size_t delimiterPos = text.find(delimiter, start);

        if (delimiterPos == std::string::npos) {
            result.push_back(text.substr(start));
            break;
        }

        result.push_back(text.substr(start, delimiterPos - start));
        start = delimiterPos + 1;
    }

    return result;
}

std::string join(const std::vector<std::string>& parts, const std::string& delimiter) {
    if (parts.empty()) {
        return "";
    }

    std::string result = parts[0];

    for (std::size_t i = 1; i < parts.size(); ++i) {
        result += delimiter;
        result += parts[i];
    }

    return result;
}

bool startsWith(const std::string& text, const std::string& prefix) {
    if (prefix.size() > text.size()) {
        return false;
    }

    return text.compare(0, prefix.size(), prefix) == 0;
}

bool endsWith(const std::string& text, const std::string& suffix) {
    if (suffix.size() > text.size()) {
        return false;
    }

    return text.compare(text.size() - suffix.size(), suffix.size(), suffix) == 0;
}

bool contains(const std::string& text, const std::string& substring) {
    return text.find(substring) != std::string::npos;
}

std::string replaceAll(
    const std::string& text,
    const std::string& from,
    const std::string& to
) {
    if (from.empty()) {
        return text;
    }

    std::string result = text;
    std::size_t pos = 0;

    while ((pos = result.find(from, pos)) != std::string::npos) {
        result.replace(pos, from.size(), to);
        pos += to.size();
    }

    return result;
}

std::string removeExtraSpaces(const std::string& text) {
    std::string result;
    bool previousWasSpace = false;

    for (unsigned char ch : text) {
        if (std::isspace(ch)) {
            if (!result.empty() && !previousWasSpace) {
                result += ' ';
            }

            previousWasSpace = true;
        } else {
            result += static_cast<char>(ch);
            previousWasSpace = false;
        }
    }

    return rtrim(result);
}

} // namespace cookbook::strings