#include <gtest/gtest.h>
#include "file_compressor.hpp"
#include <fstream>

TEST(CompressFileTest, RegularFile) {
    const std::string input_file = "../tests/test_input.txt";
    const std::string output_file = "../tests/compressed.bin";

    compress_file(input_file, output_file);

    std::ifstream compressed_file(output_file);
    ASSERT_TRUE(compressed_file.is_open());
    compressed_file.close();
}

TEST(DecompressFileTest, RegularFile) {
    const std::string input_file = "../tests/compressed.bin";
    const std::string output_file = "../tests/decompressed.txt";

    decompress_file(input_file, output_file);

    std::ifstream decompressed_file(output_file);
    ASSERT_TRUE(decompressed_file.is_open());

    std::string content((std::istreambuf_iterator<char>(decompressed_file)), std::istreambuf_iterator<char>());
    decompressed_file.close();

    std::ifstream original_file("../tests/test_input.txt");
    std::string original_content((std::istreambuf_iterator<char>(original_file)), std::istreambuf_iterator<char>());
    original_file.close();

    EXPECT_EQ(content, original_content);
}