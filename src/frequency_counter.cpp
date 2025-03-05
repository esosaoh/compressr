#include <fstream>
#include <iostream>

#include "frequency_counter.hpp"

std::unordered_map<char, int> char_freq(const std::string& file_name){
    std::ifstream input_file(file_name, std::ios::binary);
    std::unordered_map<char, int> freq_map;

    if (!input_file.is_open()){
        std::cerr << "Error: Could not open file " << file_name << std::endl;
        return freq_map;
    }

    char ch;

    while (input_file.get(ch)){
        freq_map[ch]++;
    }

    input_file.close();
    return freq_map;
}