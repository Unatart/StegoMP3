#ifndef MP3_ENCODER_H
#define MP3_ENCODER_H

#include <fstream>
#include <bitset>
#include <vector>
#include <algorithm>

#include "base_encoder.h"
#include "head.h"
#include "io.h"

#define BAD_MESSAGE -101

class mp3_encoder : public base_encoder
{
public:
    bool encode();

private:
    void rewind_file(std::ifstream& in);
    unsigned is_acceptable_message();
    unsigned number_of_frames(std::ifstream& in);
    std::vector<unsigned> rebuild_message();
    std::vector<unsigned> rebuild_symb(char symb);
    void skip_byte(std::ifstream &in, std::ofstream &out);

    bool search_valid_header(std::ifstream &in, std::ofstream& out, RawHeader& header);
    bool search_valid_header(std::ifstream &in, RawHeader& header);
};

#endif // MP3_ENCODER_H
