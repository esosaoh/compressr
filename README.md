# Huffman Compression

A C++ implementation of Huffman coding for file compression & decompression.

## Requirements
- C++17 or higher
- A C++ compiler supporting C++17 standard (e.g., GCC 7+, Clang 5+, MSVC 2017+)

## Building
```bash
g++ -std=c++17 main.cpp file_compressor.cpp frequency_counter.cpp huffman_codec.cpp bit_stream.cpp huffman_tree.cpp -o huffman
```

## Usage
```bash
./huffman <input_file> <output_file>
```


