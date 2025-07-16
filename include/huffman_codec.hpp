#ifndef HUFFMAN_CODEC_HPP
#define HUFFMAN_CODEC_HPP

#include "huffman_tree.hpp"
#include "bit_stream.hpp"
#include <optional>

class HuffmanEncoder{
    private:
        const std::unordered_map<char, std::string>& huffman_codes;
        BitWriter bit_writer;

    public:
        HuffmanEncoder(const std::unordered_map<char, std::string>& codes, const std::string& output_file);
        void encode(const std::string& input_data);
        void finish();
};

class HuffmanDecoder {
    private:
        huffman_node* root;
        BitReader& bit_reader;

    public:
        HuffmanDecoder(huffman_node* huffman_tree_root, BitReader& reader);
        void decode(const std::string& output_file);
};



#endif