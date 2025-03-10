add_library(project_library
    frequency_counter.cpp
    huffman_tree.cpp
    bit_stream.cpp
    huffman_codec.cpp
    file_compressor.cpp
)

target_include_directories(project_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}) 