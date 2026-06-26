#include "cookbook/io.hpp"

#include <iostream>
#include <map>
#include <string>
#include <vector>

int main() {
    const std::string directory_path = "example_data";
    const std::string nested_directory_path = "example_data/nested";

    cookbook::io::createDirectoryIfMissing(directory_path);
    cookbook::io::createDirectoryIfMissing(nested_directory_path);

    const std::string text_path = directory_path + "/notes.txt";
    const std::string csv_path = directory_path + "/people.csv";
    const std::string numbers_path = directory_path + "/numbers.txt";
    const std::string copy_path = directory_path + "/notes_copy.txt";
    const std::string nested_text_path = nested_directory_path + "/nested_notes.txt";
    const std::string ignored_path = directory_path + "/image.png";

    cookbook::io::writeLines(text_path, {
        "first line",
        "second line",
        "third line"
    });

    cookbook::io::appendLine(text_path, "fourth line");

    cookbook::io::writeWholeFile(numbers_path, "1 2.5 -3 4e2");
    cookbook::io::writeWholeFile(nested_text_path, "nested file\n");
    cookbook::io::writeWholeFile(ignored_path, "not a text file\n");

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

    const std::vector<double> numbers =
        cookbook::io::readNumbersFromFile(numbers_path);

    std::cout << "\nNumbers: ";
    cookbook::io::printVectorToStream(numbers, std::cout, ", ");
    std::cout << '\n';

    cookbook::io::copyFileContents(text_path, copy_path);

    std::cout << "\nCopied file exists: "
              << cookbook::io::fileExists(copy_path)
              << '\n';

    std::cout << "Directory exists: "
              << cookbook::io::directoryExists(directory_path)
              << '\n';

    std::cout << "\nFiles directly inside directory:\n";
    const std::vector<std::string> direct_files =
        cookbook::io::listFilesInDirectory(directory_path);

    for (const std::string& path : direct_files) {
        std::cout << "- " << path << '\n';
    }

    std::cout << "\nDirect .txt files:\n";
    const std::vector<std::string> direct_txt_files =
        cookbook::io::listFilesInDirectoryWithExtension(directory_path, ".txt");

    for (const std::string& path : direct_txt_files) {
        std::cout << "- " << path << '\n';
    }

    std::cout << "\nRecursive .txt files:\n";
    const std::vector<std::string> recursive_txt_files =
        cookbook::io::listFilesRecursivelyWithExtension(directory_path, "txt");

    for (const std::string& path : recursive_txt_files) {
        std::cout << "- " << path << '\n';
    }

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