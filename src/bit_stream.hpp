#ifndef BIT_STREAM_HPP
#define BIT_STREAM_HPP

#include <fstream>
#include <optional>

class BitWriter{
    private:
        std::ofstream output_file;
        unsigned char buffer;
        int bits_used;

    public:
        BitWriter(const std::string& file_name);
        ~BitWriter();
        void write_bit(bool bit);
        void flush();
};

class BitReader{
    private:
        std::ifstream input_file;
        unsigned char buffer;
        int bits_remaining;

    public:
        BitReader(const std::string& file_name);
        std::optional<bool> read_bit();
};


#endif