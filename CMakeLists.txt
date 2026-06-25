cmake_minimum_required(VERSION 3.20)

project(cpp_cookbook LANGUAGES CXX)

add_library(cookbook
    src/strings.cpp
    src/vectors.cpp
    src/algorithms.cpp
    src/iteration.cpp
    src/associative.cpp
    src/numeric.cpp
    src/comparisons.cpp
    src/parsing.cpp
    src/errors_validation.cpp
    src/queues_stacks.cpp
    src/graph.cpp
    src/io.cpp
)

target_compile_features(cookbook PUBLIC cxx_std_17)

target_include_directories(cookbook PUBLIC
    include
)

target_compile_options(cookbook PRIVATE
    -Wall
    -Wextra
    -pedantic
)

add_executable(strings_example examples/strings_example.cpp)
target_link_libraries(strings_example PRIVATE cookbook)

add_executable(vectors_example examples/vectors_example.cpp)
target_link_libraries(vectors_example PRIVATE cookbook)

add_executable(algorithms_example examples/algorithms_example.cpp)
target_link_libraries(algorithms_example PRIVATE cookbook)

include(CTest)

if(BUILD_TESTING)
    add_executable(test_strings tests/test_strings.cpp)
    target_link_libraries(test_strings PRIVATE cookbook)
    add_test(NAME test_strings COMMAND test_strings)

    add_executable(test_vectors tests/test_vectors.cpp)
    target_link_libraries(test_vectors PRIVATE cookbook)
    add_test(NAME test_vectors COMMAND test_vectors)

    add_executable(test_algorithms tests/test_algorithms.cpp)
    target_link_libraries(test_algorithms PRIVATE cookbook)
    add_test(NAME test_algorithms COMMAND test_algorithms)

    add_executable(test_iteration tests/test_iteration.cpp)
    target_link_libraries(test_iteration PRIVATE cookbook)
    add_test(NAME test_iteration COMMAND test_iteration)

    add_executable(test_associative tests/test_associative.cpp)
    target_link_libraries(test_associative PRIVATE cookbook)
    add_test(NAME test_associative COMMAND test_associative)

    add_executable(test_numeric tests/test_numeric.cpp)
    target_link_libraries(test_numeric PRIVATE cookbook)
    add_test(NAME test_numeric COMMAND test_numeric)

    add_executable(test_comparisons tests/test_comparisons.cpp)
    target_link_libraries(test_comparisons PRIVATE cookbook)
    add_test(NAME test_comparisons COMMAND test_comparisons)

    add_executable(test_parsing tests/test_parsing.cpp)
    target_link_libraries(test_parsing PRIVATE cookbook)
    add_test(NAME test_parsing COMMAND test_parsing)

    add_executable(test_errors_validation tests/test_errors_validation.cpp)
    target_link_libraries(test_errors_validation PRIVATE cookbook)
    add_test(NAME test_errors_validation COMMAND test_errors_validation)

    add_executable(test_queues_stacks tests/test_queues_stacks.cpp)
    target_link_libraries(test_queues_stacks PRIVATE cookbook)
    add_test(NAME test_queues_stacks COMMAND test_queues_stacks)

    add_executable(test_graph tests/test_graph.cpp)
    target_link_libraries(test_graph PRIVATE cookbook)
    add_test(NAME test_graph COMMAND test_graph)

    add_executable(test_io tests/test_io.cpp)
    target_link_libraries(test_io PRIVATE cookbook)
    add_test(NAME test_io COMMAND test_io)
endif()