#include <gtest/gtest.h>
#include <unordered_map>
#include "huffman_tree.hpp"

TEST(build_huffman_tree, single_node) {
    std::unordered_map<char,int> freq_map = {{'e', 1}};
    huffman_node* root = build_huffman_tree(freq_map);
    ASSERT_EQ(root->ch, 'e');
    ASSERT_EQ(root->freq, 1);
}

TEST(build_huffman_tree, two_nodes) {
    std::unordered_map<char,int> freq_map = {{'e', 1}, {' ', 13}};
    huffman_node* root = build_huffman_tree(freq_map);
    ASSERT_EQ(root->freq, 14);
    ASSERT_EQ(root->left->ch, 'e');
    ASSERT_EQ(root->right->ch, ' ');
}

TEST(generate_codes, two_node) {
    std::unordered_map<char,int> freq_map = {{'e', 1}, {' ', 13}};
    huffman_node* root = build_huffman_tree(freq_map);
    std::unordered_map<char, std::string> huffman_codes;
    generate_codes(root, "", huffman_codes);
    ASSERT_EQ(huffman_codes['e'], "0");
    ASSERT_EQ(huffman_codes[' '], "1");
}

TEST(generate_codes, multiple_nodes) {
    std::unordered_map<char,int> freq_map = {{'A', 5},
                                            {'B', 9},
                                            {'C', 12},
                                            {'D', 4},
                                            {'E', 16},
                                            {'F', 45},
                                            {'G', 7},
                                            {'H', 6}};

    huffman_node* root = build_huffman_tree(freq_map);
    std::unordered_map<char, std::string> huffman_codes;
    generate_codes(root, "", huffman_codes);

    for (const auto& pair : freq_map) {
        ASSERT_TRUE(huffman_codes.find(pair.first) != huffman_codes.end());
    }

    // More frequent characters have shorter codes
    ASSERT_LT(huffman_codes['F'].size(), huffman_codes['E'].size());
    ASSERT_LT(huffman_codes['E'].size(), huffman_codes['D'].size());
    ASSERT_GT(huffman_codes['D'].size(), huffman_codes['C'].size());
}

TEST(delete_tree, single_node) {
    std::unordered_map<char,int> freq_map = {{'e', 1}};
    huffman_node* root = build_huffman_tree(freq_map);
    delete_tree(root);
}