add_executable(frequency_counter_test 
    frequency_counter_test.cpp
    huffman_tree_test.cpp
    huffman_codec_test.cpp
)

target_link_libraries(frequency_counter_test
    PRIVATE
    GTest::gtest
    GTest::gtest_main
    project_library 
)

include(GoogleTest)
gtest_discover_tests(frequency_counter_test) 