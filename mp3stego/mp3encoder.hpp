#ifndef MP3ENCODER_HPP
#define MP3ENCODER_HPP

#include <fstream>
#include <bitset>
#include <vector>
#include <algorithm>

#include "head.hpp"
#include "file_func.hpp"

const unsigned sampling_frequency = 2;
const unsigned crc_bytes = 2;

class mp3Encoder {
public:
    static unsigned is_acceptable_message(std::ifstream& in, std::string message);
    static bool encode(std::ifstream& in, std::ofstream& out, std::string message);

private:
    static unsigned number_of_frames(std::ifstream& in);
    static std::vector<unsigned> rebuild_message(std::string message);
    static std::vector<unsigned> rebuild_symb(char symb);
    static void skip_byte(std::ifstream &in, std::ofstream &out);

    static bool search_valid_header(std::ifstream &in, std::ofstream& out, RawHeader& header);
    static bool search_valid_header(std::ifstream &in, RawHeader& header);
};

unsigned mp3Encoder::is_acceptable_message(std::ifstream& in, std::string message) {
    unsigned frame_num = number_of_frames(in);
    rewind_file(in);
    unsigned message_size = message.size() + 1; // for \0

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

    std::vector <unsigned> bit_message = rebuild_message(message);
    unsigned size_message = bit_message.size();
    unsigned step = 0;

    RawHeader header;

    for (unsigned k = 0; search_valid_header(in, out, header); ++k) {
        if (step < size_message && k % sampling_frequency == 0) {
            Header bufHeader(header);

            //size of frame + 2 bytes for crc  - 1 (which we need)
            unsigned to_skip = bufHeader.frame_size() + ((unsigned) bufHeader.crc_present()) * crc_bytes - 1;
            for (unsigned i = 0; i < to_skip; ++i) {
                skip_byte(in, out);
            }

            char coding_byte = 0;
            in.get(coding_byte);

            unsigned significant_bit = bit_message[step];
            step++;

            if (significant_bit == 1){
                coding_byte = coding_byte | 0x01;
            }
            else {
                coding_byte = coding_byte & 0xFE;
            }

            out.put(coding_byte);
        }
    }

    return true;

}

unsigned mp3Encoder::number_of_frames(std::ifstream& in) {
    unsigned result = 0;
    RawHeader header;
    for (;search_valid_header(in, header); ++result) {
    }
    return result;
}

std::vector<unsigned> mp3Encoder::rebuild_symb(char symb) {

    unsigned symbint = symb;
    std::vector<unsigned> bitint;
    for (unsigned i = 0; i < B ; i++){
       bitint.push_back(std::bitset<B>(symbint)[i]);
    }
    std::reverse(bitint.begin(), bitint.end());

    return bitint;
}

std::vector<unsigned> mp3Encoder::rebuild_message(std::string message){


    std::vector<unsigned> result_message;

    for (unsigned i = 0; i < message.size(); ++i) {
        std::vector<unsigned> buf = rebuild_symb(message[i]);
        for (unsigned j = 0; j < B; ++j) {
            result_message.push_back(buf[j]);
        }
    }

    for (unsigned i = 0; i < B; ++i) {
        result_message.push_back(0);
    }

    std::cout << "encoded bit msg: ";
    for (unsigned i = 0; i < result_message.size(); ++i) {
        std::cout << result_message[i] << " ";
    }
    std::cout << std::endl;

    return result_message;
}

bool mp3Encoder::search_valid_header(std::ifstream &in, std::ofstream& out, RawHeader& header){
    in >> header;
    out << header;

    while (!header.is_valid_header() && !in.fail()) {
        header.read_byte(in);
        out.put(header[3]);
    }

    return !in.fail();
}

bool mp3Encoder::search_valid_header(std::ifstream &in, RawHeader& header){
    in >> header;

    while (!header.is_valid_header() && !in.fail()) {
        header.read_byte(in);
    }

    return !in.fail();
}

#endif // MP3ENCODER_HPP
