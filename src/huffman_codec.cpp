#include "huffman_codec.hpp"


HuffmanEncoder::HuffmanEncoder(const std::unordered_map<char, std::string>& codes, const std::string& output_file)
    : huffman_codes(codes), bit_writer(output_file) {}

void HuffmanEncoder::encode(const std::string& input_data){
    for (char ch : input_data){
        const std::string& code = huffman_codes.at(ch);
        for (char bit : code){
            bit_writer.write_bit(bit == '1');
        }
    }
}

void HuffmanEncoder::finish(){
    bit_writer.flush();
}

HuffmanDecoder::HuffmanDecoder(huffman_node* huffman_tree_root, BitReader& reader)
    : root(huffman_tree_root), bit_reader(reader) {}

void HuffmanDecoder::decode(const std::string& output_file) {
    std::ofstream out_file(output_file, std::ios::binary);
    if (!out_file.is_open()) {
        throw std::runtime_error("Failed to open output file");
    }

    huffman_node* current = root;
    while (true) {
        std::optional<bool> bit_opt = bit_reader.read_bit();
        if (!bit_opt) {
            break;  // End of input file
        }

        if (*bit_opt) {
            current = current->right;
        } else {
            current = current->left;
        }

        if (!current->left && !current->right) {  // Leaf node
            out_file.put(current->ch);
            current = root;  // Reset for next character
        }
    }

    out_file.close();
}