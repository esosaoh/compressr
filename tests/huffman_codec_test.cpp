#include <gtest/gtest.h>
#include "huffman_codec.hpp"
#include "bit_stream.hpp"

TEST(EncodingTest, SingleCharacter) {
    std::unordered_map<char, std::string> huffman_codes = {{'a', "0"}};
    HuffmanEncoder encoder(huffman_codes, "encoded.bin");
    encoder.encode("a");
    encoder.finish();

    // Read the encoded file and verify the bits
    BitReader bit_reader("encoded.bin");
    auto bit = bit_reader.read_bit();
    EXPECT_TRUE(bit.has_value()); 
    EXPECT_EQ(*bit, false);
}

TEST(DecodingTest, SingleCharacter) {
    huffman_node* root = new huffman_node('a', 1);
    BitReader bit_reader("encoded.bin");
    HuffmanDecoder decoder(root, bit_reader);
    std::ofstream out_file("decoded.txt");
    decoder.decode("decoded.txt");
    out_file.close();

    // Verify the decoded file
    std::ifstream in_file("decoded.txt");
    std::string content((std::istreambuf_iterator<char>(in_file)), std::istreambuf_iterator<char>());
    EXPECT_EQ(content, "a");
    delete_tree(root);
}