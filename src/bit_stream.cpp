#include "bit_stream.hpp"

BitWriter::BitWriter(const std::string& file_name) : output_file(file_name, std::ios::binary), buffer(0), bits_used(0) {
    if(!output_file.is_open()){
        throw std::runtime_error("Failed to open the output file");
    }
}

BitWriter::~BitWriter(){
    flush();
    output_file.close();
}

void BitWriter::write_bit(bool bit){
    buffer = (buffer << 1) | bit;
    bits_used++;

    if (bits_used == 8){
        output_file.put(buffer);
        buffer = 0;
        bits_used = 0;
    }
}

void BitWriter::flush(){
    if (bits_used > 0){
        buffer <<= (8 - bits_used);
        output_file.put(buffer);
        buffer = 0;
        bits_used = 0;
    }
}

BitReader::BitReader(const std::string& file_name) : input_file(file_name, std::ios::binary), buffer(0), bits_remaining(0) {
    if(!input_file.is_open()){
        throw std::runtime_error("Failed to open the input file");
    }
}

std::optional<bool> BitReader::read_bit(){
    if (bits_remaining == 0){
        if (!input_file.get(reinterpret_cast<char&>(buffer))){
            return std::nullopt;
        };
        bits_remaining = 8;
    }

    bool bit = (buffer >> (bits_remaining - 1)) & 1;
    bits_remaining--;
    return bit;
}