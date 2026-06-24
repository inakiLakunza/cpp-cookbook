#include "cookbook/io.hpp"

#include <iostream>
#include <map>
#include <string>
#include <vector>

int main() {
    const std::string text_path = "example_notes.txt";
    const std::string csv_path = "example_people.csv";
    const std::string copy_path = "example_notes_copy.txt";

    cookbook::io::writeLines(text_path, {
        "first line",
        "second line",
        "third line"
    });

    cookbook::io::appendLine(text_path, "fourth line");

    const std::vector<std::string> lines = cookbook::io::readLines(text_path);

    std::cout << "Lines:\n";
    for (const std::string& line : lines) {
        std::cout << "- " << line << '\n';
    }

    std::cout << "\nWhole file:\n";
    std::cout << cookbook::io::readWholeFile(text_path) << '\n';

    std::cout << "Line count: " << cookbook::io::countLines(text_path) << '\n';

    cookbook::io::writeCsvFile(csv_path, {
        {"name", "age", "city"},
        {"Ana", "30", "Madrid"},
        {"Mark", "25", "Zurich"},
        {"Sara", "28", "New York, USA"}
    });

    const std::vector<std::vector<std::string>> csv_rows =
        cookbook::io::readCsvFile(csv_path);

    std::cout << "\nCSV rows:\n";
    for (const std::vector<std::string>& row : csv_rows) {
        cookbook::io::printVectorToStream(row, std::cout, " | ");
        std::cout << '\n';
    }

    cookbook::io::copyFileContents(text_path, copy_path);

    std::cout << "\nCopied file exists: "
              << cookbook::io::fileExists(copy_path)
              << '\n';

    const std::vector<int> scores = {10, 20, 30};
    std::cout << "\nVector: ";
    cookbook::io::printVectorToStream(scores, std::cout, ", ");
    std::cout << '\n';

    const std::map<std::string, int> counts = {
        {"errors", 3},
        {"warnings", 7}
    };

    std::cout << "\nMap:\n";
    cookbook::io::printMapToStream(counts, std::cout);
    std::cout << '\n';

    return 0;
}