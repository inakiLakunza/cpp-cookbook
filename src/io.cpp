#include "cookbook/io.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

namespace cookbook::io {
namespace {

std::ifstream openInputFile(const std::string& path, std::ios::openmode mode = std::ios::in) {
    std::ifstream file(path, mode);

    if (!file) {
        throw std::runtime_error("Could not open file for reading: " + path);
    }

    return file;
}

std::ofstream openOutputFile(const std::string& path, std::ios::openmode mode = std::ios::out) {
    std::ofstream file(path, mode);

    if (!file) {
        throw std::runtime_error("Could not open file for writing: " + path);
    }

    return file;
}

void removeTrailingCarriageReturn(std::string& line) {
    if (!line.empty() && line.back() == '\r') {
        line.pop_back();
    }
}

std::vector<std::string> parseCsvLine(const std::string& line) {
    std::vector<std::string> fields;
    std::string current_field;
    bool inside_quotes = false;

    for (std::size_t i = 0; i < line.size(); ++i) {
        const char current_char = line[i];

        if (inside_quotes) {
            if (current_char == '"') {
                const bool is_escaped_quote =
                    i + 1 < line.size() && line[i + 1] == '"';

                if (is_escaped_quote) {
                    current_field.push_back('"');
                    ++i;
                } else {
                    inside_quotes = false;

                    if (i + 1 < line.size() && line[i + 1] != ',') {
                        throw std::runtime_error("Malformed CSV line: unexpected character after quote");
                    }
                }
            } else {
                current_field.push_back(current_char);
            }
        } else {
            if (current_char == ',') {
                fields.push_back(current_field);
                current_field.clear();
            } else if (current_char == '"') {
                if (!current_field.empty()) {
                    throw std::runtime_error("Malformed CSV line: quote inside unquoted field");
                }

                inside_quotes = true;
            } else {
                current_field.push_back(current_char);
            }
        }
    }

    if (inside_quotes) {
        throw std::runtime_error("Malformed CSV line: missing closing quote");
    }

    fields.push_back(current_field);
    return fields;
}

std::string escapeCsvField(const std::string& field) {
    const bool needs_quotes =
        field.find(',') != std::string::npos ||
        field.find('"') != std::string::npos ||
        field.find('\n') != std::string::npos ||
        field.find('\r') != std::string::npos;

    if (!needs_quotes) {
        return field;
    }

    std::string escaped = "\"";

    for (char c : field) {
        if (c == '"') {
            escaped += "\"\"";
        } else {
            escaped.push_back(c);
        }
    }

    escaped.push_back('"');
    return escaped;
}

} // namespace

std::vector<std::string> readLines(const std::string& path) {
    std::ifstream file = openInputFile(path);

    std::vector<std::string> lines;
    std::string line;

    while (std::getline(file, line)) {
        removeTrailingCarriageReturn(line);
        lines.push_back(line);
    }

    if (file.bad()) {
        throw std::runtime_error("Error while reading file: " + path);
    }

    return lines;
}

void writeLines(const std::string& path, const std::vector<std::string>& lines) {
    std::ofstream file = openOutputFile(path);

    for (const std::string& line : lines) {
        file << line << '\n';
    }

    if (!file) {
        throw std::runtime_error("Error while writing file: " + path);
    }
}

void appendLine(const std::string& path, const std::string& line) {
    std::ofstream file = openOutputFile(path, std::ios::out | std::ios::app);

    file << line << '\n';

    if (!file) {
        throw std::runtime_error("Error while appending to file: " + path);
    }
}

std::string readWholeFile(const std::string& path) {
    std::ifstream file = openInputFile(path, std::ios::in | std::ios::binary);

    std::ostringstream buffer;
    buffer << file.rdbuf();

    if (file.bad()) {
        throw std::runtime_error("Error while reading file: " + path);
    }

    return buffer.str();
}

void writeWholeFile(const std::string& path, const std::string& contents) {
    std::ofstream file = openOutputFile(path, std::ios::out | std::ios::binary);

    file << contents;

    if (!file) {
        throw std::runtime_error("Error while writing file: " + path);
    }
}

bool fileExists(const std::string& path) {
    std::ifstream file(path, std::ios::in | std::ios::binary);
    return file.good();
}

std::size_t countLines(const std::string& path) {
    std::ifstream file = openInputFile(path);

    std::size_t count = 0;
    std::string line;

    while (std::getline(file, line)) {
        ++count;
    }

    if (file.bad()) {
        throw std::runtime_error("Error while counting lines in file: " + path);
    }

    return count;
}

std::vector<std::vector<std::string>> readCsvFile(const std::string& path) {
    std::ifstream file = openInputFile(path);

    std::vector<std::vector<std::string>> rows;
    std::string line;

    while (std::getline(file, line)) {
        removeTrailingCarriageReturn(line);
        rows.push_back(parseCsvLine(line));
    }

    if (file.bad()) {
        throw std::runtime_error("Error while reading CSV file: " + path);
    }

    return rows;
}

void writeCsvFile(
    const std::string& path,
    const std::vector<std::vector<std::string>>& rows
) {
    std::ofstream file = openOutputFile(path);

    for (const std::vector<std::string>& row : rows) {
        for (std::size_t i = 0; i < row.size(); ++i) {
            if (i > 0) {
                file << ',';
            }

            file << escapeCsvField(row[i]);
        }

        file << '\n';
    }

    if (!file) {
        throw std::runtime_error("Error while writing CSV file: " + path);
    }
}

std::vector<std::string> readWordsFromFile(const std::string& path) {
    std::ifstream file = openInputFile(path);

    std::vector<std::string> words;
    std::string word;

    while (file >> word) {
        words.push_back(word);
    }

    if (file.bad()) {
        throw std::runtime_error("Error while reading words from file: " + path);
    }

    return words;
}

std::vector<double> readNumbersFromFile(const std::string& path) {
    std::ifstream file = openInputFile(path);

    std::vector<double> numbers;
    std::string token;

    while (file >> token) {
        std::size_t parsed_chars = 0;

        try {
            const double value = std::stod(token, &parsed_chars);

            if (parsed_chars != token.size()) {
                throw std::runtime_error("Invalid number token: " + token);
            }

            numbers.push_back(value);
        } catch (const std::exception&) {
            throw std::runtime_error("Invalid number token: " + token);
        }
    }

    if (file.bad()) {
        throw std::runtime_error("Error while reading numbers from file: " + path);
    }

    return numbers;
}

void copyFileContents(
    const std::string& source_path,
    const std::string& destination_path
) {
    if (source_path == destination_path) {
        throw std::runtime_error("Source and destination paths are the same: " + source_path);
    }

    std::ifstream source = openInputFile(source_path, std::ios::in | std::ios::binary);
    std::ofstream destination = openOutputFile(destination_path, std::ios::out | std::ios::binary);

    destination << source.rdbuf();

    if (!destination) {
        throw std::runtime_error("Error while copying to file: " + destination_path);
    }

    if (source.bad()) {
        throw std::runtime_error("Error while reading source file: " + source_path);
    }
}

} // namespace cookbook::io