#ifndef MP3ENCODER_HPP
#define MP3ENCODER_HPP

#include <fstream>
#include <bitset>
#include <vector>
#include <algorithm>

#include "head.hpp"
#include "file_func.hpp"

const unsigned sampling_frequency = 3;

class mp3Encoder {
public:
    static unsigned is_acceptable_message(std::ifstream& in, std::string message);
    static bool encode(std::ifstream& in, std::ofstream& out, std::string message);

private:
    static unsigned number_of_frames(std::ifstream& in);
    static std::vector<unsigned int> rebuild_message(std::string message);
    static std::vector<unsigned int> rebuild_symb(unsigned char symb);
    static void skip_byte(std::ifstream &in, std::ofstream &out);
};

unsigned mp3Encoder::is_acceptable_message(std::ifstream& in, std::string message) {
    unsigned frame_num = number_of_frames(in);
    rewind_file(in);
    unsigned message_size = message.size() + 2; // for \0

    unsigned valid_message_size = frame_num / (B * sampling_frequency);
    if (valid_message_size >= message_size)
        return frame_num; // ok

    return -1;
}

void mp3Encoder::skip_byte(std::ifstream &in, std::ofstream &out) {
    char bufbyte;
    in.get(bufbyte);
    out.put(bufbyte);
}

bool mp3Encoder::encode(std::ifstream &in, std::ofstream &out, std::string message) {

    std::vector <unsigned int> bit_message = rebuild_message(message);
    unsigned size_message = bit_message.size();
    unsigned step = 0;
    unsigned k = 0;
    RawHeader header;
    in >> header;
    out << header;
    while (!in.fail()) {
        while (!header.is_valid_header() && !in.fail()) {
            header.read_byte(in);
            out.put(header[3]);
        }
        if (k % sampling_frequency == 0) {
            Header bufHeader(header);
            char bufbyte;
            if(bufHeader.crc_present()) { // skip 2 bytes
                skip_byte(in, out);
                skip_byte(in, out);
            }
            unsigned size = bufHeader.frame_size();
            if (bufHeader.padding_present()) {
                size--;
            }
            for (unsigned i = 0; i < size - 1; ++i) {
                skip_byte(in, out);
            }
            in.get(bufbyte);
            if (step < size_message){
                unsigned int significant_bit = bit_message[step];
                step++;
                if (significant_bit == 1){
                    bufbyte = bufbyte | 0x01;
                } else
                    bufbyte = bufbyte | 0x00;
            }
            out.put(bufbyte);
        }

        header.read_byte(in);
        out.put(header[3]);
        k++;
    }

    return true;

}

unsigned mp3Encoder::number_of_frames(std::ifstream& in) {
    unsigned result = 0;
    RawHeader header;
    in >> header;
    while (!in.fail()) {
        while (!header.is_valid_header() && !in.fail()) {
            header.read_byte(in);
        }

        header.read_byte(in);
        result++;
    }

    return result - 1;
}

std::vector<unsigned int> mp3Encoder::rebuild_symb(unsigned char symb) {

    int symbint = symb;
    std::vector<unsigned int> bitint;
    for (unsigned i = 0; i < 8 ; i++){
       bitint.push_back(std::bitset<8>(symbint)[i]);
    }
    std::reverse(bitint.begin(), bitint.end());

    return bitint;
}

std::vector<unsigned int> mp3Encoder::rebuild_message(std::string message){

    message = message + '\0';
    unsigned int size = message.size();

    std::vector<unsigned int> result_message;

    for (unsigned i = 0; i < size; ++i) {
        std::vector<unsigned int> buf = rebuild_symb(message[i]);
        for (unsigned j = 0; j < 8; ++j) {
            result_message.push_back(buf[j]);
        }
    }

    return result_message;
}

#endif // MP3ENCODER_HPP
