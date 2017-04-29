#ifndef CODER_HPP
#define CODER_HPP

#include <fstream>
#include "head.hpp"

class Decoder {
public:
    static unsigned number_of_frames(std::ifstream& in);
};


unsigned Decoder::number_of_frames(std::ifstream& in) {
    unsigned result = 0;
    RawHeader header;
    in >> header;
    while (!in.fail()) {
        while (!header.is_valid_header() && !in.fail()) {
            header.read_byte(in);
        }

//        if (header.is_correct()){
//            std::cout << header.bitrate() << std::endl;
//            std::cout << header.samplerate() << std::endl;
//            std::cout << header.crc_present() << std::endl;
//            std::cout << header.is_correct() << std::endl;
//            std::cout << header.padding_present() << std::endl;
//            std::cout << std::endl;
//        }

        header.read_byte(in);
        result++;
    }

    return result - 1;
}

#endif // CODER_HPP
