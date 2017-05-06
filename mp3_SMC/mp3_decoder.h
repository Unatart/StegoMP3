#ifndef MP3_DECODER_H
#define MP3_DECODER_H

#include <fstream>
#include <bitset>
#include <vector>
#include <algorithm>

#include "head.h"
#include "base_decoder.h"

class mp3_decoder : public base_decoder {
public:
    const std::string decode();

private:
    std::string create_message(std::vector<unsigned> &code_message);
    char create_symb(std::vector<unsigned> &code);
    void skip_byte(std::ifstream &in);
    bool search_valid_header(std::ifstream &in, RawHeader& header);
};

#endif // MP3_DECODER_H
