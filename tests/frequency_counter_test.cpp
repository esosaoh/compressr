#include <gtest/gtest.h>
#include <unordered_map>
#include "frequency_counter.hpp"

TEST(frequency_counter, char_freq) {
    std::unordered_map<char,int> freq_map = char_freq("../tests/test_input.txt");
    std::unordered_map<char,int> expected = {
        {'A', 2}, {'l', 8}, {' ', 28}, {'t', 9}, {'h', 7}, 
        {'e', 17}, {'w', 2}, {'o', 3}, {'r', 7}, {'d', 5}, 
        {'s', 8}, {'a', 13}, {'g', 1}, {',', 1}, {'n', 12},
        {'m', 6}, {'y', 5}, {'p', 3}, {';', 2}, {'T', 1}, {'v', 1}, 
        {'i', 6}, {'x', 1}, {'c', 1}, {'.', 1},
        {'\x99', 1}, {'\xE2', 1}, {'\x80', 1}  // UTF-8 characters for smart quotes and em-dash
    };
    ASSERT_EQ(freq_map, expected);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}