#include "file_compressor.hpp"
#include <iostream>
#include <fstream>

int main() {
    try {
        const std::string input_file = "../input.txt";
        // const std::string input_file = "dominant_e_text.txt";
        const std::string compressed_file = "../compressed.bin";
        const std::string decompressed_file = "../output.txt";

        std::cout << "Compressing " << input_file << " to " << compressed_file << "...\n";
        compress_file(input_file, compressed_file);
        std::cout << "Compression completed successfully!\n";

        std::cout << "Decompressing " << compressed_file << " to " << decompressed_file << "...\n";
        decompress_file(compressed_file, decompressed_file);
        std::cout << "Decompression completed successfully!\n";

        std::ifstream original(input_file, std::ios::binary);
        std::ifstream decompressed(decompressed_file, std::ios::binary);

        if (!original.is_open() || !decompressed.is_open()) {
            throw std::runtime_error("Failed to open files for verification");
        }

        std::string original_content((std::istreambuf_iterator<char>(original)), std::istreambuf_iterator<char>());
        std::string decompressed_content((std::istreambuf_iterator<char>(decompressed)), std::istreambuf_iterator<char>());

        if (original_content == decompressed_content) {
            std::cout << "Verification successful: The decompressed file matches the original input file.\n";
        } else {
            std::cout << "Verification failed: The decompressed file does not match the original input file.\n";
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1; // failure
    }

    return 0; // success
}