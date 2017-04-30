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
    static std::string create_message(std::vector<unsigned int> code_message);
    static unsigned char create_symb(std::vector<unsigned int> code);
    static void skip_byte(std::ifstream &in);
};

void mp3Decoder::skip_byte(std::ifstream &in) {
    char bufbyte;
    in.get(bufbyte);
}

bool mp3Decoder::decode(std::ifstream &in) {

    std::vector <unsigned int> bit_message;
    unsigned step = 0;
    unsigned k = 0;
    RawHeader header;
    in >> header;
    while (!in.fail()) {
        while (!header.is_valid_header() && !in.fail()) {
            header.read_byte(in);
        }
        if (k % sampling_frequency == 0) {
            Header bufHeader(header);
            char bufbyte;
            if(bufHeader.crc_present()) { // skip 2 bytes
                skip_byte(in); skip_byte(in);
            }
            unsigned size = bufHeader.frame_size();
            if (bufHeader.padding_present()) {
                size--;
            }
            for (unsigned i = 0; i < size - 1; ++i) {
                skip_byte(in);
            }
            in.get(bufbyte);
            if ((bufbyte & 0x01) == 0x01) {
                bit_message[step] = 1;
                step++;
            } else {
                bit_message[step] = 0;
                step++;
            }

            size++;
        }

        header.read_byte(in);
        k++;
    }

    std::string message = create_message(bit_message);
    std::cout << std::endl << message;

    return true;

}

unsigned char mp3Decoder::create_symb(std::vector<unsigned int> code){

    unsigned result;
    std::reverse(code.begin(), code.end());
    for (unsigned i = 0; i < code.size(); ++i) {
        result += code[i] * pow(2, i);
    }
    unsigned char result_symb = result;

    return result_symb;
}

std::string mp3Decoder::create_message(std::vector<unsigned int> code_message){

    std::string str_message;
    int size = 0;

    for (unsigned i = 0; i < code_message.size(); ++i) {
        std::vector <unsigned int> buf;
        for (unsigned j = 0; j < 8; ++j, ++i) {
            buf.push_back(code_message[i]);
        }
        char message_symb = create_symb(buf);
        str_message[size] = message_symb;
        size++;
    }

    return str_message;
}

#endif // MP3DECODER_HPP
