cmake_minimum_required(VERSION 3.10)
project(huffman_compression)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_library(huffman_lib
    src/bit_stream.cpp
    src/file_compressor.cpp
    src/frequency_counter.cpp
    src/huffman_codec.cpp
    src/huffman_tree.cpp
)

target_include_directories(huffman_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(huffman_tests
    tests/frequency_counter_test.cpp
)

target_link_libraries(huffman_tests
    PRIVATE
    huffman_lib
    GTest::gtest
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(huffman_tests)