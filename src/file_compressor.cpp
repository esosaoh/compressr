#include "file_compressor.hpp"
#include "frequency_counter.hpp"
#include "huffman_codec.hpp"

void serialize_tree(huffman_node* root, BitWriter& bit_writer){
    if (!root) return;

    if (!root->left && !root->right) {
        bit_writer.write_bit(true);
        for (int i = 7; i >= 0; i--) { 
            bit_writer.write_bit((root->ch >> i) & 1);
        }
    } else {
        bit_writer.write_bit(false);
        serialize_tree(root->left, bit_writer);
        serialize_tree(root->right, bit_writer);
    }
}

huffman_node* deserialize_tree(BitReader& bit_reader) {
    std::optional<bool> marker_opt = bit_reader.read_bit();
    if (!marker_opt) {
        throw std::runtime_error("Unexpected end of file while reading tree");
    }
    bool marker = *marker_opt;

    if (marker) {
        char ch = 0;
        for (int i = 0; i < 8; i++) {
            auto bit_opt = bit_reader.read_bit();
            if (!bit_opt) {
                throw std::runtime_error("Unexpected end of file while reading character");
            }
            ch = (ch << 1) | *bit_opt;
        }
        return new huffman_node(ch, 0);
    } else {
        huffman_node* left = deserialize_tree(bit_reader);
        huffman_node* right = deserialize_tree(bit_reader);
        huffman_node* node = new huffman_node('\0', 0);
        node->left = left;
        node->right = right;
        return node;
    }
}

void compress_file(const std::string& input_file, const std::string& output_file) {
    // Build the frequency map
    std::unordered_map<char, int> freq_map = char_freq(input_file);

    // Build the Huffman Tree
    huffman_node* root = build_huffman_tree(freq_map);

    // Generate Huffman codes
    std::unordered_map<char, std::string> huffman_codes;
    generate_codes(root, "", huffman_codes);

    // Create a single BitWriter for both tree and data
    BitWriter bit_writer(output_file);

    serialize_tree(root, bit_writer);

    std::ifstream in_file(input_file, std::ios::binary);
    if (!in_file.is_open()) {
        throw std::runtime_error("Failed to open input file for encoding");
    }
    
    std::string input_data((std::istreambuf_iterator<char>(in_file)), 
                          std::istreambuf_iterator<char>());
    in_file.close();

    // Encode each character
    for (char ch : input_data) {
        const std::string& code = huffman_codes.at(ch);
        for (char bit : code) {
            bit_writer.write_bit(bit == '1');
        }
    }
    
    bit_writer.flush();
    delete_tree(root);
}

void decompress_file(const std::string& input_file, const std::string& output_file) {
    BitReader bit_reader(input_file);

    huffman_node* root = deserialize_tree(bit_reader);
    if (!root) {
        throw std::runtime_error("Failed to deserialize Huffman tree");
    }

    std::ofstream out_file(output_file, std::ios::binary);
    if (!out_file.is_open()) {
        delete_tree(root);
        throw std::runtime_error("Failed to open output file");
    }

    huffman_node* current = root;
    while (true) {
        std::optional<bool> bit = bit_reader.read_bit();
        if (!bit) {
            break; 
        }

        current = *bit ? current->right : current->left;

        if (!current->left && !current->right) {  
            out_file.put(current->ch);
            current = root;
        }
    }

    out_file.close();
    delete_tree(root);
}

