#pragma once
#include <cstddef>
#include <map>
#include <ostream>
#include <string>
#include <vector>

namespace cookbook::io {

// Reads all lines from a text file, excluding newline characters.
std::vector<std::string> readLines(const std::string& path);

// Writes lines to a text file, replacing existing contents.
void writeLines(const std::string& path, const std::vector<std::string>& lines);

// Appends one line to the end of a text file.
void appendLine(const std::string& path, const std::string& line);

// Reads the entire contents of a file into one string.
std::string readWholeFile(const std::string& path);

// Writes one string to a file, replacing existing contents.
void writeWholeFile(const std::string& path, const std::string& contents);

// Returns true if a file can be opened for reading.
bool fileExists(const std::string& path);

// Counts the number of lines in a text file.
std::size_t countLines(const std::string& path);

// Reads a simple CSV file into rows and columns.
std::vector<std::vector<std::string>> readCsvFile(const std::string& path);

// Writes rows and columns to a simple CSV file.
void writeCsvFile(
    const std::string& path,
    const std::vector<std::vector<std::string>>& rows
);

// Reads whitespace-separated words from a file.
std::vector<std::string> readWordsFromFile(const std::string& path);

// Reads whitespace-separated numbers from a file.
std::vector<double> readNumbersFromFile(const std::string& path);

// Copies the full contents of one file into another file.
void copyFileContents(
    const std::string& source_path,
    const std::string& destination_path
);

// Prints a vector to an output stream using a separator.
template <typename T>
void printVectorToStream(
    const std::vector<T>& values,
    std::ostream& output,
    const std::string& separator = " "
) {
    for (std::size_t i = 0; i < values.size(); ++i) {
        if (i > 0) {
            output << separator;
        }

        output << values[i];
    }
}

// Prints a map to an output stream using configurable separators.
template <typename Key, typename Value>
void printMapToStream(
    const std::map<Key, Value>& values,
    std::ostream& output,
    const std::string& pair_separator = ": ",
    const std::string& entry_separator = "\n"
) {
    std::size_t index = 0;

    for (const auto& entry : values) {
        if (index > 0) {
            output << entry_separator;
        }

        output << entry.first << pair_separator << entry.second;
        ++index;
    }
}

} // namespace cookbook::io