#ifndef FILE_COMPRESSOR_HPP
#define FILE_COMPRESSOR_HPP

#include "huffman_tree.hpp"
#include "bit_stream.hpp"
#include <fstream>

void serialize_tree(huffman_node* root, BitWriter& bit_writer);
huffman_node* deserialize_tree(BitReader& bit_reader);
void compress_file(const std::string& input_file, const std::string& output_file);
void decompress_file(const std::string& input_file, const std::string& output_file);

#endif