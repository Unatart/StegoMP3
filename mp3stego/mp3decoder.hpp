#ifndef MP3DECODER_HPP
#define MP3DECODER_HPP

#include <fstream>
#include <bitset>
#include <vector>
#include <algorithm>

#include "head.hpp"
#include "file_func.hpp"
#include "mp3encoder.hpp"

class mp3Decoder {
public:
    static bool decode(std::ifstream& in);

private:
    static std::string create_message(std::vector<unsigned> &code_message);
    static char create_symb(std::vector<unsigned> &code);
    static void skip_byte(std::ifstream &in);

    static bool search_valid_header(std::ifstream &in, RawHeader& header);
};

void mp3Decoder::skip_byte(std::ifstream &in) {
    char bufbyte;
    in.get(bufbyte);
}

bool mp3Decoder::decode(std::ifstream &in) {

    std::vector <unsigned> bit_message;
    RawHeader header;

    for (unsigned k = 0; search_valid_header(in, header); ++k) {
        if (k % sampling_frequency == 0) {
            Header bufHeader(header);

            unsigned to_skip = bufHeader.frame_size() + ((unsigned) bufHeader.crc_present()) * crc_bytes - 1;
            for (unsigned i = 0; i < to_skip; ++i) {
                skip_byte(in);
            }

            char coding_byte = 0;
            in.get(coding_byte);
            unsigned variable = (unsigned) ((coding_byte & 0x01) == 0x01);
            bit_message.push_back(variable);

            if (bit_message.size() % B == 0) {
                bool is_end_of_message = true;
                for (unsigned i = 0; i < B; ++i) {
                    if (bit_message[bit_message.size() - 1 - i] == 1) {
                        is_end_of_message = false;
                        break;
                    }
                }
                if (is_end_of_message) {
                    break;
                }
            }
        }
    }

    std::cout << "decoded bit message: ";
    for (auto i : bit_message) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::string message = create_message(bit_message);
    std::cout << "message: " <<"|" << message << "|" << std::endl;

    return true;

}

char mp3Decoder::create_symb(std::vector<unsigned>& code){

    unsigned result = 0;
    std::reverse(code.begin(), code.end());
    for (unsigned i = 0; i < code.size(); ++i) {
        result += code[i] * pow(2, i);
    }
    char result_symb = result;

    return result_symb;
}

std::string mp3Decoder::create_message(std::vector<unsigned>& code_message){

    std::string str_message;

    for (unsigned i = 0; i < code_message.size() - B; i += B) {
        std::vector <unsigned> buf;
        for (unsigned j = 0; j < B; ++j) {
            buf.push_back(code_message[i + j]);
        }
        char message_symb = create_symb(buf);
        str_message.push_back(message_symb);
    }

    return str_message;
}

bool mp3Decoder::search_valid_header(std::ifstream &in, RawHeader& header){
    in >> header;
    while (!header.is_valid_header() && !in.fail()) {
        header.read_byte(in);
    }
    return !in.fail();
}

#endif // MP3DECODER_HPP
