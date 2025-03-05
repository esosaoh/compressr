#ifndef HUFFMAN_TREE_HPP
#define HUFFMAN_TREE_HPP

#include <string>
#include <unordered_map>


struct huffman_node {
    char ch;
    int freq;
    huffman_node* left;
    huffman_node* right;

    huffman_node(char ch, int freq)
        : ch(ch), freq(freq), left(nullptr), right(nullptr) {}

    huffman_node(char ch, int freq, huffman_node* left, huffman_node* right)
        : ch(ch), freq(freq), left(left), right(right) {}
};


struct compare {
    bool operator()(huffman_node* a, huffman_node* b){
        return a -> freq > b -> freq;
    }
};

huffman_node * build_huffman_tree(const std::unordered_map<char, int>& freq_map);
void generate_codes(huffman_node* root, const std::string& code, std::unordered_map<char, std::string>& huffman_codes);
void delete_tree(huffman_node* root);

#endif
