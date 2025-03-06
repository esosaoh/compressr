#include "file_compressor.hpp"
#include "frequency_counter.hpp"
#include "huffman_codec.hpp"

void serialize_tree(huffman_node* root, std::ofstream& out_file){
    if (!root) return;

    if (!root->left && !root->right){
        out_file.put('1');
        out_file.put(root->ch);
    } else {
        out_file.put('0');
        serialize_tree(root->left, out_file);
        serialize_tree(root->right, out_file);
    }
}

huffman_node* deserialize_tree(std::ifstream& in_file){
    char marker;
    in_file.get(marker);

    if (marker == '1'){
        char ch;
        in_file.get(ch);
        return new huffman_node(ch, 0); // frequency not needed for reconstruction
    } else if (marker == '0'){
        huffman_node* left = deserialize_tree(in_file);
        huffman_node* right = deserialize_tree(in_file);
        huffman_node* node = new huffman_node('\0', 0); //internal node

        node->left = left;
        node->right = right;
        return node;
    } else {
        throw std::runtime_error("Invalid tree format in file");
    }
}

void compress_file(const std::string& input_file, const std::string& output_file){
    // Build the frequency map
    std::unordered_map<char, int> freq_map = char_freq(input_file);

    // Build the Huffman Tree
    huffman_node* root = build_huffman_tree(freq_map);

    // Generate Huffman codes
    std::unordered_map<char, std::string> huffman_codes;
    generate_codes(root, "", huffman_codes);

    // Open output file
    std::ofstream out_file(output_file, std::ios::binary);
    if (!out_file.is_open()){
        throw std::runtime_error("Failed to open the output file");
    }

    // Serialize
    serialize_tree(root, out_file);
    out_file.close();
    
    // Encode the input data
    HuffmanEncoder encoder(huffman_codes, output_file);
    
    std::ifstream in_file(input_file, std::ios::binary);
    std::string input_data((std::istreambuf_iterator<char>(in_file)), std::istreambuf_iterator<char>());
    in_file.close();
    
    encoder.encode(input_data);
    encoder.finish();

    // Clean up
    delete_tree(root);
}

void decompress_file(const std::string& input_file, const std::string& output_file){
    std::ifstream in_file(input_file, std::ios::binary);
    if (!in_file.is_open()){
        throw std::runtime_error("Failed to open input file");
    }

    huffman_node* root = deserialize_tree(in_file);
    in_file.close();

    HuffmanDecoder decoder(root, input_file);
    decoder.decode(output_file);
    
    // Clean up
    delete_tree(root);
}

