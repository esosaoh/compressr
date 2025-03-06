#ifndef FILE_COMPRESSOR_HPP
#define FILE_COMPRESSOR_HPP

#include "huffman_tree.hpp"
#include <fstream>

void serialize_tree(huffman_node* root, std::ofstream& out_file);
huffman_node* deserialize_tree(std::ifstream& in_file);
void compress_file(const std::string& input_file, const std::string& output_file);
void decompress_file(const std::string& input_file, const std::string& output_file);

#endif