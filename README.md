# C++ Cookbook

Personal C++ cookbook with reusable, well-tested utility functions and common STL patterns.

The goal of this repo is to keep practical C++ logic organized by topic, so common operations can be reviewed, reused, and adapted quickly.

This is not meant to be a large framework or a heavily generic template library. The priority is:

* Correctness
* Readability
* Safe C++17 style
* Clear STL usage
* Easy modification
* Small examples and tests

---

## Repository Structure

```text
cpp-cookbook/
├── include/
│   └── cookbook/
│       ├── strings.hpp
│       ├── vectors.hpp
│       ├── associative.hpp
│       ├── algorithms.hpp
│       ├── graph.hpp
│       ├── comparisons.hpp
│       ├── iteration.hpp
│       ├── parsing.hpp
│       ├── numeric.hpp
│       ├── queues_stacks.hpp
│       ├── io.hpp
│       └── errors_validation.hpp
├── src/
│   ├── strings.cpp
│   ├── vectors.cpp
│   ├── associative.cpp
│   ├── algorithms.cpp
│   ├── graph.cpp
│   ├── comparisons.cpp
│   ├── iteration.cpp
│   ├── parsing.cpp
│   ├── numeric.cpp
│   ├── queues_stacks.cpp
│   ├── io.cpp
│   └── errors_validation.cpp
├── examples/
│   ├── strings_example.cpp
│   ├── vectors_example.cpp
│   └── ...
├── tests/
│   ├── test_strings.cpp
│   ├── test_vectors.cpp
│   └── ...
├── CMakeLists.txt
└── README.md
```

---

## Categories

### `strings`

String manipulation utilities.

Examples:

* Trim whitespace
* Convert to lowercase / uppercase
* Split strings
* Join strings
* Check prefixes and suffixes
* Replace substrings
* Normalize spaces

---

### `vectors`

Common `std::vector` utilities.

Examples:

* Check if a value exists
* Find index of a value
* Remove values
* Remove duplicates
* Filter values
* Transform values
* Compute sum / average
* Slice vectors
* Reverse copies

---

### `associative`

Utilities for associative containers.

Main containers:

* `std::map`
* `std::unordered_map`
* `std::set`
* `std::unordered_set`

Examples:

* Count frequencies
* Check if a key exists
* Get sorted keys
* Merge frequency maps
* Find top-k frequent values

---

### `algorithms`

Reusable STL algorithm patterns.

Examples:

* `std::find`
* `std::find_if`
* `std::sort`
* `std::stable_sort`
* `std::binary_search`
* `std::lower_bound`
* `std::upper_bound`
* `std::partition`

---

### `graph`

Graph traversal and graph algorithms.

Examples:

* BFS
* DFS recursive
* DFS iterative
* Shortest path in an unweighted graph
* Connected components
* Cycle detection
* Topological sort

---

### `comparisons`

Custom comparison logic.

Examples:

* Sort structs by one field
* Sort structs by multiple fields
* Sort pairs
* Custom priority queues
* Min-heaps and max-heaps
* `operator<` examples

---

### `iteration`

Correct traversal patterns.

Examples:

* Range-based loops by value
* Range-based loops by reference
* Range-based loops by const reference
* Index-based loops
* Iterator-based loops
* Erasing while iterating
* Iterating maps, sets, and unordered containers

---

### `parsing`

Utilities for converting raw strings into structured data.

Examples:

* Parse integers
* Parse doubles
* Safe parsing with validation
* Split by whitespace
* Parse CSV-style lines
* Parse key-value strings
* Parse log lines

---

### `numeric`

Basic numeric and ML-adjacent utilities.

Examples:

* Sum
* Mean
* Variance
* Standard deviation
* Clamp
* Normalize
* Argmax
* Argmin
* Dot product
* Euclidean distance

---

### `queues_stacks`

Queue-like containers and common use cases.

Main containers:

* `std::queue`
* `std::stack`
* `std::deque`
* `std::priority_queue`

Examples:

* Task processing
* Priority queues
* Sliding windows
* BFS support structures

---

### `io`

Input/output utilities.

Examples:

* Read file lines
* Write file lines
* Read whole file
* Append to file
* Parse file line by line
* Check if a file exists

---

### `errors_validation`

Validation and defensive programming helpers.

Examples:

* Check non-empty containers
* Check index bounds
* Check matching sizes
* Validate matrix dimensions
* Use `std::optional`
* Use exceptions for invalid input

---

## Code Style

General rules:

* Use C++17.
* Do not use `using namespace std`.
* Prefer `std::vector`, `std::string`, and STL containers directly.
* Prefer safe standard library utilities over manual memory management.
* Avoid raw `new` and `delete`.
* Prefer returning values instead of printing inside reusable functions.
* Keep functions small and focused.
* Make edge cases explicit.
* Add tests for every function.

Function declaration style:

```cpp
// Converts all alphabetic characters in the string to lowercase.
std::string toLower(const std::string& text);
```

Implementation style:

```cpp
std::string toLower(const std::string& text) {
    std::string result = text;

    for (char& ch : result) {
        ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
    }

    return result;
}
```

Comments should be useful but not excessive.

Use:

```cpp
// Skip empty tokens produced by repeated delimiters.
```

Avoid:

```cpp
// Loop over the string.
// Increment i.
// Return result.
```

---

## Header / Source Convention

Each category has:

```text
include/cookbook/category.hpp
src/category.cpp
examples/category_example.cpp
tests/test_category.cpp
```

The header contains public declarations.

The source file contains implementations.

The example file shows basic usage.

The test file checks correctness and edge cases.

---

## Namespaces

All functions should use the `cookbook` namespace.

Recommended structure:

```cpp
namespace cookbook::strings {

std::string trim(const std::string& text);

}
```

Example usage:

```cpp
#include "cookbook/strings.hpp"

#include <iostream>

int main() {
    std::string text = "  Hello C++  ";
    std::cout << cookbook::strings::trim(text) << "\n";
}
```

---

## Building Examples Manually

Example compile command:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic \
    examples/strings_example.cpp src/strings.cpp \
    -Iinclude \
    -o strings_example
```

Run:

```bash
./strings_example
```

On Windows/MSYS2, the output executable may be:

```bash
./strings_example.exe
```

---

## Testing Manually

Example compile command:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic \
    tests/test_strings.cpp src/strings.cpp \
    -Iinclude \
    -o test_strings
```

Run:

```bash
./test_strings
```

Tests can start simple, using `assert`:

```cpp
#include "cookbook/strings.hpp"

#include <cassert>

int main() {
    assert(cookbook::strings::trim("  hello  ") == "hello");
    assert(cookbook::strings::trim("") == "");
}
```

---

## Development Order

Recommended order for filling the repo:

1. `strings`
2. `vectors`
3. `iteration`
4. `associative`
5. `comparisons`
6. `algorithms`
7. `queues_stacks`
8. `graph`
9. `parsing`
10. `numeric`
11. `io`
12. `errors_validation`

This order starts with the most common containers and operations, then moves toward more complex patterns.

---

## Goal

This repo should become a personal reference for:

* C++ syntax patterns
* STL usage
* Common interview-style utilities
* Clean reusable code
* Small tested examples
* Data structure and algorithm practice

Every function should be understandable, reusable, and easy to modify for a real problem.
