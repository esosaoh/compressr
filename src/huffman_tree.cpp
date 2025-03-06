#include <queue>
#include <vector>

#include "huffman_tree.hpp"

huffman_node * build_huffman_tree(const std::unordered_map<char, int>& freq_map){
    std::priority_queue<huffman_node*, std::vector<huffman_node*>, compare> pq;

    for (auto pair : freq_map){
        pq.push(new huffman_node(pair.first, pair.second));
    }

    while (pq.size() != 1){
        huffman_node* left = pq.top();
        pq.pop();
        huffman_node* right = pq.top();
        pq.pop();

        int sum = left->freq + right->freq;

        pq.push(new huffman_node('\0', sum, left, right));
    }

    huffman_node* root = pq.top();
    return root;
}


void generate_codes(huffman_node* root, const std::string& code, std::unordered_map<char, std::string>& huffman_codes){
    if (!root) return;

    if (!root->left && !root->right){
        huffman_codes[root->ch] = code;
    }

    generate_codes(root->left, code + "0", huffman_codes);
    generate_codes(root->right, code + "1", huffman_codes);
}


void delete_tree(huffman_node* root){
    if (!root) return;

    delete_tree(root->left);
    delete_tree(root->right);

    delete root;
}